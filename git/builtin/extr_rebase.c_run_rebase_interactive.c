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
struct string_list {int dummy; } ;
struct replay_opts {int dummy; } ;
struct rebase_options {scalar_t__ rebase_cousins; int /*<<< orphan*/  cmd; int /*<<< orphan*/  upstream; int /*<<< orphan*/  onto; scalar_t__ root_with_onto; scalar_t__ rebase_merges; scalar_t__ keep_empty; } ;
struct child_process {int git_cmd; int /*<<< orphan*/  args; } ;
typedef  enum action { ____Placeholder_action } action ;

/* Variables and functions */
#define  ACTION_ADD_EXEC 137 
#define  ACTION_CHECK_TODO_LIST 136 
#define  ACTION_CONTINUE 135 
#define  ACTION_EDIT_TODO 134 
#define  ACTION_EXPAND_OIDS 133 
#define  ACTION_NONE 132 
#define  ACTION_REARRANGE_SQUASH 131 
#define  ACTION_SHORTEN_OIDS 130 
#define  ACTION_SHOW_CURRENT_PATCH 129 
#define  ACTION_SKIP 128 
 int /*<<< orphan*/  BUG (char*,int) ; 
 struct child_process CHILD_PROCESS_INIT ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 unsigned int TODO_LIST_ABBREVIATE_CMDS ; 
 unsigned int TODO_LIST_KEEP_EMPTY ; 
 unsigned int TODO_LIST_REBASE_COUSINS ; 
 unsigned int TODO_LIST_REBASE_MERGES ; 
 unsigned int TODO_LIST_ROOT_WITH_ONTO ; 
 unsigned int TODO_LIST_SHORTEN_IDS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int add_exec_commands (struct string_list*) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int check_todo_list_from_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int do_interactive_rebase (struct rebase_options*,unsigned int) ; 
 int edit_todo_file (unsigned int) ; 
 struct replay_opts get_replay_opts (struct rebase_options*) ; 
 int /*<<< orphan*/  git_config_get_bool (char*,int*) ; 
 int rearrange_squash_in_todo_file () ; 
 int /*<<< orphan*/  rerere_clear (int /*<<< orphan*/ ,struct string_list*) ; 
 int run_command (struct child_process*) ; 
 int sequencer_continue (int /*<<< orphan*/ ,struct replay_opts*) ; 
 int /*<<< orphan*/  split_exec_commands (int /*<<< orphan*/ ,struct string_list*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_repository ; 
 int transform_todo_file (unsigned int) ; 

__attribute__((used)) static int run_rebase_interactive(struct rebase_options *opts,
				  enum action command)
{
	unsigned flags = 0;
	int abbreviate_commands = 0, ret = 0;

	git_config_get_bool("rebase.abbreviatecommands", &abbreviate_commands);

	flags |= opts->keep_empty ? TODO_LIST_KEEP_EMPTY : 0;
	flags |= abbreviate_commands ? TODO_LIST_ABBREVIATE_CMDS : 0;
	flags |= opts->rebase_merges ? TODO_LIST_REBASE_MERGES : 0;
	flags |= opts->rebase_cousins > 0 ? TODO_LIST_REBASE_COUSINS : 0;
	flags |= opts->root_with_onto ? TODO_LIST_ROOT_WITH_ONTO : 0;
	flags |= command == ACTION_SHORTEN_OIDS ? TODO_LIST_SHORTEN_IDS : 0;

	switch (command) {
	case ACTION_NONE: {
		if (!opts->onto && !opts->upstream)
			die(_("a base commit must be provided with --upstream or --onto"));

		ret = do_interactive_rebase(opts, flags);
		break;
	}
	case ACTION_SKIP: {
		struct string_list merge_rr = STRING_LIST_INIT_DUP;

		rerere_clear(the_repository, &merge_rr);
	}
		/* fallthrough */
	case ACTION_CONTINUE: {
		struct replay_opts replay_opts = get_replay_opts(opts);

		ret = sequencer_continue(the_repository, &replay_opts);
		break;
	}
	case ACTION_EDIT_TODO:
		ret = edit_todo_file(flags);
		break;
	case ACTION_SHOW_CURRENT_PATCH: {
		struct child_process cmd = CHILD_PROCESS_INIT;

		cmd.git_cmd = 1;
		argv_array_pushl(&cmd.args, "show", "REBASE_HEAD", "--", NULL);
		ret = run_command(&cmd);

		break;
	}
	case ACTION_SHORTEN_OIDS:
	case ACTION_EXPAND_OIDS:
		ret = transform_todo_file(flags);
		break;
	case ACTION_CHECK_TODO_LIST:
		ret = check_todo_list_from_file(the_repository);
		break;
	case ACTION_REARRANGE_SQUASH:
		ret = rearrange_squash_in_todo_file();
		break;
	case ACTION_ADD_EXEC: {
		struct string_list commands = STRING_LIST_INIT_DUP;

		split_exec_commands(opts->cmd, &commands);
		ret = add_exec_commands(&commands);
		string_list_clear(&commands, 0);
		break;
	}
	default:
		BUG("invalid command '%d'", command);
	}

	return ret;
}