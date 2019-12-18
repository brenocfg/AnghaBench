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
struct string_list {int nr; TYPE_1__* items; } ;
struct cmdname_help {char* name; int category; int /*<<< orphan*/  help; } ;
struct TYPE_2__ {char* string; int /*<<< orphan*/  util; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ARRAY (struct cmdname_help*,int) ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  free (struct cmdname_help*) ; 
 int /*<<< orphan*/  get_alias ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,struct string_list*) ; 
 int /*<<< orphan*/  list_all_other_cmds (struct string_list*) ; 
 int /*<<< orphan*/  main_categories ; 
 int /*<<< orphan*/  print_cmd_by_category (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  print_command_list (struct cmdname_help*,int,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  printf_ln (char*) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int) ; 
 int /*<<< orphan*/  string_list_sort (struct string_list*) ; 
 size_t strlen (char*) ; 

void list_all_cmds_help(void)
{
	struct string_list others = STRING_LIST_INIT_DUP;
	struct string_list alias_list = STRING_LIST_INIT_DUP;
	struct cmdname_help *aliases;
	int i, longest;

	printf_ln(_("See 'git help <command>' to read about a specific subcommand"));
	print_cmd_by_category(main_categories, &longest);

	list_all_other_cmds(&others);
	if (others.nr)
		printf("\n%s\n", _("External commands"));
	for (i = 0; i < others.nr; i++)
		printf("   %s\n", others.items[i].string);
	string_list_clear(&others, 0);

	git_config(get_alias, &alias_list);
	string_list_sort(&alias_list);

	for (i = 0; i < alias_list.nr; i++) {
		size_t len = strlen(alias_list.items[i].string);
		if (longest < len)
			longest = len;
	}

	if (alias_list.nr) {
		printf("\n%s\n", _("Command aliases"));
		ALLOC_ARRAY(aliases, alias_list.nr + 1);
		for (i = 0; i < alias_list.nr; i++) {
			aliases[i].name = alias_list.items[i].string;
			aliases[i].help = alias_list.items[i].util;
			aliases[i].category = 1;
		}
		aliases[alias_list.nr].name = NULL;
		print_command_list(aliases, 1, longest);
		free(aliases);
	}
	string_list_clear(&alias_list, 1);
}