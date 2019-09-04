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
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  cfg ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_string_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

void test_config_include__ordering(void)
{
	cl_git_mkfile("included", "[foo \"bar\"]\nbaz = hurrah\nfrotz = hiya");
	cl_git_mkfile("including",
		      "[foo \"bar\"]\nfrotz = hello\n"
		      "[include]\npath = included\n"
		      "[foo \"bar\"]\nbaz = huzzah\n");

	cl_git_pass(git_config_open_ondisk(&cfg, "including"));

	cl_git_pass(git_config_get_string_buf(&buf, cfg, "foo.bar.frotz"));
	cl_assert_equal_s("hiya", git_buf_cstr(&buf));
	git_buf_clear(&buf);
	cl_git_pass(git_config_get_string_buf(&buf, cfg, "foo.bar.baz"));
	cl_assert_equal_s("huzzah", git_buf_cstr(&buf));

	cl_git_pass(p_unlink("included"));
	cl_git_pass(p_unlink("including"));
}