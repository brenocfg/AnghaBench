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
struct partedit_item {int indentation; char* name; char* type; char* mountpoint; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  chtype ;
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int /*<<< orphan*/  A_NORMAL ; 
 int /*<<< orphan*/  HN_AUTOSCALE ; 
 int /*<<< orphan*/  HN_DECIMAL ; 
 int MARGIN ; 
 int /*<<< orphan*/  dlg_print_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  humanize_number (char*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_attr ; 
 int /*<<< orphan*/  item_selected_attr ; 
 int /*<<< orphan*/  wattrset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
print_partedit_item(WINDOW *partitions, struct partedit_item *items,
    int item, int nscroll, int selected)
{
	chtype attr = A_NORMAL;
	char sizetext[16];
	int y = item - nscroll + 1;

	wattrset(partitions, selected ? item_selected_attr : item_attr);
	wmove(partitions, y, MARGIN + items[item].indentation*2);
	dlg_print_text(partitions, items[item].name, 10, &attr);
	wmove(partitions, y, 17);
	wattrset(partitions, item_attr);

	humanize_number(sizetext, 7, items[item].size, "B", HN_AUTOSCALE,
	    HN_DECIMAL);
	dlg_print_text(partitions, sizetext, 8, &attr);
	wmove(partitions, y, 25);
	dlg_print_text(partitions, items[item].type, 15, &attr);
	wmove(partitions, y, 40);
	if (items[item].mountpoint != NULL)
		dlg_print_text(partitions, items[item].mountpoint, 8, &attr);
}