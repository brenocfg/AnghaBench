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
typedef  int /*<<< orphan*/  git_index_entry ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (int) ; 

void test_index_bypath__add_hidden(void)
{
	const git_index_entry *entry;
	bool hidden;

	GIT_UNUSED(entry);
	GIT_UNUSED(hidden);

#ifdef GIT_WIN32
	cl_git_mkfile("submod2/hidden_file", "you can't see me");

	cl_git_pass(git_win32__hidden(&hidden, "submod2/hidden_file"));
	cl_assert(!hidden);

	cl_git_pass(git_win32__set_hidden("submod2/hidden_file", true));

	cl_git_pass(git_win32__hidden(&hidden, "submod2/hidden_file"));
	cl_assert(hidden);

	cl_git_pass(git_index_add_bypath(g_idx, "hidden_file"));

	cl_assert(entry = git_index_get_bypath(g_idx, "hidden_file", 0));
	cl_assert_equal_i(GIT_FILEMODE_BLOB, entry->mode);
#endif
}