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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_treebuilder_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_treebuilder_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_treebuilder_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_object_tree_write__protect_filesystems(void)
{
	git_treebuilder *builder;
	git_oid bid;

	cl_git_pass(git_oid_fromstr(&bid, "fa49b077972391ad58037050f2a75f74e3671e92"));

	/* Ensure that (by default) we can write objects with funny names on
	 * platforms that are not affected.
	 */
	cl_git_pass(git_treebuilder_new(&builder, g_repo, NULL));

#ifndef GIT_WIN32
	cl_git_pass(git_treebuilder_insert(NULL, builder, ".git.", &bid, GIT_FILEMODE_BLOB));
	cl_git_pass(git_treebuilder_insert(NULL, builder, "git~1", &bid, GIT_FILEMODE_BLOB));
#endif

#ifndef __APPLE__
	cl_git_pass(git_treebuilder_insert(NULL, builder, ".git\xef\xbb\xbf", &bid, GIT_FILEMODE_BLOB));
	cl_git_pass(git_treebuilder_insert(NULL, builder, ".git\xe2\x80\xad", &bid, GIT_FILEMODE_BLOB));
#endif

	git_treebuilder_free(builder);

	/* Now turn on core.protectHFS and core.protectNTFS and validate that these
	 * paths are rejected.
	 */

	cl_repo_set_bool(g_repo, "core.protectHFS", true);
	cl_repo_set_bool(g_repo, "core.protectNTFS", true);

	cl_git_pass(git_treebuilder_new(&builder, g_repo, NULL));

	cl_git_fail(git_treebuilder_insert(NULL, builder, ".git.", &bid, GIT_FILEMODE_BLOB));
	cl_git_fail(git_treebuilder_insert(NULL, builder, "git~1", &bid, GIT_FILEMODE_BLOB));

	cl_git_fail(git_treebuilder_insert(NULL, builder, ".git\xef\xbb\xbf", &bid, GIT_FILEMODE_BLOB));
	cl_git_fail(git_treebuilder_insert(NULL, builder, ".git\xe2\x80\xad", &bid, GIT_FILEMODE_BLOB));

	git_treebuilder_free(builder);
}