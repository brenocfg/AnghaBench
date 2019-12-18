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
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 int /*<<< orphan*/  sleep (int) ; 

__attribute__((used)) static void *
incorrect_mask_bug_sleeper(void* arg)
{
	int i;
	for (i = 0; i < 10; i++)
		sleep(1);

	atf_tc_fail("sleeper");
}