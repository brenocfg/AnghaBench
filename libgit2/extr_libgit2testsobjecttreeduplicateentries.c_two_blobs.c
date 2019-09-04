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
typedef  int /*<<< orphan*/  git_treebuilder ;
typedef  int /*<<< orphan*/  git_tree_entry ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_treebuilder_insert (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void two_blobs(git_treebuilder *bld)
{
	git_oid oid;
	const git_tree_entry *entry;

	cl_git_pass(git_oid_fromstr(&oid,
		"a8233120f6ad708f843d861ce2b7228ec4e3dec6"));	/* blob oid (README) */

	cl_git_pass(git_treebuilder_insert(
		&entry,	bld, "duplicate", &oid,
		GIT_FILEMODE_BLOB));

	cl_git_pass(git_oid_fromstr(&oid,
		"a71586c1dfe8a71c6cbf6c129f404c5642ff31bd"));	/* blob oid (new.txt) */

	cl_git_pass(git_treebuilder_insert(
		&entry,	bld, "duplicate", &oid,
		GIT_FILEMODE_BLOB));
}