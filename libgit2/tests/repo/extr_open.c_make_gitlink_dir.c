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
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_MKDIR_VERIFY_DIR ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,char const*,char*) ; 
 int /*<<< orphan*/  git_futils_mkdir (char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void make_gitlink_dir(const char *dir, const char *linktext)
{
	git_buf path = GIT_BUF_INIT;

	cl_git_pass(git_futils_mkdir(dir, 0777, GIT_MKDIR_VERIFY_DIR));
	cl_git_pass(git_buf_joinpath(&path, dir, ".git"));
	cl_git_rewritefile(path.ptr, linktext);
	git_buf_dispose(&path);
}