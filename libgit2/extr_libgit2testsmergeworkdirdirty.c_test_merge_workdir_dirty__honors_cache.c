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
 char*** affected ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  merge_differently_filtered_files (char**) ; 

void test_merge_workdir_dirty__honors_cache(void)
{
	char **files;
	size_t i;

	for (i = 0, files = affected[i]; files[0]; files = affected[++i])
		cl_git_pass(merge_differently_filtered_files(files));
}