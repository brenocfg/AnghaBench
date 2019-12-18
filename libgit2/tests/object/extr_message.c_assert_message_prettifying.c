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
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_message_prettify (int /*<<< orphan*/ *,char*,int,char) ; 

__attribute__((used)) static void assert_message_prettifying(char *expected_output, char *input, int strip_comments)
{
	git_buf prettified_message = GIT_BUF_INIT;

	git_message_prettify(&prettified_message, input, strip_comments, '#');
	cl_assert_equal_s(expected_output, git_buf_cstr(&prettified_message));

	git_buf_dispose(&prettified_message);
}