#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* start; char* end; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;
struct TYPE_9__ {scalar_t__ mode; int /*<<< orphan*/  path; } ;
typedef  TYPE_2__ git_index_entry ;

/* Variables and functions */
 scalar_t__ GIT_FILEMODE_COMMIT ; 
 scalar_t__ GIT_FILEMODE_TREE ; 
 int /*<<< orphan*/  GIT_ITERATOR_DONT_AUTOEXPAND ; 
 TYPE_1__ GIT_ITERATOR_OPTIONS_INIT ; 
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_ (int,char const*) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int git_iterator_advance (TYPE_2__ const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_advance_into (TYPE_2__ const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_current (TYPE_2__ const**,int /*<<< orphan*/ *) ; 
 int git_iterator_current_is_ignored (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_for_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_iterator_workdir__builtin_ignores(void)
{
	git_iterator *i;
	git_iterator_options i_opts = GIT_ITERATOR_OPTIONS_INIT;
	const git_index_entry *entry;
	int idx;
	static struct {
		const char *path;
		bool ignored;
	} expected[] = {
		{ "dir/", true },
		{ "file", false },
		{ "ign", true },
		{ "macro_bad", false },
		{ "macro_test", false },
		{ "root_test1", false },
		{ "root_test2", false },
		{ "root_test3", false },
		{ "root_test4.txt", false },
		{ "sub/", false },
		{ "sub/.gitattributes", false },
		{ "sub/abc", false },
		{ "sub/dir/", true },
		{ "sub/file", false },
		{ "sub/ign/", true },
		{ "sub/sub/", false },
		{ "sub/sub/.gitattributes", false },
		{ "sub/sub/dir", false }, /* file is not actually a dir */
		{ "sub/sub/file", false },
		{ NULL, false }
	};

	g_repo = cl_git_sandbox_init("attr");

	cl_git_pass(p_mkdir("attr/sub/sub/.git", 0777));
	cl_git_mkfile("attr/sub/.git", "whatever");

	i_opts.flags = GIT_ITERATOR_DONT_AUTOEXPAND;
	i_opts.start = "dir";
	i_opts.end = "sub/sub/file";

	cl_git_pass(git_iterator_for_workdir(
		&i, g_repo, NULL, NULL, &i_opts));
	cl_git_pass(git_iterator_current(&entry, i));

	for (idx = 0; entry != NULL; ++idx) {
		int ignored = git_iterator_current_is_ignored(i);

		cl_assert_equal_s(expected[idx].path, entry->path);
		cl_assert_(ignored == expected[idx].ignored, expected[idx].path);

		if (!ignored &&
			(entry->mode == GIT_FILEMODE_TREE ||
			 entry->mode == GIT_FILEMODE_COMMIT))
		{
			/* it is possible to advance "into" a submodule */
			cl_git_pass(git_iterator_advance_into(&entry, i));
		} else {
			int error = git_iterator_advance(&entry, i);
			cl_assert(!error || error == GIT_ITEROVER);
		}
	}

	cl_assert(expected[idx].path == NULL);

	git_iterator_free(i);
}