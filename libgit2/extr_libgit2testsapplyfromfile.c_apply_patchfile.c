#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_patch ;
struct TYPE_5__ {unsigned int size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 int git_apply__patch (TYPE_1__*,char**,unsigned int*,char const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_buffer (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int apply_patchfile(
	const char *old,
	size_t old_len,
	const char *new,
	size_t new_len,
	const char *patchfile,
	const char *filename_expected,
	unsigned int mode_expected)
{
	git_patch *patch;
	git_buf result = GIT_BUF_INIT;
	git_buf patchbuf = GIT_BUF_INIT;
	char *filename;
	unsigned int mode;
	int error;

	cl_git_pass(git_patch_from_buffer(&patch, patchfile, strlen(patchfile), NULL));

	error = git_apply__patch(&result, &filename, &mode, old, old_len, patch, NULL);

	if (error == 0) {
		cl_assert_equal_i(new_len, result.size);
		if (new_len)
			cl_assert(memcmp(new, result.ptr, new_len) == 0);

		cl_assert_equal_s(filename_expected, filename);
		cl_assert_equal_i(mode_expected, mode);
	}

	git__free(filename);
	git_buf_dispose(&result);
	git_buf_dispose(&patchbuf);
	git_patch_free(patch);

	return error;
}