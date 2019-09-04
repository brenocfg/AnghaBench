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
 int /*<<< orphan*/  GIT_EPEEL ; 
 int /*<<< orphan*/  assert_invalid_single_spec (char*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_obj ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_object (char*,char*) ; 

void test_refs_revparse__to_type(void)
{
	assert_invalid_single_spec("wrapped_tag^{trip}");
	test_object("point_to_blob^{commit}", NULL);
	cl_assert_equal_i(
		GIT_EPEEL, git_revparse_single(&g_obj, g_repo, "wrapped_tag^{blob}"));

	test_object("wrapped_tag^{commit}", "a65fedf39aefe402d3bb6e24df4d4f5fe4547750");
	test_object("wrapped_tag^{tree}", "944c0f6e4dfa41595e6eb3ceecdb14f50fe18162");
	test_object("point_to_blob^{blob}", "1385f264afb75a56a5bec74243be9b367ba4ca08");
	test_object("master^{commit}^{commit}", "a65fedf39aefe402d3bb6e24df4d4f5fe4547750");
}