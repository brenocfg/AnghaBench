#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_8__ {size_t size; struct TYPE_8__* items; struct TYPE_8__* name; scalar_t__ checked; } ;
typedef  TYPE_1__ GMenu ;
typedef  TYPE_1__ GItem ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HELPDLG_DESC ; 
 int /*<<< orphan*/  HELPDLG_HEAD ; 
 int /*<<< orphan*/  HELP_MENU_HEIGHT ; 
 int /*<<< orphan*/  HELP_MENU_WIDTH ; 
 int /*<<< orphan*/  HELP_MENU_X ; 
 int /*<<< orphan*/  HELP_MENU_Y ; 
 int HELP_WIN_HEIGHT ; 
 int HELP_WIN_WIDTH ; 
#define  KEY_DOWN 130 
#define  KEY_RESIZE 129 
#define  KEY_UP 128 
 int /*<<< orphan*/  REQ_DOWN ; 
 int /*<<< orphan*/  REQ_UP ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* alloc_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_win (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  color_panel_header ; 
 int /*<<< orphan*/  draw_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  getmaxyx (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gmenu_driver (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * help_main ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* new_gmenu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * newwin (int,int,int,int) ; 
 int /*<<< orphan*/  post_gmenu (TYPE_1__*) ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  touchwin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wborder (int /*<<< orphan*/ *,char,char,char,char,char,char,char,char) ; 
 int wgetch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 
 scalar_t__ xcalloc (size_t,int) ; 

void
load_help_popup (WINDOW * main_win)
{
  int c, quit = 1;
  size_t i, n;
  int y, x, h = HELP_WIN_HEIGHT, w = HELP_WIN_WIDTH;
  int w2 = w - 2;
  WINDOW *win;
  GMenu *menu;

  n = ARRAY_SIZE (help_main);
  getmaxyx (stdscr, y, x);

  win = newwin (h, w, (y - h) / 2, (x - w) / 2);
  keypad (win, TRUE);
  wborder (win, '|', '|', '-', '-', '+', '+', '+', '+');

  /* create a new instance of GMenu and make it selectable */
  menu =
    new_gmenu (win, HELP_MENU_HEIGHT, HELP_MENU_WIDTH, HELP_MENU_Y,
               HELP_MENU_X);
  menu->size = n;

  /* add items to GMenu */
  menu->items = (GItem *) xcalloc (n, sizeof (GItem));
  for (i = 0; i < n; ++i) {
    menu->items[i].name = alloc_string (help_main[i]);
    menu->items[i].checked = 0;
  }
  post_gmenu (menu);

  draw_header (win, HELPDLG_HEAD, " %s", 1, 1, w2, color_panel_header);
  mvwprintw (win, 2, 2, HELPDLG_DESC);

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
  /* clean stuff up */
  for (i = 0; i < n; ++i)
    free (menu->items[i].name);
  free (menu->items);
  free (menu);

  touchwin (main_win);
  close_win (win);
  wrefresh (main_win);
}