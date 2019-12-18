#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_12__ {size_t module; int idx_data; } ;
struct TYPE_11__ {int y; int w; int idx; int sel; int /*<<< orphan*/ * win; } ;
struct TYPE_10__ {size_t current; TYPE_1__* module; scalar_t__ expanded; } ;
struct TYPE_9__ {int scroll; } ;
typedef  TYPE_2__ GScroll ;
typedef  size_t GModule ;
typedef  TYPE_3__ GDashRender ;
typedef  TYPE_4__ GDashModule ;

/* Variables and functions */
 int /*<<< orphan*/  getmaxyx (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  render_metrics (TYPE_4__*,TYPE_3__,int) ; 

__attribute__((used)) static void
render_data_line (WINDOW * win, GDashModule * data, int *y, int j,
                  GScroll * gscroll)
{
  GDashRender render;
  GModule module = data->module;
  int expanded = 0, sel = 0;
  int w, h;

  getmaxyx (win, h, w);
  (void) h;

  if (gscroll->expanded && module == gscroll->current)
    expanded = 1;

  if (j >= data->idx_data)
    goto out;

  sel = expanded && j == gscroll->module[module].scroll ? 1 : 0;

  render.win = win;
  render.y = *y;
  render.w = w;
  render.idx = j;
  render.sel = sel;

  render_metrics (data, render, expanded);

out:
  (*y)++;
}