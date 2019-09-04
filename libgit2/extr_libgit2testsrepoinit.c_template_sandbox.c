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
struct TYPE_5__ {char const* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 char* cl_fixture (char const*) ; 
 int /*<<< orphan*/  cl_fixture_sandbox (char const*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char const*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,char const*,char*) ; 
 int /*<<< orphan*/  symlink (char*,char const*) ; 

__attribute__((used)) static const char *template_sandbox(const char *name)
{
	git_buf hooks_path = GIT_BUF_INIT, link_path = GIT_BUF_INIT,
		dotfile_path = GIT_BUF_INIT;
	const char *path = cl_fixture(name);

	cl_fixture_sandbox(name);

	/* create a symlink from link.sample to update.sample if the filesystem
	 * supports it.
	 */

	cl_git_pass(git_buf_joinpath(&hooks_path, name, "hooks"));
	cl_git_pass(git_buf_joinpath(&link_path, hooks_path.ptr, "link.sample"));

#ifdef GIT_WIN32
	cl_git_mkfile(link_path.ptr, "#!/bin/sh\necho hello, world\n");
#else
	cl_must_pass(symlink("update.sample", link_path.ptr));
#endif

	/* create a file starting with a dot */
	cl_git_pass(git_buf_joinpath(&dotfile_path, hooks_path.ptr, ".dotfile"));
	cl_git_mkfile(dotfile_path.ptr, "something\n");
	git_buf_dispose(&dotfile_path);

	git_buf_dispose(&dotfile_path);
	git_buf_dispose(&link_path);
	git_buf_dispose(&hooks_path);

	return path;
}