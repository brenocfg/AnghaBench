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
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_commit_from_ids (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 char* parent_id_str ; 
 char* tree_id_str ; 

void test_commit_write__can_validate_objects(void)
{
	git_oid tree_id, parent_id, commit_id;

	/* this is a valid tree and parent */
	git_oid_fromstr(&tree_id, tree_id_str);
	git_oid_fromstr(&parent_id, parent_id_str);
	cl_git_pass(create_commit_from_ids(&commit_id, &tree_id, &parent_id));

	/* this is a wholly invented tree id */
	git_oid_fromstr(&tree_id, "1234567890123456789012345678901234567890");
	git_oid_fromstr(&parent_id, parent_id_str);
	cl_git_fail(create_commit_from_ids(&commit_id, &tree_id, &parent_id));

	/* this is a wholly invented parent id */
	git_oid_fromstr(&tree_id, tree_id_str);
	git_oid_fromstr(&parent_id, "1234567890123456789012345678901234567890");
	cl_git_fail(create_commit_from_ids(&commit_id, &tree_id, &parent_id));

	/* these are legitimate objects, but of the wrong type */
	git_oid_fromstr(&tree_id, parent_id_str);
	git_oid_fromstr(&parent_id, tree_id_str);
	cl_git_fail(create_commit_from_ids(&commit_id, &tree_id, &parent_id));
}