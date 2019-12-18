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
 int /*<<< orphan*/  MALLOC_DONT_FAIL ; 
 int /*<<< orphan*/  TEST_FAIL_MESSAGE (char*) ; 
 scalar_t__ malloc_count ; 
 int /*<<< orphan*/  malloc_fail_countdown ; 

void UnityMalloc_EndTest(void)
{
    malloc_fail_countdown = MALLOC_DONT_FAIL;
    if (malloc_count != 0)
    {
        TEST_FAIL_MESSAGE("This test leaks!");
    }
}