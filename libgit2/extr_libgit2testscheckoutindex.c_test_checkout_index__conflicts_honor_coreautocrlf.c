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

/* Variables and functions */

void test_checkout_index__conflicts_honor_coreautocrlf(void)
{
#ifdef GIT_WIN32
	git_index *index;
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_buf conflicting_buf = GIT_BUF_INIT;

	cl_git_pass(p_unlink("./testrepo/.gitattributes"));
	cl_repo_set_bool(g_repo, "core.autocrlf", true);

	cl_git_pass(git_repository_index(&index, g_repo));

	add_conflict(index, "conflicting.txt");
	cl_git_pass(git_index_write(index));

	cl_git_pass(git_checkout_index(g_repo, NULL, &opts));

	cl_git_pass(git_futils_readbuffer(&conflicting_buf, "testrepo/conflicting.txt"));
	cl_assert(strcmp(conflicting_buf.ptr,
		"<<<<<<< ours\r\n"
		"this file is changed in master and branch\r\n"
		"=======\r\n"
		"this file is changed in branch and master\r\n"
		">>>>>>> theirs\r\n") == 0);
	git_buf_dispose(&conflicting_buf);

	git_index_free(index);
#endif
}