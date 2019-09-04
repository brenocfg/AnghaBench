#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct todo_list {TYPE_1__ buf; } ;
struct string_list {int dummy; } ;
struct replay_opts {int dummy; } ;
struct argv_array {int /*<<< orphan*/  argv; int /*<<< orphan*/  argc; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  BUG (char*) ; 
 struct todo_list TODO_LIST_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_clear (struct argv_array*) ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char const*) ; 
 int /*<<< orphan*/  argv_array_pushl (struct argv_array*,char*,char*,int /*<<< orphan*/ *) ; 
 int complete_action (int /*<<< orphan*/ ,struct replay_opts*,unsigned int,char*,char const*,char const*,char const*,struct string_list*,unsigned int,struct todo_list*) ; 
 int /*<<< orphan*/  discard_cache () ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_revision_ranges (char const*,char const*,char const**,char**,char**) ; 
 scalar_t__ init_basic_state (struct replay_opts*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  parse_strategy_opts (struct replay_opts*,char*) ; 
 int /*<<< orphan*/  path_squash_onto () ; 
 scalar_t__ prepare_branch_to_be_rebased (struct replay_opts*,char const*) ; 
 int sequencer_make_script (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  the_repository ; 
 scalar_t__ todo_list_parse_insn_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct todo_list*) ; 
 int /*<<< orphan*/  todo_list_release (struct todo_list*) ; 
 int /*<<< orphan*/  write_file (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int do_interactive_rebase(struct replay_opts *opts, unsigned flags,
				 const char *switch_to, const char *upstream,
				 const char *onto, const char *onto_name,
				 const char *squash_onto, const char *head_name,
				 const char *restrict_revision, char *raw_strategies,
				 struct string_list *commands, unsigned autosquash)
{
	int ret;
	const char *head_hash = NULL;
	char *revisions = NULL, *shortrevisions = NULL;
	struct argv_array make_script_args = ARGV_ARRAY_INIT;
	struct todo_list todo_list = TODO_LIST_INIT;

	if (prepare_branch_to_be_rebased(opts, switch_to))
		return -1;

	if (get_revision_ranges(upstream, onto, &head_hash,
				&revisions, &shortrevisions))
		return -1;

	if (raw_strategies)
		parse_strategy_opts(opts, raw_strategies);

	if (init_basic_state(opts, head_name, onto, head_hash)) {
		free(revisions);
		free(shortrevisions);

		return -1;
	}

	if (!upstream && squash_onto)
		write_file(path_squash_onto(), "%s\n", squash_onto);

	argv_array_pushl(&make_script_args, "", revisions, NULL);
	if (restrict_revision)
		argv_array_push(&make_script_args, restrict_revision);

	ret = sequencer_make_script(the_repository, &todo_list.buf,
				    make_script_args.argc, make_script_args.argv,
				    flags);

	if (ret)
		error(_("could not generate todo list"));
	else {
		discard_cache();
		if (todo_list_parse_insn_buffer(the_repository, todo_list.buf.buf,
						&todo_list))
			BUG("unusable todo list");

		ret = complete_action(the_repository, opts, flags, shortrevisions, onto_name,
				      onto, head_hash, commands, autosquash, &todo_list);
	}

	free(revisions);
	free(shortrevisions);
	todo_list_release(&todo_list);
	argv_array_clear(&make_script_args);

	return ret;
}