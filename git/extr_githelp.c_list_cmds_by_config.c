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
struct strbuf {char* buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 scalar_t__ git_config_get_string_const (char*,char const**) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* strchrnul (char const*,char) ; 
 int /*<<< orphan*/  string_list_insert (struct string_list*,char*) ; 
 int /*<<< orphan*/  string_list_remove (struct string_list*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_remove_duplicates (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_sort (struct string_list*) ; 

void list_cmds_by_config(struct string_list *list)
{
	const char *cmd_list;

	if (git_config_get_string_const("completion.commands", &cmd_list))
		return;

	string_list_sort(list);
	string_list_remove_duplicates(list, 0);

	while (*cmd_list) {
		struct strbuf sb = STRBUF_INIT;
		const char *p = strchrnul(cmd_list, ' ');

		strbuf_add(&sb, cmd_list, p - cmd_list);
		if (sb.buf[0] == '-')
			string_list_remove(list, sb.buf + 1, 0);
		else
			string_list_insert(list, sb.buf);
		strbuf_release(&sb);
		while (*p == ' ')
			p++;
		cmd_list = p;
	}
}