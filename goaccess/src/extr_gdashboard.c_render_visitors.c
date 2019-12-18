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
struct TYPE_11__ {int visitors_len; } ;
struct TYPE_16__ {scalar_t__ module; TYPE_3__* data; TYPE_1__ meta; } ;
struct TYPE_15__ {int y; int w; int idx; int sel; int /*<<< orphan*/ * win; } ;
struct TYPE_14__ {int /*<<< orphan*/  idx; } ;
struct TYPE_13__ {TYPE_2__* metrics; scalar_t__ is_subitem; } ;
struct TYPE_12__ {int /*<<< orphan*/  visitors; } ;
typedef  TYPE_5__ GDashRender ;
typedef  TYPE_6__ GDashModule ;
typedef  TYPE_7__ GColors ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_MTRC_VISITORS ; 
 int COLOR_PAIR (int /*<<< orphan*/ ) ; 
 scalar_t__ DASH_SPACE ; 
 scalar_t__ HOSTS ; 
 int /*<<< orphan*/  color_selected ; 
 int /*<<< orphan*/  draw_header (int /*<<< orphan*/ *,char*,char*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_7__* get_color_by_item_module (int /*<<< orphan*/ ,scalar_t__) ; 
 char* int2str (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ *,int,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wattroff (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wattron (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
render_visitors (GDashModule * data, GDashRender render, int *x)
{
  GColors *color = get_color_by_item_module (COLOR_MTRC_VISITORS, data->module);
  WINDOW *win = render.win;

  char *visitors;
  int y = render.y, w = render.w, idx = render.idx, sel = render.sel;
  int len = data->meta.visitors_len;

  if (data->module == HOSTS && data->data[idx].is_subitem)
    goto out;

  if (sel) {
    /* selected state */
    visitors = int2str (data->data[idx].metrics->visitors, len);
    draw_header (win, visitors, "%s", y, *x, w, color_selected);
    free (visitors);
  } else {
    /* regular state */
    wattron (win, color->attr | COLOR_PAIR (color->pair->idx));
    mvwprintw (win, y, *x, "%*d", len, data->data[idx].metrics->visitors);
    wattroff (win, color->attr | COLOR_PAIR (color->pair->idx));
  }

out:
  *x += len + DASH_SPACE;
}