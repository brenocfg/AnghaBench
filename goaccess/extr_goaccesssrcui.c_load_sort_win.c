#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_13__ {int size; int selectable; int checked; int idx; struct TYPE_13__* items; struct TYPE_13__* name; } ;
struct TYPE_12__ {scalar_t__ field; scalar_t__ sort; } ;
struct TYPE_11__ {int /*<<< orphan*/  append_method; int /*<<< orphan*/  append_protocol; int /*<<< orphan*/  bandwidth; int /*<<< orphan*/  serve_usecs; } ;
typedef  scalar_t__ GSortField ;
typedef  TYPE_1__ GSort ;
typedef  size_t GModule ;
typedef  TYPE_2__ GMenu ;
typedef  TYPE_2__ GItem ;

/* Variables and functions */
#define  KEY_DOWN 131 
#define  KEY_ENTER 130 
#define  KEY_RESIZE 129 
#define  KEY_UP 128 
 int /*<<< orphan*/  MTRC_AVGTS_LBL ; 
 int /*<<< orphan*/  MTRC_BW_LBL ; 
 int /*<<< orphan*/  MTRC_CUMTS_LBL ; 
 int /*<<< orphan*/  MTRC_DATA_LBL ; 
 int /*<<< orphan*/  MTRC_HITS_LBL ; 
 int /*<<< orphan*/  MTRC_MAXTS_LBL ; 
 int /*<<< orphan*/  MTRC_METHODS_LBL ; 
 int /*<<< orphan*/  MTRC_PROTOCOLS_LBL ; 
 int /*<<< orphan*/  MTRC_VISITORS_LBL ; 
 int /*<<< orphan*/  REQ_DOWN ; 
 int /*<<< orphan*/  REQ_SEL ; 
 int /*<<< orphan*/  REQ_UP ; 
 int /*<<< orphan*/  SORTDLG_DESC ; 
 int /*<<< orphan*/  SORTDLG_HEAD ; 
 scalar_t__ SORT_ASC ; 
 int /*<<< orphan*/  SORT_ASC_SEL ; 
 scalar_t__ SORT_BY_AVGTS ; 
 scalar_t__ SORT_BY_BW ; 
 scalar_t__ SORT_BY_CUMTS ; 
 scalar_t__ SORT_BY_DATA ; 
 scalar_t__ SORT_BY_HITS ; 
 scalar_t__ SORT_BY_MAXTS ; 
 scalar_t__ SORT_BY_MTHD ; 
 scalar_t__ SORT_BY_PROT ; 
 scalar_t__ SORT_BY_VISITORS ; 
 scalar_t__ SORT_DESC ; 
 int /*<<< orphan*/  SORT_DESC_SEL ; 
 int SORT_MAX_OPTS ; 
 int /*<<< orphan*/  SORT_MENU_H ; 
 int /*<<< orphan*/  SORT_MENU_W ; 
 int /*<<< orphan*/  SORT_MENU_X ; 
 int /*<<< orphan*/  SORT_MENU_Y ; 
 int SORT_WIN_H ; 
 int SORT_WIN_W ; 
 int /*<<< orphan*/  TRUE ; 
 void* alloc_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_win (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  color_panel_header ; 
 TYPE_10__ conf ; 
 int /*<<< orphan*/  draw_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  getmaxyx (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gmenu_driver (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ *,int,int,char*,...) ; 
 TYPE_2__* new_gmenu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * newwin (int,int,int,int) ; 
 int /*<<< orphan*/  post_gmenu (TYPE_2__*) ; 
 int** sort_choices ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  strcmp (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  touchwin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wborder (int /*<<< orphan*/ *,char,char,char,char,char,char,char,char) ; 
 int wgetch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 
 scalar_t__ xcalloc (int,int) ; 

void
load_sort_win (WINDOW * main_win, GModule module, GSort * sort)
{
  GMenu *menu;
  WINDOW *win;
  GSortField opts[SORT_MAX_OPTS];

  int c, quit = 1;
  int i = 0, k, n = 0;
  int y, x, h = SORT_WIN_H, w = SORT_WIN_W;
  int w2 = w - 2;

  getmaxyx (stdscr, y, x);

  /* determine amount of sort choices */
  for (i = 0, k = 0; -1 != sort_choices[module][i]; i++) {
    GSortField field = sort_choices[module][i];
    if (SORT_BY_CUMTS == field && !conf.serve_usecs)
      continue;
    else if (SORT_BY_MAXTS == field && !conf.serve_usecs)
      continue;
    else if (SORT_BY_AVGTS == field && !conf.serve_usecs)
      continue;
    else if (SORT_BY_BW == field && !conf.bandwidth)
      continue;
    else if (SORT_BY_PROT == field && !conf.append_protocol)
      continue;
    else if (SORT_BY_MTHD == field && !conf.append_method)
      continue;
    opts[k++] = field;
    n++;
  }

  win = newwin (h, w, (y - h) / 2, (x - w) / 2);
  keypad (win, TRUE);
  wborder (win, '|', '|', '-', '-', '+', '+', '+', '+');

  /* create a new instance of GMenu and make it selectable */
  menu = new_gmenu (win, SORT_MENU_H, SORT_MENU_W, SORT_MENU_Y, SORT_MENU_X);
  menu->size = n;
  menu->selectable = 1;

  /* add items to GMenu */
  menu->items = (GItem *) xcalloc (n, sizeof (GItem));

  /* set choices, checked option and index */
  for (i = 0; i < n; ++i) {
    GSortField field = sort_choices[module][opts[i]];
    if (SORT_BY_HITS == field) {
      menu->items[i].name = alloc_string (MTRC_HITS_LBL);
      if (sort->field == SORT_BY_HITS) {
        menu->items[i].checked = 1;
        menu->idx = i;
      }
    } else if (SORT_BY_VISITORS == field) {
      menu->items[i].name = alloc_string (MTRC_VISITORS_LBL);
      if (sort->field == SORT_BY_VISITORS) {
        menu->items[i].checked = 1;
        menu->idx = i;
      }
    } else if (SORT_BY_DATA == field) {
      menu->items[i].name = alloc_string (MTRC_DATA_LBL);
      if (sort->field == SORT_BY_DATA) {
        menu->items[i].checked = 1;
        menu->idx = i;
      }
    } else if (SORT_BY_BW == field) {
      menu->items[i].name = alloc_string (MTRC_BW_LBL);
      if (sort->field == SORT_BY_BW) {
        menu->items[i].checked = 1;
        menu->idx = i;
      }
    } else if (SORT_BY_AVGTS == field) {
      menu->items[i].name = alloc_string (MTRC_AVGTS_LBL);
      if (sort->field == SORT_BY_AVGTS) {
        menu->items[i].checked = 1;
        menu->idx = i;
      }
    } else if (SORT_BY_CUMTS == field) {
      menu->items[i].name = alloc_string (MTRC_CUMTS_LBL);
      if (sort->field == SORT_BY_CUMTS) {
        menu->items[i].checked = 1;
        menu->idx = i;
      }
    } else if (SORT_BY_MAXTS == field) {
      menu->items[i].name = alloc_string (MTRC_MAXTS_LBL);
      if (sort->field == SORT_BY_MAXTS) {
        menu->items[i].checked = 1;
        menu->idx = i;
      }
    } else if (SORT_BY_PROT == field) {
      menu->items[i].name = alloc_string (MTRC_PROTOCOLS_LBL);
      if (sort->field == SORT_BY_PROT) {
        menu->items[i].checked = 1;
        menu->idx = i;
      }
    } else if (SORT_BY_MTHD == field) {
      menu->items[i].name = alloc_string (MTRC_METHODS_LBL);
      if (sort->field == SORT_BY_MTHD) {
        menu->items[i].checked = 1;
        menu->idx = i;
      }
    }
  }
  post_gmenu (menu);

  draw_header (win, SORTDLG_HEAD, " %s", 1, 1, w2, color_panel_header);
  mvwprintw (win, 2, 2, SORTDLG_DESC);

  if (sort->sort == SORT_ASC)
    mvwprintw (win, SORT_WIN_H - 2, 1, " %s", SORT_ASC_SEL);
  else
    mvwprintw (win, SORT_WIN_H - 2, 1, " %s", SORT_DESC_SEL);

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
    case 9:    /* TAB */
      if (sort->sort == SORT_ASC) {
        /* ascending */
        sort->sort = SORT_DESC;
        mvwprintw (win, SORT_WIN_H - 2, 1, " %s", SORT_DESC_SEL);
      } else {
        /* descending */
        sort->sort = SORT_ASC;
        mvwprintw (win, SORT_WIN_H - 2, 1, " %s", SORT_ASC_SEL);
      }
      break;
    case 32:
    case 0x0a:
    case 0x0d:
    case KEY_ENTER:
      gmenu_driver (menu, REQ_SEL);
      for (i = 0; i < n; ++i) {
        if (menu->items[i].checked != 1)
          continue;
        if (strcmp ("Hits", menu->items[i].name) == 0)
          sort->field = SORT_BY_HITS;
        else if (strcmp ("Visitors", menu->items[i].name) == 0)
          sort->field = SORT_BY_VISITORS;
        else if (strcmp ("Data", menu->items[i].name) == 0)
          sort->field = SORT_BY_DATA;
        else if (strcmp ("Tx. Amount", menu->items[i].name) == 0)
          sort->field = SORT_BY_BW;
        else if (strcmp ("Avg. T.S.", menu->items[i].name) == 0)
          sort->field = SORT_BY_AVGTS;
        else if (strcmp ("Cum. T.S.", menu->items[i].name) == 0)
          sort->field = SORT_BY_CUMTS;
        else if (strcmp ("Max. T.S.", menu->items[i].name) == 0)
          sort->field = SORT_BY_MAXTS;
        else if (strcmp ("Protocol", menu->items[i].name) == 0)
          sort->field = SORT_BY_PROT;
        else if (strcmp ("Method", menu->items[i].name) == 0)
          sort->field = SORT_BY_MTHD;
        quit = 0;
        break;
      }
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