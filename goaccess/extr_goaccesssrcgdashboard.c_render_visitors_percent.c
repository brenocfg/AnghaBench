#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int visitors_perc_len; scalar_t__ max_visitors; } ;
struct TYPE_13__ {TYPE_3__* data; int /*<<< orphan*/  module; TYPE_1__ meta; } ;
struct TYPE_12__ {int idx; } ;
struct TYPE_11__ {TYPE_2__* metrics; scalar_t__ is_subitem; } ;
struct TYPE_10__ {scalar_t__ visitors; int /*<<< orphan*/  visitors_perc; } ;
typedef  TYPE_4__ GDashRender ;
typedef  TYPE_5__ GDashModule ;
typedef  int /*<<< orphan*/  GColors ;
typedef  int /*<<< orphan*/  GColorItem ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_MTRC_VISITORS_PERC ; 
 int /*<<< orphan*/  COLOR_MTRC_VISITORS_PERC_MAX ; 
 scalar_t__ DASH_SPACE ; 
 int /*<<< orphan*/  HOSTS ; 
 int /*<<< orphan*/ * get_color_by_item_module (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  render_percent (TYPE_4__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
render_visitors_percent (GDashModule * data, GDashRender render, int *x)
{
  GColorItem item = COLOR_MTRC_VISITORS_PERC;
  GColors *color;
  int l = data->meta.visitors_perc_len + 3, idx = render.idx;

  if (data->module == HOSTS && data->data[idx].is_subitem)
    goto out;

  if (data->meta.max_visitors == data->data[idx].metrics->visitors)
    item = COLOR_MTRC_VISITORS_PERC_MAX;

  color = get_color_by_item_module (item, data->module);
  render_percent (render, color, data->data[idx].metrics->visitors_perc, l, *x);

out:
  *x += l + 1 + DASH_SPACE;
}