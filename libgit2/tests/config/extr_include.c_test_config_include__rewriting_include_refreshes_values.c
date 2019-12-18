#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 TYPE_1__ buf ; 
 int /*<<< orphan*/  cfg ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_get_string_buf (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

void test_config_include__rewriting_include_refreshes_values(void)
{
	cl_git_mkfile("top-level", "[include]\npath = first\n[include]\npath = second");
	cl_git_mkfile("first", "[first]\nfoo = bar");
	cl_git_mkfile("second", "[second]\nfoo = bar");

	cl_git_pass(git_config_open_ondisk(&cfg, "top-level"));
	cl_git_mkfile("first", "[first]\nother = value");
	cl_git_fail(git_config_get_string_buf(&buf, cfg, "foo.bar"));
	cl_git_pass(git_config_get_string_buf(&buf, cfg, "first.other"));
	cl_assert_equal_s(buf.ptr, "value");

	cl_git_pass(p_unlink("top-level"));
	cl_git_pass(p_unlink("first"));
	cl_git_pass(p_unlink("second"));
}