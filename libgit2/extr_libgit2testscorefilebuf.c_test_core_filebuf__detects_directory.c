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
typedef  int /*<<< orphan*/  git_filebuf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_EDIRECTORY ; 
 int /*<<< orphan*/  GIT_FILEBUF_INIT ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_filebuf_open (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  p_rmdir (char*) ; 

void test_core_filebuf__detects_directory(void)
{
	git_filebuf file = GIT_FILEBUF_INIT;

	cl_must_pass(p_mkdir("foo", 0777));
	cl_git_fail_with(GIT_EDIRECTORY, git_filebuf_open(&file, "foo", 0, 0666));
	cl_must_pass(p_rmdir("foo"));
}