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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OPT_ENABLE_STRICT_OBJECT_CREATION ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_commit_from_ids (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_libgit2_opts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 char* parent_id_str ; 
 char* tree_id_str ; 

void test_commit_write__can_write_invalid_objects(void)
{
	git_oid expected_id, tree_id, parent_id, commit_id;

	cl_git_pass(git_libgit2_opts(GIT_OPT_ENABLE_STRICT_OBJECT_CREATION, 0));

	/* this is a valid tree and parent */
	git_oid_fromstr(&tree_id, tree_id_str);
	git_oid_fromstr(&parent_id, parent_id_str);

	git_oid_fromstr(&expected_id, "c8571bbec3a72c4bcad31648902e5a453f1adece");
	cl_git_pass(create_commit_from_ids(&commit_id, &tree_id, &parent_id));
	cl_assert_equal_oid(&expected_id, &commit_id);

	/* this is a wholly invented tree id */
	git_oid_fromstr(&tree_id, "1234567890123456789012345678901234567890");
	git_oid_fromstr(&parent_id, parent_id_str);

	git_oid_fromstr(&expected_id, "996008340b8e68d69bf3c28d7c57fb7ec3c8e202");
	cl_git_pass(create_commit_from_ids(&commit_id, &tree_id, &parent_id));
	cl_assert_equal_oid(&expected_id, &commit_id);

	/* this is a wholly invented parent id */
	git_oid_fromstr(&tree_id, tree_id_str);
	git_oid_fromstr(&parent_id, "1234567890123456789012345678901234567890");

	git_oid_fromstr(&expected_id, "d78f660cab89d9791ca6714b57978bf2a7e709fd");
	cl_git_pass(create_commit_from_ids(&commit_id, &tree_id, &parent_id));
	cl_assert_equal_oid(&expected_id, &commit_id);

	/* these are legitimate objects, but of the wrong type */
	git_oid_fromstr(&tree_id, parent_id_str);
	git_oid_fromstr(&parent_id, tree_id_str);

	git_oid_fromstr(&expected_id, "5d80c07414e3f18792949699dfcacadf7748f361");
	cl_git_pass(create_commit_from_ids(&commit_id, &tree_id, &parent_id));
	cl_assert_equal_oid(&expected_id, &commit_id);
}