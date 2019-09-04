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
struct todo_list {int dummy; } ;
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct repository {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 unsigned int TODO_LIST_APPEND_TODO_HELP ; 
 unsigned int TODO_LIST_KEEP_EMPTY ; 
 int /*<<< orphan*/  append_todo_help (unsigned int,int /*<<< orphan*/ ,char const*,char const*,struct strbuf*) ; 
 int /*<<< orphan*/  count_commands (struct todo_list*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  todo_list_to_strbuf (struct repository*,struct todo_list*,struct strbuf*,int,unsigned int) ; 
 int write_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int todo_list_write_to_file(struct repository *r, struct todo_list *todo_list,
			    const char *file, const char *shortrevisions,
			    const char *shortonto, int num, unsigned flags)
{
	int res;
	struct strbuf buf = STRBUF_INIT;

	todo_list_to_strbuf(r, todo_list, &buf, num, flags);
	if (flags & TODO_LIST_APPEND_TODO_HELP)
		append_todo_help(flags & TODO_LIST_KEEP_EMPTY, count_commands(todo_list),
				 shortrevisions, shortonto, &buf);

	res = write_message(buf.buf, buf.len, file, 0);
	strbuf_release(&buf);

	return res;
}