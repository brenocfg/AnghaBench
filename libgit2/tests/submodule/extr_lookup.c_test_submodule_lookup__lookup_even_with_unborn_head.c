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
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_symbolic_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_submodule_lookup__simple_lookup () ; 

void test_submodule_lookup__lookup_even_with_unborn_head(void)
{
	git_reference *head;

	/* put us on an unborn branch */
	cl_git_pass(git_reference_symbolic_create(
		&head, g_repo, "HEAD", "refs/heads/garbage", 1, NULL));
	git_reference_free(head);

	test_submodule_lookup__simple_lookup(); /* baseline should still pass */
}