#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_17__ {int attr; TYPE_4__* pair; } ;
struct TYPE_13__ {int /*<<< orphan*/  max_hits; } ;
struct TYPE_16__ {TYPE_3__ meta; TYPE_2__* data; } ;
struct TYPE_15__ {int y; int w; int idx; int sel; int /*<<< orphan*/ * win; } ;
struct TYPE_14__ {int /*<<< orphan*/  idx; } ;
struct TYPE_12__ {TYPE_1__* metrics; } ;
struct TYPE_11__ {int /*<<< orphan*/  hits; } ;
typedef  TYPE_5__ GDashRender ;
typedef  TYPE_6__ GDashModule ;
typedef  TYPE_7__ GColors ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_BARS ; 
 int COLOR_PAIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  color_selected ; 
 int /*<<< orphan*/  draw_header (int /*<<< orphan*/ *,char*,char*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_bars (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_7__* get_color (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ *,int,int,char*,char*) ; 
 int /*<<< orphan*/  wattroff (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wattron (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
render_bars (GDashModule * data, GDashRender render, int *x)
{
  GColors *color = get_color (COLOR_BARS);
  WINDOW *win = render.win;
  char *bar;
  int y = render.y, w = render.w, idx = render.idx, sel = render.sel;

  bar = get_bars (data->data[idx].metrics->hits, data->meta.max_hits, *x);
  if (sel)
    draw_header (win, bar, "%s", y, *x, w, color_selected);
  else {
    wattron (win, color->attr | COLOR_PAIR (color->pair->idx));
    mvwprintw (win, y, *x, "%s", bar);
    wattroff (win, color->attr | COLOR_PAIR (color->pair->idx));
  }
  free (bar);
}