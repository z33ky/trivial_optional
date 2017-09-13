#include "optional.hpp"
#include <type_traits>

struct Foo
{
};

struct NDFoo
{
	NDFoo(const NDFoo&) = default;
	NDFoo(NDFoo&&) = default;
	~NDFoo() { ; }
};

struct NCFoo
{
	NCFoo(const NCFoo&) { ; }
	NCFoo(NCFoo&&) = default;
	~NCFoo() = default;
};

struct NMFoo
{
	NMFoo(const NMFoo&) = default;
	NMFoo(NMFoo&&) { ; }
	~NMFoo() = default;
};

template<typename T>
void test()
{
	using optional = boost::optional<T>;
	static_assert(std::is_trivially_destructible<optional>::value == std::is_trivially_destructible<T>::value, "destruct");
	static_assert(std::is_trivially_copy_constructible<optional>::value == std::is_trivially_copy_constructible<T>::value, "copy");
	static_assert(std::is_trivially_move_constructible<optional>::value == std::is_trivially_move_constructible<T>::value, "move");
}

int main()
{
	test<Foo>();
	test<NDFoo>();
	test<NCFoo>();
	test<NMFoo>();
}
