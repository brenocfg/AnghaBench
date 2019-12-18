#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_patch ;
typedef  int /*<<< orphan*/  git_diff_options ;
struct TYPE_8__ {char* ptr; unsigned int size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,unsigned int) ; 
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 int git_apply__patch (TYPE_1__*,char**,unsigned int*,char*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_buffers (int /*<<< orphan*/ **,char*,unsigned int,char const*,char*,unsigned int,char const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_patch_to_buf (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int apply_gitbuf(
	const git_buf *old,
	const char *oldname,
	const git_buf *new,
	const char *newname,
	const char *patch_expected,
	const git_diff_options *diff_opts)
{
	git_patch *patch;
	git_buf result = GIT_BUF_INIT;
	git_buf patchbuf = GIT_BUF_INIT;
	char *filename;
	unsigned int mode;
	int error;

	cl_git_pass(git_patch_from_buffers(&patch,
		old ? old->ptr : NULL, old ? old->size : 0,
		oldname,
		new ? new->ptr : NULL, new ? new->size : 0,
		newname,
		diff_opts));

	if (patch_expected) {
		cl_git_pass(git_patch_to_buf(&patchbuf, patch));
		cl_assert_equal_s(patch_expected, patchbuf.ptr);
	}

	error = git_apply__patch(&result, &filename, &mode, old ? old->ptr : NULL, old ? old->size : 0, patch, NULL);

	if (error == 0 && new == NULL) {
		cl_assert_equal_i(0, result.size);
		cl_assert_equal_p(NULL, filename);
		cl_assert_equal_i(0, mode);
	}
	else if (error == 0) {
		cl_assert_equal_s(new->ptr, result.ptr);
		cl_assert_equal_s(newname ? newname : oldname, filename);
		cl_assert_equal_i(0100644, mode);
	}

	git__free(filename);
	git_buf_dispose(&result);
	git_buf_dispose(&patchbuf);
	git_patch_free(patch);

	return error;
}