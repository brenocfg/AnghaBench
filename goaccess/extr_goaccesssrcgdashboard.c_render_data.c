#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_18__ {int attr; TYPE_3__* pair; } ;
struct TYPE_15__ {int data_len; } ;
struct TYPE_17__ {scalar_t__ module; TYPE_4__ meta; TYPE_2__* data; } ;
struct TYPE_16__ {int y; int w; int idx; int sel; int /*<<< orphan*/ * win; } ;
struct TYPE_14__ {int /*<<< orphan*/  idx; } ;
struct TYPE_13__ {scalar_t__ is_subitem; TYPE_1__* metrics; } ;
struct TYPE_12__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_5__ GDashRender ;
typedef  TYPE_6__ GDashModule ;
typedef  TYPE_7__ GColors ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_MTRC_DATA ; 
 int COLOR_PAIR (int /*<<< orphan*/ ) ; 
 scalar_t__ DASH_SPACE ; 
 scalar_t__ HOSTS ; 
 scalar_t__ VISITORS ; 
 int /*<<< orphan*/  color_selected ; 
 int /*<<< orphan*/  draw_header (int /*<<< orphan*/ *,char*,char*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_7__* get_color_by_item_module (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ *,int,int,char*,char*) ; 
 int /*<<< orphan*/  render_data_hosts (int /*<<< orphan*/ *,TYPE_5__,char*,int) ; 
 char* set_visitors_date (char*) ; 
 int strlen (char*) ; 
 char* substring (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wattroff (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wattron (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
render_data (GDashModule * data, GDashRender render, int *x)
{
  GColors *color = get_color_by_item_module (COLOR_MTRC_DATA, data->module);
  WINDOW *win = render.win;

  char *date = NULL, *value = NULL, *buf = NULL;
  int y = render.y, w = render.w, idx = render.idx, sel = render.sel;
  int date_len = 0;

  value = substring (data->data[idx].metrics->data, 0, w - *x);
  if (data->module == VISITORS) {
    date = set_visitors_date (value);
    date_len = strlen (date);
  }

  if (sel && data->module == HOSTS && data->data[idx].is_subitem) {
    render_data_hosts (win, render, value, *x);
  } else if (sel) {
    buf = data->module == VISITORS ? date : value;
    draw_header (win, buf, "%s", y, *x, w, color_selected);
  } else {
    wattron (win, color->attr | COLOR_PAIR (color->pair->idx));
    mvwprintw (win, y, *x, "%s", data->module == VISITORS ? date : value);
    wattroff (win, color->attr | COLOR_PAIR (color->pair->idx));
  }

  *x += data->module == VISITORS ? date_len : data->meta.data_len;
  *x += DASH_SPACE;
  free (value);
  free (date);
}