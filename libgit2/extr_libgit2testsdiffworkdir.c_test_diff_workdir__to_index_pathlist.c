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
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_9__ {char** strings; int /*<<< orphan*/  count; } ;
struct TYPE_11__ {int /*<<< orphan*/  flags; TYPE_1__ pathspec; } ;
typedef  TYPE_3__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIFF_DISABLE_PATHSPEC_MATCH ; 
 int /*<<< orphan*/  GIT_DIFF_INCLUDE_IGNORED ; 
 TYPE_3__ GIT_DIFF_OPTIONS_INIT ; 
 TYPE_2__ GIT_VECTOR_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_vector_insert (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_diff_workdir__to_index_pathlist(void)
{
	git_index *index;
	git_diff *diff;
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_vector pathlist = GIT_VECTOR_INIT;

	git_vector_insert(&pathlist, "foobar/asdf");
	git_vector_insert(&pathlist, "subdir/asdf");
	git_vector_insert(&pathlist, "ignored/asdf");

	g_repo = cl_git_sandbox_init("status");

	cl_git_mkfile("status/.gitignore", ".gitignore\n" "ignored/\n");

	cl_must_pass(p_mkdir("status/foobar", 0777));
	cl_git_mkfile("status/foobar/one", "one\n");

	cl_must_pass(p_mkdir("status/ignored", 0777));
	cl_git_mkfile("status/ignored/one", "one\n");
	cl_git_mkfile("status/ignored/two", "two\n");
	cl_git_mkfile("status/ignored/three", "three\n");

	cl_git_pass(git_repository_index(&index, g_repo));

	opts.flags = GIT_DIFF_INCLUDE_IGNORED;
	opts.pathspec.strings = (char **)pathlist.contents;
	opts.pathspec.count = pathlist.length;

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, index, &opts));
	cl_assert_equal_i(0, git_diff_num_deltas(diff));
	git_diff_free(diff);

	opts.flags |= GIT_DIFF_DISABLE_PATHSPEC_MATCH;

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, index, &opts));
	cl_assert_equal_i(0, git_diff_num_deltas(diff));
	git_diff_free(diff);

	git_index_free(index);
	git_vector_free(&pathlist);
}