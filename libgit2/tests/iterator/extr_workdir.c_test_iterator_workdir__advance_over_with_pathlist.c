#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  length; scalar_t__ contents; } ;
typedef  TYPE_2__ git_vector ;
struct TYPE_9__ {char** strings; int /*<<< orphan*/  count; } ;
struct TYPE_11__ {int flags; TYPE_1__ pathlist; } ;
typedef  TYPE_3__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;

/* Variables and functions */
 int GIT_ITERATOR_DONT_AUTOEXPAND ; 
 int GIT_ITERATOR_DONT_IGNORE_CASE ; 
 TYPE_3__ GIT_ITERATOR_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_ITERATOR_STATUS_FILTERED ; 
 int /*<<< orphan*/  GIT_ITERATOR_STATUS_NORMAL ; 
 int /*<<< orphan*/  GIT_ITEROVER ; 
 TYPE_2__ GIT_VECTOR_INIT ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect_advance_over (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_iterator_advance (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_for_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_vector_insert (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_iterator_workdir__advance_over_with_pathlist(void)
{
	git_vector pathlist = GIT_VECTOR_INIT;
	git_iterator *i;
	git_iterator_options i_opts = GIT_ITERATOR_OPTIONS_INIT;

	git_vector_insert(&pathlist, "dirA/subdir1/subdir2/file");
	git_vector_insert(&pathlist, "dirB/subdir1/subdir2");
	git_vector_insert(&pathlist, "dirC/subdir1/nonexistent");
	git_vector_insert(&pathlist, "dirD/subdir1/nonexistent");
	git_vector_insert(&pathlist, "dirD/subdir1/subdir2");
	git_vector_insert(&pathlist, "dirD/nonexistent");

	i_opts.pathlist.strings = (char **)pathlist.contents;
	i_opts.pathlist.count = pathlist.length;
	i_opts.flags |= GIT_ITERATOR_DONT_IGNORE_CASE |
		GIT_ITERATOR_DONT_AUTOEXPAND;

	g_repo = cl_git_sandbox_init("icase");

	/* Create a directory that has a file that is included in our pathlist */
	cl_must_pass(p_mkdir("icase/dirA", 0777));
	cl_must_pass(p_mkdir("icase/dirA/subdir1", 0777));
	cl_must_pass(p_mkdir("icase/dirA/subdir1/subdir2", 0777));
	cl_git_rewritefile("icase/dirA/subdir1/subdir2/file", "foo!");

	/* Create a directory that has a directory that is included in our pathlist */
	cl_must_pass(p_mkdir("icase/dirB", 0777));
	cl_must_pass(p_mkdir("icase/dirB/subdir1", 0777));
	cl_must_pass(p_mkdir("icase/dirB/subdir1/subdir2", 0777));
	cl_git_rewritefile("icase/dirB/subdir1/subdir2/file", "foo!");

	/* Create a directory that would contain an entry in our pathlist, but
	 * that entry does not actually exist.  We don't know this until we
	 * advance_over it.  We want to distinguish this from an actually empty
	 * or ignored directory.
	 */
	cl_must_pass(p_mkdir("icase/dirC", 0777));
	cl_must_pass(p_mkdir("icase/dirC/subdir1", 0777));
	cl_must_pass(p_mkdir("icase/dirC/subdir1/subdir2", 0777));
	cl_git_rewritefile("icase/dirC/subdir1/subdir2/file", "foo!");

	/* Create a directory that has a mix of actual and nonexistent paths */
	cl_must_pass(p_mkdir("icase/dirD", 0777));
	cl_must_pass(p_mkdir("icase/dirD/subdir1", 0777));
	cl_must_pass(p_mkdir("icase/dirD/subdir1/subdir2", 0777));
	cl_git_rewritefile("icase/dirD/subdir1/subdir2/file", "foo!");

	cl_git_pass(git_iterator_for_workdir(&i, g_repo, NULL, NULL, &i_opts));

	expect_advance_over(i, "dirA/", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "dirB/", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "dirC/", GIT_ITERATOR_STATUS_FILTERED);
	expect_advance_over(i, "dirD/", GIT_ITERATOR_STATUS_NORMAL);

	cl_git_fail_with(GIT_ITEROVER, git_iterator_advance(NULL, i));
	git_iterator_free(i);
	git_vector_free(&pathlist);
}