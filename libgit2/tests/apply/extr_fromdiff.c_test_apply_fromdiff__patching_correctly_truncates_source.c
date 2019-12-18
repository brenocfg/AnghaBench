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
typedef  int /*<<< orphan*/  git_patch ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_EAPPLYFAIL ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 int /*<<< orphan*/  git_apply__patch (int /*<<< orphan*/ *,char**,unsigned int*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_buffers (int /*<<< orphan*/ **,char*,int,char*,char*,int,char*,int /*<<< orphan*/ *) ; 

void test_apply_fromdiff__patching_correctly_truncates_source(void)
{
	git_buf original = GIT_BUF_INIT, patched = GIT_BUF_INIT;
	git_patch *patch;
	unsigned int mode;
	char *path;

	cl_git_pass(git_patch_from_buffers(&patch,
					   "foo\nbar", 7, "file.txt",
					   "foo\nfoo", 7, "file.txt", NULL));

	/*
	 * Previously, we would fail to correctly truncate the source buffer if
	 * the source has more than one line and ends with a non-newline
	 * character. In the following call, we thus truncate the source string
	 * in the middle of the second line. Without the bug fixed, we would
	 * successfully apply the patch to the source and return success. With
	 * the overflow being fixed, we should return an error.
	 */
	cl_git_fail_with(GIT_EAPPLYFAIL,
			 git_apply__patch(&patched, &path, &mode,
					  "foo\nbar\n", 5, patch, NULL));

	/* Verify that the patch succeeds if we do not truncate */
	cl_git_pass(git_apply__patch(&patched, &path, &mode,
				     "foo\nbar\n", 7, patch, NULL));

	git_buf_dispose(&original);
	git_buf_dispose(&patched);
	git_patch_free(patch);
	git__free(path);
}