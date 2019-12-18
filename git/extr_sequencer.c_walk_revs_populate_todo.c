#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
struct todo_list {int /*<<< orphan*/  nr; TYPE_2__ buf; } ;
struct todo_item {int command; int /*<<< orphan*/  offset_in_buf; scalar_t__ arg_len; scalar_t__ arg_offset; struct commit* commit; } ;
struct replay_opts {scalar_t__ action; int /*<<< orphan*/  revs; } ;
struct commit {int dummy; } ;
typedef  enum todo_command { ____Placeholder_todo_command } todo_command ;
struct TYPE_3__ {char* str; } ;

/* Variables and functions */
 scalar_t__ REPLAY_PICK ; 
 int TODO_PICK ; 
 int TODO_REVERT ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct todo_item* append_new_todo (struct todo_list*) ; 
 int error (int /*<<< orphan*/ ) ; 
 int find_commit_subject (char const*,char const**) ; 
 char* get_commit_buffer (struct commit*,int /*<<< orphan*/ *) ; 
 struct commit* get_revision (int /*<<< orphan*/ ) ; 
 scalar_t__ prepare_revs (struct replay_opts*) ; 
 int /*<<< orphan*/  short_commit_name (struct commit*) ; 
 int /*<<< orphan*/  strbuf_addf (TYPE_2__*,char*,char const*,int /*<<< orphan*/ ,int,char const*) ; 
 TYPE_1__* todo_command_info ; 
 int /*<<< orphan*/  unuse_commit_buffer (struct commit*,char const*) ; 

__attribute__((used)) static int walk_revs_populate_todo(struct todo_list *todo_list,
				struct replay_opts *opts)
{
	enum todo_command command = opts->action == REPLAY_PICK ?
		TODO_PICK : TODO_REVERT;
	const char *command_string = todo_command_info[command].str;
	struct commit *commit;

	if (prepare_revs(opts))
		return -1;

	while ((commit = get_revision(opts->revs))) {
		struct todo_item *item = append_new_todo(todo_list);
		const char *commit_buffer = get_commit_buffer(commit, NULL);
		const char *subject;
		int subject_len;

		item->command = command;
		item->commit = commit;
		item->arg_offset = 0;
		item->arg_len = 0;
		item->offset_in_buf = todo_list->buf.len;
		subject_len = find_commit_subject(commit_buffer, &subject);
		strbuf_addf(&todo_list->buf, "%s %s %.*s\n", command_string,
			short_commit_name(commit), subject_len, subject);
		unuse_commit_buffer(commit, commit_buffer);
	}

	if (!todo_list->nr)
		return error(_("empty commit set passed"));

	return 0;
}