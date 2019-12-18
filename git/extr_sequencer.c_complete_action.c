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
struct strbuf {scalar_t__ len; int /*<<< orphan*/  buf; } ;
struct todo_list {struct strbuf buf; } ;
struct todo_item {scalar_t__ offset_in_buf; scalar_t__ flags; scalar_t__ arg_offset; scalar_t__ arg_len; int /*<<< orphan*/ * commit; int /*<<< orphan*/  command; } ;
struct string_list {scalar_t__ nr; } ;
struct repository {int dummy; } ;
struct replay_opts {scalar_t__ allow_ff; } ;
struct object_id {int dummy; } ;
struct TYPE_2__ {struct object_id oid; } ;
struct commit {TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_ABBREV ; 
 struct todo_list TODO_LIST_INIT ; 
 unsigned int TODO_LIST_SHORTEN_IDS ; 
 int /*<<< orphan*/  TODO_NOOP ; 
 char* _ (char*) ; 
 struct todo_item* append_new_todo (struct todo_list*) ; 
 int /*<<< orphan*/  apply_autostash (struct replay_opts*) ; 
 scalar_t__ checkout_onto (struct repository*,struct replay_opts*,char const*,struct object_id*,char const*) ; 
 scalar_t__ count_commands (struct todo_list*) ; 
 int edit_todo_list (struct repository*,struct todo_list*,struct todo_list*,char const*,char const*,unsigned int) ; 
 char* edit_todo_list_advice ; 
 int error (char*) ; 
 int error_errno (char*,char const*) ; 
 char* find_unique_abbrev (struct object_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 char* rebase_path_todo () ; 
 scalar_t__ require_clean_work_tree (struct repository*,char*,char*,int,int) ; 
 int sequencer_continue (struct repository*,struct replay_opts*) ; 
 int /*<<< orphan*/  sequencer_remove_state (struct replay_opts*) ; 
 scalar_t__ skip_unnecessary_picks (struct repository*,struct todo_list*,struct object_id*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  todo_list_add_exec_commands (struct todo_list*,struct string_list*) ; 
 scalar_t__ todo_list_check (struct todo_list*,struct todo_list*) ; 
 scalar_t__ todo_list_parse_insn_buffer (struct repository*,int /*<<< orphan*/ ,struct todo_list*) ; 
 scalar_t__ todo_list_rearrange_squash (struct todo_list*) ; 
 int /*<<< orphan*/  todo_list_release (struct todo_list*) ; 
 scalar_t__ todo_list_write_to_file (struct repository*,struct todo_list*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,unsigned int) ; 

int complete_action(struct repository *r, struct replay_opts *opts, unsigned flags,
		    const char *shortrevisions, const char *onto_name,
		    struct commit *onto, const char *orig_head,
		    struct string_list *commands, unsigned autosquash,
		    struct todo_list *todo_list)
{
	const char *shortonto, *todo_file = rebase_path_todo();
	struct todo_list new_todo = TODO_LIST_INIT;
	struct strbuf *buf = &todo_list->buf;
	struct object_id oid = onto->object.oid;
	int res;

	shortonto = find_unique_abbrev(&oid, DEFAULT_ABBREV);

	if (buf->len == 0) {
		struct todo_item *item = append_new_todo(todo_list);
		item->command = TODO_NOOP;
		item->commit = NULL;
		item->arg_len = item->arg_offset = item->flags = item->offset_in_buf = 0;
	}

	if (autosquash && todo_list_rearrange_squash(todo_list))
		return -1;

	if (commands->nr)
		todo_list_add_exec_commands(todo_list, commands);

	if (count_commands(todo_list) == 0) {
		apply_autostash(opts);
		sequencer_remove_state(opts);

		return error(_("nothing to do"));
	}

	res = edit_todo_list(r, todo_list, &new_todo, shortrevisions,
			     shortonto, flags);
	if (res == -1)
		return -1;
	else if (res == -2) {
		apply_autostash(opts);
		sequencer_remove_state(opts);

		return -1;
	} else if (res == -3) {
		apply_autostash(opts);
		sequencer_remove_state(opts);
		todo_list_release(&new_todo);

		return error(_("nothing to do"));
	}

	if (todo_list_parse_insn_buffer(r, new_todo.buf.buf, &new_todo) ||
	    todo_list_check(todo_list, &new_todo)) {
		fprintf(stderr, _(edit_todo_list_advice));
		checkout_onto(r, opts, onto_name, &onto->object.oid, orig_head);
		todo_list_release(&new_todo);

		return -1;
	}

	if (opts->allow_ff && skip_unnecessary_picks(r, &new_todo, &oid)) {
		todo_list_release(&new_todo);
		return error(_("could not skip unnecessary pick commands"));
	}

	if (todo_list_write_to_file(r, &new_todo, todo_file, NULL, NULL, -1,
				    flags & ~(TODO_LIST_SHORTEN_IDS))) {
		todo_list_release(&new_todo);
		return error_errno(_("could not write '%s'"), todo_file);
	}

	todo_list_release(&new_todo);

	if (checkout_onto(r, opts, onto_name, &oid, orig_head))
		return -1;

	if (require_clean_work_tree(r, "rebase", "", 1, 1))
		return -1;

	return sequencer_continue(r, opts);
}