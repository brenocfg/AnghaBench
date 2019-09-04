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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct child_process {int no_stdin; int no_stderr; int out; int git_cmd; int /*<<< orphan*/  args; int /*<<< orphan*/  env_array; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  PATH_MAX ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,char*,char*,char*,char*,char*,char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 int finish_command (struct child_process*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  is_inside_work_tree () ; 
 int /*<<< orphan*/  prepare_submodule_repo_env (int /*<<< orphan*/ *) ; 
 char* real_path (char*) ; 
 char* real_path_if_valid (char*) ; 
 char* relative_path (char const*,char const*,struct strbuf*) ; 
 scalar_t__ start_command (struct child_process*) ; 
 scalar_t__ starts_with (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strbuf_read (struct strbuf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 char* xgetcwd () ; 
 char* xstrdup (char const*) ; 

const char *get_superproject_working_tree(void)
{
	struct child_process cp = CHILD_PROCESS_INIT;
	struct strbuf sb = STRBUF_INIT;
	const char *one_up = real_path_if_valid("../");
	const char *cwd = xgetcwd();
	const char *ret = NULL;
	const char *subpath;
	int code;
	ssize_t len;

	if (!is_inside_work_tree())
		/*
		 * FIXME:
		 * We might have a superproject, but it is harder
		 * to determine.
		 */
		return NULL;

	if (!one_up)
		return NULL;

	subpath = relative_path(cwd, one_up, &sb);

	prepare_submodule_repo_env(&cp.env_array);
	argv_array_pop(&cp.env_array);

	argv_array_pushl(&cp.args, "--literal-pathspecs", "-C", "..",
			"ls-files", "-z", "--stage", "--full-name", "--",
			subpath, NULL);
	strbuf_reset(&sb);

	cp.no_stdin = 1;
	cp.no_stderr = 1;
	cp.out = -1;
	cp.git_cmd = 1;

	if (start_command(&cp))
		die(_("could not start ls-files in .."));

	len = strbuf_read(&sb, cp.out, PATH_MAX);
	close(cp.out);

	if (starts_with(sb.buf, "160000")) {
		int super_sub_len;
		int cwd_len = strlen(cwd);
		char *super_sub, *super_wt;

		/*
		 * There is a superproject having this repo as a submodule.
		 * The format is <mode> SP <hash> SP <stage> TAB <full name> \0,
		 * We're only interested in the name after the tab.
		 */
		super_sub = strchr(sb.buf, '\t') + 1;
		super_sub_len = strlen(super_sub);

		if (super_sub_len > cwd_len ||
		    strcmp(&cwd[cwd_len - super_sub_len], super_sub))
			BUG("returned path string doesn't match cwd?");

		super_wt = xstrdup(cwd);
		super_wt[cwd_len - super_sub_len] = '\0';

		ret = real_path(super_wt);
		free(super_wt);
	}
	strbuf_release(&sb);

	code = finish_command(&cp);

	if (code == 128)
		/* '../' is not a git repository */
		return NULL;
	if (code == 0 && len == 0)
		/* There is an unrelated git repository at '../' */
		return NULL;
	if (code)
		die(_("ls-tree returned unexpected return code %d"), code);

	return ret;
}