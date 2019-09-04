#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_9__ {int /*<<< orphan*/  list_agents; } ;
struct TYPE_8__ {int size; struct TYPE_8__* items; struct TYPE_8__* name; } ;
typedef  TYPE_1__ GMenu ;

/* Variables and functions */
 int /*<<< orphan*/  AGENTSDLG_DESC ; 
 char* AGENTSDLG_HEAD ; 
 int AGENTS_MENU_X ; 
 int AGENTS_MENU_Y ; 
#define  KEY_DOWN 130 
#define  KEY_RESIZE 129 
#define  KEY_UP 128 
 int /*<<< orphan*/  REQ_DOWN ; 
 int /*<<< orphan*/  REQ_UP ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  close_win (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  color_panel_header ; 
 TYPE_7__ conf ; 
 int /*<<< orphan*/  draw_header (int /*<<< orphan*/ *,char*,char*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  getmaxyx (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gmenu_driver (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_host_agents_gmenu ; 
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* new_gmenu (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/ * newwin (int,int,int,int) ; 
 int /*<<< orphan*/  post_gmenu (TYPE_1__*) ; 
 int set_host_agents (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  touchwin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wborder (int /*<<< orphan*/ *,char,char,char,char,char,char,char,char) ; 
 int wgetch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 

void
load_agent_list (WINDOW * main_win, char *addr)
{
  GMenu *menu;
  WINDOW *win;

  char buf[256];
  int c, quit = 1, i;
  int y, x, list_h, list_w, menu_w, menu_h;

  if (!conf.list_agents)
    return;

  getmaxyx (stdscr, y, x);
  list_h = y / 2;       /* list window - height */
  list_w = x - 4;       /* list window - width */
  menu_h = list_h - AGENTS_MENU_Y - 1;  /* menu window - height */
  menu_w = list_w - AGENTS_MENU_X - AGENTS_MENU_X;      /* menu window - width */

  win = newwin (list_h, list_w, (y - list_h) / 2, (x - list_w) / 2);
  keypad (win, TRUE);
  wborder (win, '|', '|', '-', '-', '+', '+', '+', '+');

  /* create a new instance of GMenu and make it selectable */
  menu = new_gmenu (win, menu_h, menu_w, AGENTS_MENU_Y, AGENTS_MENU_X);
  if (set_host_agents (addr, load_host_agents_gmenu, menu) == 1)
    goto out;

  post_gmenu (menu);
  snprintf (buf, sizeof buf, AGENTSDLG_HEAD, addr);
  draw_header (win, buf, " %s", 1, 1, list_w - 2, color_panel_header);
  mvwprintw (win, 2, 2, AGENTSDLG_DESC);
  wrefresh (win);

  while (quit) {
    c = wgetch (stdscr);
    switch (c) {
    case KEY_DOWN:
      gmenu_driver (menu, REQ_DOWN);
      break;
    case KEY_UP:
      gmenu_driver (menu, REQ_UP);
      break;
    case KEY_RESIZE:
    case 'q':
      quit = 0;
      break;
    }
    wrefresh (win);
  }

  touchwin (main_win);
  close_win (win);
  wrefresh (main_win);

out:

  /* clean stuff up */
  for (i = 0; i < menu->size; ++i)
    free (menu->items[i].name);
  if (menu->items)
    free (menu->items);
  free (menu);
}