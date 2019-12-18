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
 int /*<<< orphan*/  TEST_ENTER (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uint16_t ; 
 int /*<<< orphan*/  uint32_t ; 
 int /*<<< orphan*/  uint64_t ; 

__attribute__((used)) static void test_enter(void)
{
#if defined(__x86_64__)
    TEST_ENTER("q", uint64_t, 0);
    TEST_ENTER("q", uint64_t, 1);
    TEST_ENTER("q", uint64_t, 2);
    TEST_ENTER("q", uint64_t, 31);
#else
    TEST_ENTER("l", uint32_t, 0);
    TEST_ENTER("l", uint32_t, 1);
    TEST_ENTER("l", uint32_t, 2);
    TEST_ENTER("l", uint32_t, 31);
#endif

    TEST_ENTER("w", uint16_t, 0);
    TEST_ENTER("w", uint16_t, 1);
    TEST_ENTER("w", uint16_t, 2);
    TEST_ENTER("w", uint16_t, 31);
}