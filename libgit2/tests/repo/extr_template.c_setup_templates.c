#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_fixture_sandbox (char*) ; 
 int /*<<< orphan*/  cl_git_mkfile (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clar_sandbox_path () ; 
 int /*<<< orphan*/  create_tmp_global_config (char*,char*,int /*<<< orphan*/ ) ; 
 char const* fixture_templates ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_join3 (TYPE_1__*,char,char const*,char*,char*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  p_rename (char*,char const*) ; 
 int /*<<< orphan*/  p_symlink (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void setup_templates(const char *name, bool setup_globally)
{
	git_buf path = GIT_BUF_INIT;

	cl_fixture_sandbox("template");
	if (strcmp(name, "template"))
		cl_must_pass(p_rename("template", name));

	fixture_templates = name;

	/*
	 * Create a symlink from link.sample to update.sample if the filesystem
	 * supports it.
	 */
	cl_git_pass(git_buf_join3(&path, '/', name, "hooks", "link.sample"));
#ifdef GIT_WIN32
	cl_git_mkfile(path.ptr, "#!/bin/sh\necho hello, world\n");
#else
	cl_must_pass(p_symlink("update.sample", path.ptr));
#endif

	git_buf_clear(&path);

	/* Create a file starting with a dot */
	cl_git_pass(git_buf_join3(&path, '/', name, "hooks", ".dotfile"));
	cl_git_mkfile(path.ptr, "something\n");

	git_buf_clear(&path);

	if (setup_globally) {
		cl_git_pass(git_buf_joinpath(&path, clar_sandbox_path(), name));
		create_tmp_global_config("tmp_global_path", "init.templatedir", path.ptr);
	}

	git_buf_dispose(&path);
}