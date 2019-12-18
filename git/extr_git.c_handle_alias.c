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
struct TYPE_3__ {char const** argv; } ;
struct child_process {int use_shell; char* trace2_child_class; TYPE_1__ args; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  COPY_ARRAY (char const**,char const**,int) ; 
 int /*<<< orphan*/  MOVE_ARRAY (char const**,char const**,int) ; 
 int /*<<< orphan*/  REALLOC_ARRAY (char const**,int) ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* alias_lookup (char const*) ; 
 int /*<<< orphan*/  argv_array_push (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  argv_array_pushv (TYPE_1__*,char const**) ; 
 int /*<<< orphan*/  commit_pager_choice () ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char const*,char*) ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char*) ; 
 int handle_options (char const***,int*,int*) ; 
 int run_command (struct child_process*) ; 
 int /*<<< orphan*/  setup_git_directory_gently (int*) ; 
 int split_cmdline (char*,char const***) ; 
 char* split_cmdline_strerror (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  trace2_cmd_alias (char const*,char const**) ; 
 int /*<<< orphan*/  trace2_cmd_list_config () ; 
 int /*<<< orphan*/  trace2_cmd_name (char*) ; 
 int /*<<< orphan*/  trace_argv_printf (char const**,char*,char const*) ; 

__attribute__((used)) static int handle_alias(int *argcp, const char ***argv)
{
	int envchanged = 0, ret = 0, saved_errno = errno;
	int count, option_count;
	const char **new_argv;
	const char *alias_command;
	char *alias_string;

	alias_command = (*argv)[0];
	alias_string = alias_lookup(alias_command);
	if (alias_string) {
		if (*argcp > 1 && !strcmp((*argv)[1], "-h"))
			fprintf_ln(stderr, _("'%s' is aliased to '%s'"),
				   alias_command, alias_string);
		if (alias_string[0] == '!') {
			struct child_process child = CHILD_PROCESS_INIT;
			int nongit_ok;

			/* Aliases expect GIT_PREFIX, GIT_DIR etc to be set */
			setup_git_directory_gently(&nongit_ok);

			commit_pager_choice();

			child.use_shell = 1;
			child.trace2_child_class = "shell_alias";
			argv_array_push(&child.args, alias_string + 1);
			argv_array_pushv(&child.args, (*argv) + 1);

			trace2_cmd_alias(alias_command, child.args.argv);
			trace2_cmd_list_config();
			trace2_cmd_name("_run_shell_alias_");

			ret = run_command(&child);
			if (ret >= 0)   /* normal exit */
				exit(ret);

			die_errno(_("while expanding alias '%s': '%s'"),
				  alias_command, alias_string + 1);
		}
		count = split_cmdline(alias_string, &new_argv);
		if (count < 0)
			die(_("bad alias.%s string: %s"), alias_command,
			    _(split_cmdline_strerror(count)));
		option_count = handle_options(&new_argv, &count, &envchanged);
		if (envchanged)
			die(_("alias '%s' changes environment variables.\n"
			      "You can use '!git' in the alias to do this"),
			    alias_command);
		MOVE_ARRAY(new_argv - option_count, new_argv, count);
		new_argv -= option_count;

		if (count < 1)
			die(_("empty alias for %s"), alias_command);

		if (!strcmp(alias_command, new_argv[0]))
			die(_("recursive alias: %s"), alias_command);

		trace_argv_printf(new_argv,
				  "trace: alias expansion: %s =>",
				  alias_command);

		REALLOC_ARRAY(new_argv, count + *argcp);
		/* insert after command name */
		COPY_ARRAY(new_argv + count, *argv + 1, *argcp);

		trace2_cmd_alias(alias_command, new_argv);
		trace2_cmd_list_config();

		*argv = new_argv;
		*argcp += count - 1;

		ret = 1;
	}

	errno = saved_errno;

	return ret;
}