#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_4__ {int /*<<< orphan*/  checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_hashfile (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void execute_test(void)
{
	git_oid oid, check;
	git_commit *commit;
	git_tree *tree;
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;

	cl_git_pass(git_reference_name_to_id(&oid, g_repo, "refs/heads/branch1"));
	cl_git_pass(git_commit_lookup(&commit, g_repo, &oid));
	cl_git_pass(git_commit_tree(&tree, commit));

	opts.checkout_strategy = GIT_CHECKOUT_SAFE;

	cl_git_pass(git_checkout_tree(g_repo, (git_object *)tree, &opts));

	git_tree_free(tree);
	git_commit_free(commit);

	/* Verify that the lenna.jpg file was checked out correctly */
	cl_git_pass(git_oid_fromstr(&check, "8ab005d890fe53f65eda14b23672f60d9f4ec5a1"));
	cl_git_pass(git_odb_hashfile(&oid, "binaryunicode/lenna.jpg", GIT_OBJECT_BLOB));
	cl_assert_equal_oid(&oid, &check);

	/* Verify that the text file was checked out correctly */
	cl_git_pass(git_oid_fromstr(&check, "965b223880dd4249e2c66a0cc0b4cffe1dc40f5a"));
	cl_git_pass(git_odb_hashfile(&oid, "binaryunicode/utf16_withbom_noeol_crlf.txt", GIT_OBJECT_BLOB));
	cl_assert_equal_oid(&oid, &check);
}