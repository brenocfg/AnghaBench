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
typedef  int /*<<< orphan*/  git_diff_driver ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_FILTER_BYTES_TO_CHECK_NUL ; 
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_attach_notowned (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ git_buf_text_contains_nul (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  min (size_t,int /*<<< orphan*/ ) ; 

int git_diff_driver_content_is_binary(
	git_diff_driver *driver, const char *content, size_t content_len)
{
	git_buf search = GIT_BUF_INIT;

	GIT_UNUSED(driver);

	git_buf_attach_notowned(&search, content,
		min(content_len, GIT_FILTER_BYTES_TO_CHECK_NUL));

	/* TODO: provide encoding / binary detection callbacks that can
	 * be UTF-8 aware, etc.  For now, instead of trying to be smart,
	 * let's just use the simple NUL-byte detection that core git uses.
	 */

	/* previously was: if (git_buf_text_is_binary(&search)) */
	if (git_buf_text_contains_nul(&search))
		return 1;

	return 0;
}