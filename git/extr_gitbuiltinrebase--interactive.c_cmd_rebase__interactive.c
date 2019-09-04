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
struct replay_opts {unsigned int allow_ff; unsigned int allow_empty_message; unsigned int signoff; char const* strategy; unsigned int reschedule_failed_exec; int allow_empty; int /*<<< orphan*/  gpg_sign; int /*<<< orphan*/  action; int /*<<< orphan*/  allow_rerere_auto; int /*<<< orphan*/  verbose; } ;
struct option {char member_1; char* member_2; intptr_t member_8; int /*<<< orphan*/ * member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_0; } ;
struct child_process {int git_cmd; int /*<<< orphan*/  args; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,int) ; 
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  N_ (char*) ; 
 int /*<<< orphan*/  OPTION_STRING ; 
 struct option OPT_BOOL (int /*<<< orphan*/ ,char*,...) ; 
 struct option OPT_CMDMODE (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ,int) ; 
 struct option OPT_END () ; 
 struct option OPT_RERERE_AUTOUPDATE (int /*<<< orphan*/ *) ; 
 struct option OPT_STRING (int /*<<< orphan*/ ,char*,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct option OPT__VERBOSE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_OPT_KEEP_ARGV0 ; 
 int /*<<< orphan*/  PARSE_OPT_OPTARG ; 
 int /*<<< orphan*/  REPLAY_INTERACTIVE_REBASE ; 
 struct replay_opts REPLAY_OPTS_INIT ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 unsigned int TODO_LIST_ABBREVIATE_CMDS ; 
 unsigned int TODO_LIST_KEEP_EMPTY ; 
 unsigned int TODO_LIST_REBASE_COUSINS ; 
 unsigned int TODO_LIST_REBASE_MERGES ; 
 unsigned int TODO_LIST_SHORTEN_IDS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int add_exec_commands (struct string_list*) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  builtin_rebase_interactive_usage ; 
 int check_todo_list_from_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int do_interactive_rebase (struct replay_opts*,unsigned int,char const*,char const*,char const*,char const*,char const*,char const*,char const*,char*,struct string_list*,unsigned int) ; 
 int edit_todo_file (unsigned int) ; 
 int /*<<< orphan*/  git_config_get_bool (char*,int*) ; 
 int parse_options (int,char const**,int /*<<< orphan*/ *,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rearrange_squash_in_todo_file () ; 
 int /*<<< orphan*/  rerere_clear (int /*<<< orphan*/ ,struct string_list*) ; 
 int run_command (struct child_process*) ; 
 int sequencer_continue (int /*<<< orphan*/ ,struct replay_opts*) ; 
 int /*<<< orphan*/  sequencer_init_config (struct replay_opts*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_remove_empty_items (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_split (struct string_list*,char const*,char,int) ; 
 int /*<<< orphan*/  the_repository ; 
 int transform_todo_file (unsigned int) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrdup_or_null (int /*<<< orphan*/ ) ; 

int cmd_rebase__interactive(int argc, const char **argv, const char *prefix)
{
	struct replay_opts opts = REPLAY_OPTS_INIT;
	unsigned flags = 0, keep_empty = 0, rebase_merges = 0, autosquash = 0;
	int abbreviate_commands = 0, rebase_cousins = -1, ret = 0;
	const char *onto = NULL, *onto_name = NULL, *restrict_revision = NULL,
		*squash_onto = NULL, *upstream = NULL, *head_name = NULL,
		*switch_to = NULL, *cmd = NULL;
	struct string_list commands = STRING_LIST_INIT_DUP;
	char *raw_strategies = NULL;
	enum {
		NONE = 0, CONTINUE, SKIP, EDIT_TODO, SHOW_CURRENT_PATCH,
		SHORTEN_OIDS, EXPAND_OIDS, CHECK_TODO_LIST, REARRANGE_SQUASH, ADD_EXEC
	} command = 0;
	struct option options[] = {
		OPT_BOOL(0, "ff", &opts.allow_ff, N_("allow fast-forward")),
		OPT_BOOL(0, "keep-empty", &keep_empty, N_("keep empty commits")),
		OPT_BOOL(0, "allow-empty-message", &opts.allow_empty_message,
			 N_("allow commits with empty messages")),
		OPT_BOOL(0, "rebase-merges", &rebase_merges, N_("rebase merge commits")),
		OPT_BOOL(0, "rebase-cousins", &rebase_cousins,
			 N_("keep original branch points of cousins")),
		OPT_BOOL(0, "autosquash", &autosquash,
			 N_("move commits that begin with squash!/fixup!")),
		OPT_BOOL(0, "signoff", &opts.signoff, N_("sign commits")),
		OPT__VERBOSE(&opts.verbose, N_("be verbose")),
		OPT_CMDMODE(0, "continue", &command, N_("continue rebase"),
			    CONTINUE),
		OPT_CMDMODE(0, "skip", &command, N_("skip commit"), SKIP),
		OPT_CMDMODE(0, "edit-todo", &command, N_("edit the todo list"),
			    EDIT_TODO),
		OPT_CMDMODE(0, "show-current-patch", &command, N_("show the current patch"),
			    SHOW_CURRENT_PATCH),
		OPT_CMDMODE(0, "shorten-ids", &command,
			N_("shorten commit ids in the todo list"), SHORTEN_OIDS),
		OPT_CMDMODE(0, "expand-ids", &command,
			N_("expand commit ids in the todo list"), EXPAND_OIDS),
		OPT_CMDMODE(0, "check-todo-list", &command,
			N_("check the todo list"), CHECK_TODO_LIST),
		OPT_CMDMODE(0, "rearrange-squash", &command,
			N_("rearrange fixup/squash lines"), REARRANGE_SQUASH),
		OPT_CMDMODE(0, "add-exec-commands", &command,
			N_("insert exec commands in todo list"), ADD_EXEC),
		OPT_STRING(0, "onto", &onto, N_("onto"), N_("onto")),
		OPT_STRING(0, "restrict-revision", &restrict_revision,
			   N_("restrict-revision"), N_("restrict revision")),
		OPT_STRING(0, "squash-onto", &squash_onto, N_("squash-onto"),
			   N_("squash onto")),
		OPT_STRING(0, "upstream", &upstream, N_("upstream"),
			   N_("the upstream commit")),
		OPT_STRING(0, "head-name", &head_name, N_("head-name"), N_("head name")),
		{ OPTION_STRING, 'S', "gpg-sign", &opts.gpg_sign, N_("key-id"),
			N_("GPG-sign commits"),
			PARSE_OPT_OPTARG, NULL, (intptr_t) "" },
		OPT_STRING(0, "strategy", &opts.strategy, N_("strategy"),
			   N_("rebase strategy")),
		OPT_STRING(0, "strategy-opts", &raw_strategies, N_("strategy-opts"),
			   N_("strategy options")),
		OPT_STRING(0, "switch-to", &switch_to, N_("switch-to"),
			   N_("the branch or commit to checkout")),
		OPT_STRING(0, "onto-name", &onto_name, N_("onto-name"), N_("onto name")),
		OPT_STRING(0, "cmd", &cmd, N_("cmd"), N_("the command to run")),
		OPT_RERERE_AUTOUPDATE(&opts.allow_rerere_auto),
		OPT_BOOL(0, "reschedule-failed-exec", &opts.reschedule_failed_exec,
			 N_("automatically re-schedule any `exec` that fails")),
		OPT_END()
	};

	sequencer_init_config(&opts);
	git_config_get_bool("rebase.abbreviatecommands", &abbreviate_commands);

	opts.action = REPLAY_INTERACTIVE_REBASE;
	opts.allow_ff = 1;
	opts.allow_empty = 1;

	if (argc == 1)
		usage_with_options(builtin_rebase_interactive_usage, options);

	argc = parse_options(argc, argv, NULL, options,
			builtin_rebase_interactive_usage, PARSE_OPT_KEEP_ARGV0);

	opts.gpg_sign = xstrdup_or_null(opts.gpg_sign);

	flags |= keep_empty ? TODO_LIST_KEEP_EMPTY : 0;
	flags |= abbreviate_commands ? TODO_LIST_ABBREVIATE_CMDS : 0;
	flags |= rebase_merges ? TODO_LIST_REBASE_MERGES : 0;
	flags |= rebase_cousins > 0 ? TODO_LIST_REBASE_COUSINS : 0;
	flags |= command == SHORTEN_OIDS ? TODO_LIST_SHORTEN_IDS : 0;

	if (rebase_cousins >= 0 && !rebase_merges)
		warning(_("--[no-]rebase-cousins has no effect without "
			  "--rebase-merges"));

	if (cmd && *cmd) {
		string_list_split(&commands, cmd, '\n', -1);

		/* rebase.c adds a new line to cmd after every command,
		 * so here the last command is always empty */
		string_list_remove_empty_items(&commands, 0);
	}

	switch (command) {
	case NONE:
		if (!onto && !upstream)
			die(_("a base commit must be provided with --upstream or --onto"));

		ret = do_interactive_rebase(&opts, flags, switch_to, upstream, onto,
					    onto_name, squash_onto, head_name, restrict_revision,
					    raw_strategies, &commands, autosquash);
		break;
	case SKIP: {
		struct string_list merge_rr = STRING_LIST_INIT_DUP;

		rerere_clear(the_repository, &merge_rr);
		/* fallthrough */
	case CONTINUE:
		ret = sequencer_continue(the_repository, &opts);
		break;
	}
	case EDIT_TODO:
		ret = edit_todo_file(flags);
		break;
	case SHOW_CURRENT_PATCH: {
		struct child_process cmd = CHILD_PROCESS_INIT;

		cmd.git_cmd = 1;
		argv_array_pushl(&cmd.args, "show", "REBASE_HEAD", "--", NULL);
		ret = run_command(&cmd);

		break;
	}
	case SHORTEN_OIDS:
	case EXPAND_OIDS:
		ret = transform_todo_file(flags);
		break;
	case CHECK_TODO_LIST:
		ret = check_todo_list_from_file(the_repository);
		break;
	case REARRANGE_SQUASH:
		ret = rearrange_squash_in_todo_file();
		break;
	case ADD_EXEC:
		ret = add_exec_commands(&commands);
		break;
	default:
		BUG("invalid command '%d'", command);
	}

	string_list_clear(&commands, 0);
	return !!ret;
}