#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_patch ;
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_6__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_DIFF_FORMAT_PATCH ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_from_buffer (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff_to_buf (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_buffers (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_to_buf (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void test_diff_parse__patch_roundtrip_succeeds(void)
{
	const char buf1[] = "a\n", buf2[] = "b\n";
	git_buf patchbuf = GIT_BUF_INIT, diffbuf = GIT_BUF_INIT;
	git_patch *patch;
	git_diff *diff;

	cl_git_pass(git_patch_from_buffers(&patch, buf1, strlen(buf1), "obj1", buf2, strlen(buf2), "obj2", NULL));
	cl_git_pass(git_patch_to_buf(&patchbuf, patch));

	cl_git_pass(git_diff_from_buffer(&diff, patchbuf.ptr, patchbuf.size));
	cl_git_pass(git_diff_to_buf(&diffbuf, diff, GIT_DIFF_FORMAT_PATCH));

	cl_assert_equal_s(patchbuf.ptr, diffbuf.ptr);

	git_patch_free(patch);
	git_diff_free(diff);
	git_buf_dispose(&patchbuf);
	git_buf_dispose(&diffbuf);
}