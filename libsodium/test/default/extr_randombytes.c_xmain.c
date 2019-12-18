#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  compat_tests () ; 
 int /*<<< orphan*/  impl_tests () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  randombytes_salsa20_implementation ; 
 int /*<<< orphan*/  randombytes_set_implementation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  randombytes_tests () ; 

int
main(void)
{
    compat_tests();
    randombytes_tests();
#ifndef __EMSCRIPTEN__
    impl_tests();
#endif
    printf("OK\n");

#ifndef __EMSCRIPTEN__
    randombytes_set_implementation(&randombytes_salsa20_implementation);
#endif

    return 0;
}