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
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_2__ {int /*<<< orphan*/  pattern; scalar_t__ icase; } ;
typedef  int /*<<< orphan*/  GScroll ;

/* Variables and functions */
 int /*<<< orphan*/  FIND_DESC ; 
 int FIND_DLG_HEIGHT ; 
 int FIND_DLG_WIDTH ; 
 int /*<<< orphan*/  FIND_HEAD ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  close_win (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  color_panel_header ; 
 int /*<<< orphan*/  draw_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ find_t ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getmaxyx (int /*<<< orphan*/ ,int,int) ; 
 char* input_string (int /*<<< orphan*/ *,int,int,int,char*,int,scalar_t__*) ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ *,int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * newwin (int,int,int,int) ; 
 int /*<<< orphan*/  reset_find () ; 
 int /*<<< orphan*/  reset_scroll_offsets (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  touchwin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wborder (int /*<<< orphan*/ *,char,char,char,char,char,char,char,char) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

int
render_find_dialog (WINDOW * main_win, GScroll * gscroll)
{
  int y, x, valid = 1;
  int w = FIND_DLG_WIDTH;
  int h = FIND_DLG_HEIGHT;
  char *query = NULL;
  WINDOW *win;

  getmaxyx (stdscr, y, x);

  win = newwin (h, w, (y - h) / 2, (x - w) / 2);
  keypad (win, TRUE);
  wborder (win, '|', '|', '-', '-', '+', '+', '+', '+');
  draw_header (win, FIND_HEAD, " %s", 1, 1, w - 2, color_panel_header);
  mvwprintw (win, 2, 1, " %s", FIND_DESC);

  find_t.icase = 0;
  query = input_string (win, 4, 2, w - 3, "", 1, &find_t.icase);
  if (query != NULL && *query != '\0') {
    reset_scroll_offsets (gscroll);
    reset_find ();
    find_t.pattern = xstrdup (query);
    valid = 0;
  }
  if (query != NULL)
    free (query);
  touchwin (main_win);
  close_win (win);
  wrefresh (main_win);

  return valid;
}