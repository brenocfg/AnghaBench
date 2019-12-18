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
struct column_options {char* indent; int padding; } ;
struct cmdnames {int cnt; TYPE_1__** names; } ;
typedef  int /*<<< orphan*/  copts ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int COL_ENABLED ; 
 unsigned int COL_ENABLE_MASK ; 
 struct string_list STRING_LIST_INIT_NODUP ; 
 int /*<<< orphan*/  memset (struct column_options*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_columns (struct string_list*,unsigned int,struct column_options*) ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pretty_print_cmdnames(struct cmdnames *cmds, unsigned int colopts)
{
	struct string_list list = STRING_LIST_INIT_NODUP;
	struct column_options copts;
	int i;

	for (i = 0; i < cmds->cnt; i++)
		string_list_append(&list, cmds->names[i]->name);
	/*
	 * always enable column display, we only consult column.*
	 * about layout strategy and stuff
	 */
	colopts = (colopts & ~COL_ENABLE_MASK) | COL_ENABLED;
	memset(&copts, 0, sizeof(copts));
	copts.indent = "  ";
	copts.padding = 2;
	print_columns(&list, colopts, &copts);
	string_list_clear(&list, 0);
}