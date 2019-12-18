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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int GIT_PASSTHROUGH ; 
 int /*<<< orphan*/  cl_assert_equal_b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  expected_commit_content ; 
 int /*<<< orphan*/  git_buf_is_allocated (int /*<<< orphan*/ *) ; 

int signing_cb_passthrough(
	git_buf *signature,
	git_buf *signature_field,
	const char *commit_content,
	void *payload)
{
	cl_assert_equal_b(false, git_buf_is_allocated(signature));
	cl_assert_equal_b(false, git_buf_is_allocated(signature_field));
	cl_assert_equal_s(expected_commit_content, commit_content);
	cl_assert_equal_p(NULL, payload);
	return GIT_PASSTHROUGH;
}