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
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIFF_FORMAT_RAW ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_print_callback__to_file_handle ; 
 int /*<<< orphan*/ * stderr ; 

void diff_print_raw(FILE *fp, git_diff *diff)
{
	cl_git_pass(
		git_diff_print(diff, GIT_DIFF_FORMAT_RAW,
			git_diff_print_callback__to_file_handle, fp ? fp : stderr));
}