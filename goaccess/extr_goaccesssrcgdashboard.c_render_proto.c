#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_15__ {int attr; TYPE_3__* pair; } ;
struct TYPE_14__ {TYPE_2__* data; int /*<<< orphan*/  module; } ;
struct TYPE_13__ {int y; int w; int idx; int sel; int /*<<< orphan*/ * win; } ;
struct TYPE_12__ {int /*<<< orphan*/  idx; } ;
struct TYPE_11__ {TYPE_1__* metrics; } ;
struct TYPE_10__ {char* protocol; } ;
typedef  TYPE_4__ GDashRender ;
typedef  TYPE_5__ GDashModule ;
typedef  TYPE_6__ GColors ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_MTRC_PROT ; 
 int COLOR_PAIR (int /*<<< orphan*/ ) ; 
 int DASH_SPACE ; 
 int REQ_PROTO_LEN ; 
 int /*<<< orphan*/  color_selected ; 
 int /*<<< orphan*/  draw_header (int /*<<< orphan*/ *,char*,char*,int,int,int,int /*<<< orphan*/ ) ; 
 TYPE_6__* get_color_by_item_module (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvwprintw (int /*<<< orphan*/ *,int,int,char*,char*) ; 
 int /*<<< orphan*/  wattroff (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wattron (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
render_proto (GDashModule * data, GDashRender render, int *x)
{
  GColors *color = get_color_by_item_module (COLOR_MTRC_PROT, data->module);
  WINDOW *win = render.win;

  int y = render.y, w = render.w, idx = render.idx, sel = render.sel;
  char *protocol = data->data[idx].metrics->protocol;

  if (protocol == NULL || *protocol == '\0')
    return;

  if (sel) {
    /* selected state */
    draw_header (win, protocol, "%s", y, *x, w, color_selected);
  } else {
    /* regular state */
    wattron (win, color->attr | COLOR_PAIR (color->pair->idx));
    mvwprintw (win, y, *x, "%s", protocol);
    wattroff (win, color->attr | COLOR_PAIR (color->pair->idx));
  }

  *x += REQ_PROTO_LEN - 1 + DASH_SPACE;
}