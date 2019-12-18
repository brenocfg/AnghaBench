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
 void* __start_initcall ; 
 void* __stop_initcall ; 
 int /*<<< orphan*/  test_bsx () ; 
 int /*<<< orphan*/  test_code16 () ; 
 int /*<<< orphan*/  test_conv () ; 
 int /*<<< orphan*/  test_fxsave () ; 
 int /*<<< orphan*/  test_jcc () ; 
 int /*<<< orphan*/  test_lea () ; 
 int /*<<< orphan*/  test_mul () ; 
 int /*<<< orphan*/  test_segs () ; 
 int /*<<< orphan*/  test_sse () ; 
 int /*<<< orphan*/  test_string () ; 
 int /*<<< orphan*/  test_vm86 () ; 
 int /*<<< orphan*/  test_xchg () ; 

int main(int argc, char **argv)
{
    void **ptr;
    void (*func)(void);

    ptr = &__start_initcall;
    while (ptr != &__stop_initcall) {
        func = *ptr++;
        func();
    }
    test_bsx();
    test_mul();
    test_jcc();
    //test_loop();
    //test_floats();
#if !defined(__x86_64__)
    //test_bcd();
#endif
    test_xchg();
    test_string();
    //test_misc();
    test_lea();
#ifdef TEST_SEGS
    test_segs();
    test_code16();
#endif
#ifdef TEST_VM86
    test_vm86();
#endif
#if !defined(__x86_64__)
    //test_exceptions();
    //test_self_modifying_code();
    //test_single_step();
#endif
    //test_enter();
    test_conv();
#ifdef TEST_SSE
    test_sse();
    test_fxsave();
#endif
    return 0;
}