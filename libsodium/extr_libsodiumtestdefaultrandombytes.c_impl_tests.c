#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/ * close; int /*<<< orphan*/  uniform; } ;
typedef  TYPE_1__ randombytes_implementation ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  randombytes_close () ; 
 int randombytes_random () ; 
 int /*<<< orphan*/  randombytes_set_implementation (TYPE_1__*) ; 
 TYPE_1__ randombytes_sysrandom_implementation ; 
 int randombytes_uniform (int) ; 
 int /*<<< orphan*/  randombytes_uniform_impl ; 

__attribute__((used)) static int
impl_tests(void)
{
    randombytes_implementation impl = randombytes_sysrandom_implementation;
    uint32_t                   v = randombytes_random();

    impl.uniform = randombytes_uniform_impl;
    randombytes_close();
    randombytes_set_implementation(&impl);
    assert(randombytes_uniform(1) == 1);
    assert(randombytes_uniform(v) == v);
    assert(randombytes_uniform(v) == v);
    assert(randombytes_uniform(v) == v);
    assert(randombytes_uniform(v) == v);
    randombytes_close();
    impl.close = NULL;
    randombytes_close();

    return 0;
}