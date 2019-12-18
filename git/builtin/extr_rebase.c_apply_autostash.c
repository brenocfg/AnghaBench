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
struct strbuf {char const* buf; } ;
struct rebase_options {int dummy; } ;
struct child_process {int git_cmd; int no_stderr; int no_stdout; int no_stdin; int /*<<< orphan*/  args; } ;
struct argv_array {int /*<<< orphan*/  argv; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  RUN_GIT_CMD ; 
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_pushl (struct argv_array*,char*,char*,char const*,char*,...) ; 
 int error (char*,char const*) ; 
 int /*<<< orphan*/  file_exists (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ read_one (char const*,struct strbuf*) ; 
 int /*<<< orphan*/  run_command (struct child_process*) ; 
 scalar_t__ run_command_v_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* state_dir_path (char*,struct rebase_options*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int apply_autostash(struct rebase_options *opts)
{
	const char *path = state_dir_path("autostash", opts);
	struct strbuf autostash = STRBUF_INIT;
	struct child_process stash_apply = CHILD_PROCESS_INIT;

	if (!file_exists(path))
		return 0;

	if (read_one(path, &autostash))
		return error(_("Could not read '%s'"), path);
	/* Ensure that the hash is not mistaken for a number */
	strbuf_addstr(&autostash, "^0");
	argv_array_pushl(&stash_apply.args,
			 "stash", "apply", autostash.buf, NULL);
	stash_apply.git_cmd = 1;
	stash_apply.no_stderr = stash_apply.no_stdout =
		stash_apply.no_stdin = 1;
	if (!run_command(&stash_apply))
		printf(_("Applied autostash.\n"));
	else {
		struct argv_array args = ARGV_ARRAY_INIT;
		int res = 0;

		argv_array_pushl(&args,
				 "stash", "store", "-m", "autostash", "-q",
				 autostash.buf, NULL);
		if (run_command_v_opt(args.argv, RUN_GIT_CMD))
			res = error(_("Cannot store %s"), autostash.buf);
		argv_array_clear(&args);
		strbuf_release(&autostash);
		if (res)
			return res;

		fprintf(stderr,
			_("Applying autostash resulted in conflicts.\n"
			  "Your changes are safe in the stash.\n"
			  "You can run \"git stash pop\" or \"git stash drop\" "
			  "at any time.\n"));
	}

	strbuf_release(&autostash);
	return 0;
}