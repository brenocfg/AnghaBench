#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_8__ {char** strings; size_t count; } ;
struct TYPE_10__ {TYPE_1__ pathspec; } ;
typedef  TYPE_3__ git_diff_options ;
struct TYPE_9__ {int /*<<< orphan*/  path; } ;
struct TYPE_11__ {TYPE_2__ new_file; } ;
typedef  TYPE_4__ git_diff_delta ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 TYPE_3__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_strn (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 TYPE_4__* git_diff_get_delta (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void ensure_submodules_found(
	git_repository *repo,
	const char **paths,
	size_t cnt)
{
	git_diff *diff = NULL;
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	const git_diff_delta *delta;
	size_t i, pathlen;

	opts.pathspec.strings = (char **)paths;
	opts.pathspec.count = cnt;

	git_diff_index_to_workdir(&diff, repo, NULL, &opts);

	cl_assert_equal_i(cnt, git_diff_num_deltas(diff));

	for (i = 0; i < cnt; i++) {
		delta = git_diff_get_delta(diff, i);

		/* ensure that the given path is returned w/o trailing slashes. */
		pathlen = strlen(opts.pathspec.strings[i]);

		while (pathlen && opts.pathspec.strings[i][pathlen - 1] == '/')
			pathlen--;

		cl_assert_equal_strn(opts.pathspec.strings[i], delta->new_file.path, pathlen);
	}

	git_diff_free(diff);
}