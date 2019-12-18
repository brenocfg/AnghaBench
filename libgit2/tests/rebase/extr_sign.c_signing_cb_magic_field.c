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
 int GIT_OK ; 
 int /*<<< orphan*/  cl_assert_equal_b (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expected_commit_content ; 
 int /*<<< orphan*/  git_buf_is_allocated (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_set (int /*<<< orphan*/ *,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

int signing_cb_magic_field(
	git_buf *signature,
	git_buf *signature_field,
	const char *commit_content,
	void *payload)
{
	const char *signature_content = "magic word: pretty please";
	const char *signature_field_content = "magicsig";

	cl_assert_equal_b(false, git_buf_is_allocated(signature));
	cl_assert_equal_b(false, git_buf_is_allocated(signature_field));
	cl_assert_equal_s(expected_commit_content, commit_content);
	cl_assert_equal_p(NULL, payload);

	cl_git_pass(git_buf_set(signature, signature_content,
		strlen(signature_content) + 1));
	cl_git_pass(git_buf_set(signature_field, signature_field_content,
		strlen(signature_field_content) + 1));

	return GIT_OK;
}