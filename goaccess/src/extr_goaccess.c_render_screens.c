#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int processed; int offset; } ;
struct TYPE_10__ {int /*<<< orphan*/  current; } ;
struct TYPE_9__ {int attr; TYPE_1__* pair; } ;
struct TYPE_8__ {int /*<<< orphan*/  idx; } ;
typedef  TYPE_2__ GColors ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_DEFAULT ; 
 int COLOR_PAIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GO_VERSION ; 
 int /*<<< orphan*/  T_HELP_ENTER ; 
 int /*<<< orphan*/  T_QUIT ; 
 int /*<<< orphan*/  asctime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  color_default ; 
 int /*<<< orphan*/  dash ; 
 int /*<<< orphan*/  display_content (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  display_general (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_header (int /*<<< orphan*/ ,char*,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generate_time () ; 
 TYPE_2__* get_color (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getmaxyx (int /*<<< orphan*/ ,int,int) ; 
 TYPE_4__* glog ; 
 TYPE_3__ gscroll ; 
 int /*<<< orphan*/  header_win ; 
 int /*<<< orphan*/  holder ; 
 int /*<<< orphan*/  main_win ; 
 int /*<<< orphan*/  main_win_height ; 
 int /*<<< orphan*/  mvaddstr (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvprintw (int,int,char*,int,...) ; 
 int /*<<< orphan*/  now_tm ; 
 int /*<<< orphan*/  refresh () ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  term_size (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_active_module (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wattroff (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wattron (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
render_screens (void)
{
  GColors *color = get_color (COLOR_DEFAULT);
  int row, col, chg = 0;

  getmaxyx (stdscr, row, col);
  term_size (main_win, &main_win_height);

  generate_time ();
  chg = glog->processed - glog->offset;

  draw_header (stdscr, "", "%s", row - 1, 0, col, color_default);

  wattron (stdscr, color->attr | COLOR_PAIR (color->pair->idx));
  mvaddstr (row - 1, 1, T_HELP_ENTER);
  mvprintw (row - 1, 30, "%d - %s", chg, asctime (now_tm));
  mvaddstr (row - 1, col - 21, T_QUIT);
  mvprintw (row - 1, col - 5, "%s", GO_VERSION);
  wattroff (stdscr, color->attr | COLOR_PAIR (color->pair->idx));

  refresh ();

  /* call general stats header */
  display_general (header_win, glog, holder);
  wrefresh (header_win);

  /* display active label based on current module */
  update_active_module (header_win, gscroll.current);

  display_content (main_win, dash, &gscroll);
}