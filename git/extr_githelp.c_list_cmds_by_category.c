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
typedef  int uint32_t ;
struct string_list {int dummy; } ;
struct cmdname_help {int category; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct cmdname_help*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__* category_names ; 
 struct cmdname_help* command_list ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  drop_prefix (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,int /*<<< orphan*/ ) ; 

void list_cmds_by_category(struct string_list *list,
			   const char *cat)
{
	int i, n = ARRAY_SIZE(command_list);
	uint32_t cat_id = 0;

	for (i = 0; category_names[i]; i++) {
		if (!strcmp(cat, category_names[i])) {
			cat_id = 1UL << i;
			break;
		}
	}
	if (!cat_id)
		die(_("unsupported command listing type '%s'"), cat);

	for (i = 0; i < n; i++) {
		struct cmdname_help *cmd = command_list + i;

		if (!(cmd->category & cat_id))
			continue;
		string_list_append(list, drop_prefix(cmd->name, cmd->category));
	}
}