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
 int /*<<< orphan*/  assert_invalid_single_spec (char*) ; 
 int /*<<< orphan*/  test_object (char*,char*) ; 

void test_refs_revparse__ordinal(void)
{
	assert_invalid_single_spec("master@{-2}");
	
	/* TODO: make the test below actually fail
	 * cl_git_fail(git_revparse_single(&g_obj, g_repo, "master@{1a}"));
	 */

	test_object("nope@{0}", NULL);
	test_object("master@{31415}", NULL);
	test_object("@{1000}", NULL);
	test_object("@{2}", NULL);

	test_object("@{0}", "a65fedf39aefe402d3bb6e24df4d4f5fe4547750");
	test_object("@{1}", "be3563ae3f795b2b4353bcce3a527ad0a4f7f644");

	test_object("master@{0}", "a65fedf39aefe402d3bb6e24df4d4f5fe4547750");
	test_object("master@{1}", "be3563ae3f795b2b4353bcce3a527ad0a4f7f644");
	test_object("heads/master@{1}", "be3563ae3f795b2b4353bcce3a527ad0a4f7f644");
	test_object("refs/heads/master@{1}", "be3563ae3f795b2b4353bcce3a527ad0a4f7f644");
}