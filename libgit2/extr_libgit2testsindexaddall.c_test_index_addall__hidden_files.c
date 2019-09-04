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
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/ *) ; 

void test_index_addall__hidden_files(void)
{
	git_index *index;

	GIT_UNUSED(index);

#ifdef GIT_WIN32
	addall_create_test_repo(true);

	cl_git_pass(git_repository_index(&index, g_repo));

	cl_git_pass(git_index_add_all(index, NULL, 0, NULL, NULL));
	cl_git_pass(git_index_write(index));
	check_stat_data(index, TEST_DIR "/file.bar", true);
	check_status(g_repo, 2, 0, 0, 0, 0, 0, 1, 0);

	cl_git_mkfile(TEST_DIR "/file.zzz", "yet another one");
	cl_git_mkfile(TEST_DIR "/more.zzz", "yet another one");
	cl_git_mkfile(TEST_DIR "/other.zzz", "yet another one");

	check_status(g_repo, 2, 0, 0, 3, 0, 0, 1, 0);

	cl_git_pass(git_win32__set_hidden(TEST_DIR "/file.zzz", true));
	cl_git_pass(git_win32__set_hidden(TEST_DIR "/more.zzz", true));
	cl_git_pass(git_win32__set_hidden(TEST_DIR "/other.zzz", true));

	check_status(g_repo, 2, 0, 0, 3, 0, 0, 1, 0);

	cl_git_pass(git_index_add_all(index, NULL, 0, NULL, NULL));
	cl_git_pass(git_index_write(index));
	check_stat_data(index, TEST_DIR "/file.bar", true);
	check_status(g_repo, 5, 0, 0, 0, 0, 0, 1, 0);

	git_index_free(index);
#endif
}