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
struct string_list {int dummy; } ;
struct cmdnames {int cnt; TYPE_1__** names; } ;
typedef  int /*<<< orphan*/  other_cmds ;
typedef  int /*<<< orphan*/  main_cmds ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  clean_cmdnames (struct cmdnames*) ; 
 int /*<<< orphan*/  load_command_list (char*,struct cmdnames*,struct cmdnames*) ; 
 int /*<<< orphan*/  memset (struct cmdnames*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,int /*<<< orphan*/ ) ; 

void list_all_other_cmds(struct string_list *list)
{
	struct cmdnames main_cmds, other_cmds;
	int i;

	memset(&main_cmds, 0, sizeof(main_cmds));
	memset(&other_cmds, 0, sizeof(other_cmds));
	load_command_list("git-", &main_cmds, &other_cmds);

	for (i = 0; i < other_cmds.cnt; i++)
		string_list_append(list, other_cmds.names[i]->name);

	clean_cmdnames(&main_cmds);
	clean_cmdnames(&other_cmds);
}