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
struct column_options {char* indent; int padding; } ;
typedef  int /*<<< orphan*/  copts ;

/* Variables and functions */
 unsigned int COL_ENABLED ; 
 unsigned int COL_ROW ; 
 int /*<<< orphan*/  memset (struct column_options*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_columns (struct string_list*,unsigned int,struct column_options*) ; 

__attribute__((used)) static void pretty_print_menus(struct string_list *menu_list)
{
	unsigned int local_colopts = 0;
	struct column_options copts;

	local_colopts = COL_ENABLED | COL_ROW;
	memset(&copts, 0, sizeof(copts));
	copts.indent = "  ";
	copts.padding = 2;
	print_columns(menu_list, local_colopts, &copts);
}