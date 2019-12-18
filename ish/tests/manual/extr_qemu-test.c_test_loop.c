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
 int /*<<< orphan*/  TEST_LOOP (char*) ; 

void test_loop(void)
{
    long ecx, zf;
    const long ecx_vals[] = {
        0,
        1,
        0x10000,
        0x10001,
#if defined(__x86_64__)
        0x100000000L,
        0x100000001L,
#endif
    };
    int i, res;

#if !defined(__x86_64__)
    TEST_LOOP("jcxz");
#endif

    TEST_LOOP("jecxz");
    TEST_LOOP("loop");
    TEST_LOOP("loopz");
    TEST_LOOP("loopnz");
}