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
typedef  int /*<<< orphan*/  git_indexer ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clar_sandbox_path () ; 
 int /*<<< orphan*/  find_tmp_file_recurs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_indexer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_indexer_new (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void test_pack_indexer__no_tmp_files(void)
{
	git_indexer *idx = NULL;
	git_buf path = GIT_BUF_INIT;
	git_buf first_tmp_file = GIT_BUF_INIT;

	/* Precondition: there are no temporary files. */
	cl_git_pass(git_buf_sets(&path, clar_sandbox_path()));
	cl_git_pass(find_tmp_file_recurs(&first_tmp_file, &path));
	git_buf_dispose(&path);
	cl_assert(git_buf_len(&first_tmp_file) == 0);

	cl_git_pass(git_indexer_new(&idx, ".", 0, NULL, NULL));
	git_indexer_free(idx);

	cl_git_pass(git_buf_sets(&path, clar_sandbox_path()));
	cl_git_pass(find_tmp_file_recurs(&first_tmp_file, &path));
	git_buf_dispose(&path);
	cl_assert(git_buf_len(&first_tmp_file) == 0);
	git_buf_dispose(&first_tmp_file);
}