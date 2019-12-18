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
struct repository {int dummy; } ;

/* Variables and functions */
 struct todo_list TODO_LIST_INIT ; 
 char* _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edit_todo_list_advice ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rebase_path_todo () ; 
 int /*<<< orphan*/  rebase_path_todo_backup () ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strbuf_read_file_or_whine (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int todo_list_check (struct todo_list*,struct todo_list*) ; 
 int todo_list_parse_insn_buffer (struct repository*,int /*<<< orphan*/ ,struct todo_list*) ; 
 int /*<<< orphan*/  todo_list_release (struct todo_list*) ; 

int check_todo_list_from_file(struct repository *r)
{
	struct todo_list old_todo = TODO_LIST_INIT, new_todo = TODO_LIST_INIT;
	int res = 0;

	if (strbuf_read_file_or_whine(&new_todo.buf, rebase_path_todo()) < 0) {
		res = -1;
		goto out;
	}

	if (strbuf_read_file_or_whine(&old_todo.buf, rebase_path_todo_backup()) < 0) {
		res = -1;
		goto out;
	}

	res = todo_list_parse_insn_buffer(r, old_todo.buf.buf, &old_todo);
	if (!res)
		res = todo_list_parse_insn_buffer(r, new_todo.buf.buf, &new_todo);
	if (!res)
		res = todo_list_check(&old_todo, &new_todo);
	if (res)
		fprintf(stderr, _(edit_todo_list_advice));
out:
	todo_list_release(&old_todo);
	todo_list_release(&new_todo);

	return res;
}