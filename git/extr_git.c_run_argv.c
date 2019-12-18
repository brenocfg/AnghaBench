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
struct string_list_item {int /*<<< orphan*/  string; } ;
struct string_list {int nr; struct string_list_item* items; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct argv_array {int /*<<< orphan*/  argv; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 scalar_t__ ENOENT ; 
 int RUN_CLEAN_ON_EXIT ; 
 int RUN_SILENT_EXEC_FAILURE ; 
 struct strbuf STRBUF_INIT ; 
 struct string_list STRING_LIST_INIT_NODUP ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char const*) ; 
 int /*<<< orphan*/  commit_pager_choice () ; 
 int /*<<< orphan*/  die (char*,char const*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  execv_dashed_external (char const**) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ get_builtin (char const*) ; 
 scalar_t__ get_super_prefix () ; 
 int /*<<< orphan*/  handle_alias (int*,char const***) ; 
 int /*<<< orphan*/  handle_builtin (int,char const**) ; 
 int run_command_v_opt_tr2 (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,char const*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace2_cmd_name (char*) ; 
 int /*<<< orphan*/  trace_argv_printf (int /*<<< orphan*/ ,char*) ; 
 struct string_list_item* unsorted_string_list_lookup (struct string_list*,char const*) ; 

__attribute__((used)) static int run_argv(int *argcp, const char ***argv)
{
	int done_alias = 0;
	struct string_list cmd_list = STRING_LIST_INIT_NODUP;
	struct string_list_item *seen;

	while (1) {
		/*
		 * If we tried alias and futzed with our environment,
		 * it no longer is safe to invoke builtins directly in
		 * general.  We have to spawn them as dashed externals.
		 *
		 * NEEDSWORK: if we can figure out cases
		 * where it is safe to do, we can avoid spawning a new
		 * process.
		 */
		if (!done_alias)
			handle_builtin(*argcp, *argv);
		else if (get_builtin(**argv)) {
			struct argv_array args = ARGV_ARRAY_INIT;
			int i;

			/*
			 * The current process is committed to launching a
			 * child process to run the command named in (**argv)
			 * and exiting.  Log a generic string as the trace2
			 * command verb to indicate this.  Note that the child
			 * process will log the actual verb when it runs.
			 */
			trace2_cmd_name("_run_git_alias_");

			if (get_super_prefix())
				die("%s doesn't support --super-prefix", **argv);

			commit_pager_choice();

			argv_array_push(&args, "git");
			for (i = 0; i < *argcp; i++)
				argv_array_push(&args, (*argv)[i]);

			trace_argv_printf(args.argv, "trace: exec:");

			/*
			 * if we fail because the command is not found, it is
			 * OK to return. Otherwise, we just pass along the status code.
			 */
			i = run_command_v_opt_tr2(args.argv, RUN_SILENT_EXEC_FAILURE |
						  RUN_CLEAN_ON_EXIT, "git_alias");
			if (i >= 0 || errno != ENOENT)
				exit(i);
			die("could not execute builtin %s", **argv);
		}

		/* .. then try the external ones */
		execv_dashed_external(*argv);

		seen = unsorted_string_list_lookup(&cmd_list, *argv[0]);
		if (seen) {
			int i;
			struct strbuf sb = STRBUF_INIT;
			for (i = 0; i < cmd_list.nr; i++) {
				struct string_list_item *item = &cmd_list.items[i];

				strbuf_addf(&sb, "\n  %s", item->string);
				if (item == seen)
					strbuf_addstr(&sb, " <==");
				else if (i == cmd_list.nr - 1)
					strbuf_addstr(&sb, " ==>");
			}
			die(_("alias loop detected: expansion of '%s' does"
			      " not terminate:%s"), cmd_list.items[0].string, sb.buf);
		}

		string_list_append(&cmd_list, *argv[0]);

		/*
		 * It could be an alias -- this works around the insanity
		 * of overriding "git log" with "git show" by having
		 * alias.log = show
		 */
		if (!handle_alias(argcp, argv))
			break;
		done_alias = 1;
	}

	string_list_clear(&cmd_list, 0);

	return done_alias;
}