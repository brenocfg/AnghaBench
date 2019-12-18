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

/* Variables and functions */
 int /*<<< orphan*/  string_list_remove_empty_items (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_split (struct string_list*,char const*,char,int) ; 

__attribute__((used)) static void split_exec_commands(const char *cmd, struct string_list *commands)
{
	if (cmd && *cmd) {
		string_list_split(commands, cmd, '\n', -1);

		/* rebase.c adds a new line to cmd after every command,
		 * so here the last command is always empty */
		string_list_remove_empty_items(commands, 0);
	}
}