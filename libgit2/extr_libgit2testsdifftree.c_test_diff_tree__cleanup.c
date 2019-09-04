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
 int /*<<< orphan*/  a ; 
 int /*<<< orphan*/  b ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/  diff ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ ) ; 

void test_diff_tree__cleanup(void)
{
	git_diff_free(diff);
	git_tree_free(a);
	git_tree_free(b);

	cl_git_sandbox_cleanup();

}