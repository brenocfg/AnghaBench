#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_8__ {int attr; TYPE_1__* pair; } ;
struct TYPE_7__ {int y; int w; int sel; int /*<<< orphan*/ * win; } ;
struct TYPE_6__ {int /*<<< orphan*/  idx; } ;
typedef  TYPE_2__ GDashRender ;
typedef  TYPE_3__ GColors ;

/* Variables and functions */
 int COLOR_PAIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  color_selected ; 
 int /*<<< orphan*/  draw_header (int /*<<< orphan*/ *,char*,char*,int,int,int,int /*<<< orphan*/ ) ; 
 char* float2str (float,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ *,int,int,char*,int,float) ; 
 int /*<<< orphan*/  wattroff (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wattron (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
render_percent (GDashRender render, GColors * color, float perc, int len, int x)
{
  WINDOW *win = render.win;
  char *percent;
  int y = render.y, w = render.w, sel = render.sel;

  if (sel) {
    /* selected state */
    percent = float2str (perc, len);
    draw_header (win, percent, "%s%%", y, x, w, color_selected);
    free (percent);
  } else {
    /* regular state */
    wattron (win, color->attr | COLOR_PAIR (color->pair->idx));
    mvwprintw (win, y, x, "%*.2f%%", len, perc);
    wattroff (win, color->attr | COLOR_PAIR (color->pair->idx));
  }
}