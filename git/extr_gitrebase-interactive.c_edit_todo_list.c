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
struct TYPE_3__ {scalar_t__ len; int /*<<< orphan*/  buf; } ;
struct todo_list {TYPE_1__ buf; } ;
struct repository {int dummy; } ;

/* Variables and functions */
 unsigned int TODO_LIST_APPEND_TODO_HELP ; 
 unsigned int TODO_LIST_SHORTEN_IDS ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ copy_file (char*,char const*,int) ; 
 int error (int /*<<< orphan*/ ,char const*,char*) ; 
 int error_errno (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ launch_sequence_editor (char const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 char* rebase_path_todo () ; 
 char* rebase_path_todo_backup () ; 
 int /*<<< orphan*/  strbuf_stripspace (TYPE_1__*,int) ; 
 int todo_list_parse_insn_buffer (struct repository*,int /*<<< orphan*/ ,struct todo_list*) ; 
 scalar_t__ todo_list_write_to_file (struct repository*,struct todo_list*,char const*,char const*,char const*,int,unsigned int) ; 

int edit_todo_list(struct repository *r, struct todo_list *todo_list,
		   struct todo_list *new_todo, const char *shortrevisions,
		   const char *shortonto, unsigned flags)
{
	const char *todo_file = rebase_path_todo();
	unsigned initial = shortrevisions && shortonto;

	/* If the user is editing the todo list, we first try to parse
	 * it.  If there is an error, we do not return, because the user
	 * might want to fix it in the first place. */
	if (!initial)
		todo_list_parse_insn_buffer(r, todo_list->buf.buf, todo_list);

	if (todo_list_write_to_file(r, todo_list, todo_file, shortrevisions, shortonto,
				    -1, flags | TODO_LIST_SHORTEN_IDS | TODO_LIST_APPEND_TODO_HELP))
		return error_errno(_("could not write '%s'"), todo_file);

	if (initial && copy_file(rebase_path_todo_backup(), todo_file, 0666))
		return error(_("could not copy '%s' to '%s'."), todo_file,
			     rebase_path_todo_backup());

	if (launch_sequence_editor(todo_file, &new_todo->buf, NULL))
		return -2;

	strbuf_stripspace(&new_todo->buf, 1);
	if (initial && new_todo->buf.len == 0)
		return -3;

	/* For the initial edit, the todo list gets parsed in
	 * complete_action(). */
	if (!initial)
		return todo_list_parse_insn_buffer(r, new_todo->buf.buf, new_todo);

	return 0;
}