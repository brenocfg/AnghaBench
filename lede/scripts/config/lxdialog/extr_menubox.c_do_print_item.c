#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_11__ {int /*<<< orphan*/  atr; } ;
struct TYPE_10__ {int /*<<< orphan*/  atr; } ;
struct TYPE_9__ {int /*<<< orphan*/  atr; } ;
struct TYPE_8__ {int /*<<< orphan*/  atr; } ;
struct TYPE_7__ {int /*<<< orphan*/  atr; } ;
struct TYPE_12__ {TYPE_5__ tag_key; TYPE_4__ tag_key_selected; TYPE_3__ item; TYPE_2__ item_selected; TYPE_1__ menubox; } ;

/* Variables and functions */
 TYPE_6__ dlg ; 
 int first_alpha (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int item_x ; 
 char* malloc (int) ; 
 int menu_width ; 
 int /*<<< orphan*/  mvwaddch (int /*<<< orphan*/ *,int,int,char) ; 
 int /*<<< orphan*/  mvwaddstr (int /*<<< orphan*/ *,int,int,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  wattrset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wclrtoeol (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void do_print_item(WINDOW * win, const char *item, int line_y,
			  int selected, int hotkey)
{
	int j;
	char *menu_item = malloc(menu_width + 1);

	strncpy(menu_item, item, menu_width - item_x);
	menu_item[menu_width - item_x] = '\0';
	j = first_alpha(menu_item, "YyNnMmHh");

	/* Clear 'residue' of last item */
	wattrset(win, dlg.menubox.atr);
	wmove(win, line_y, 0);
#if OLD_NCURSES
	{
		int i;
		for (i = 0; i < menu_width; i++)
			waddch(win, ' ');
	}
#else
	wclrtoeol(win);
#endif
	wattrset(win, selected ? dlg.item_selected.atr : dlg.item.atr);
	mvwaddstr(win, line_y, item_x, menu_item);
	if (hotkey) {
		wattrset(win, selected ? dlg.tag_key_selected.atr
			 : dlg.tag_key.atr);
		mvwaddch(win, line_y, item_x + j, menu_item[j]);
	}
	if (selected) {
		wmove(win, line_y, item_x + 1);
	}
	free(menu_item);
	wrefresh(win);
}