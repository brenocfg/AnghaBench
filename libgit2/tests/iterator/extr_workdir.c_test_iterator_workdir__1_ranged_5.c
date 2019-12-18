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
 int /*<<< orphan*/  status_paths_range_5 ; 
 int /*<<< orphan*/  workdir_iterator_test (char*,char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_iterator_workdir__1_ranged_5(void)
{
	workdir_iterator_test(
		"status", "subdir/modified_file", "subdir/modified_file",
		1, 0, status_paths_range_5, NULL);
}