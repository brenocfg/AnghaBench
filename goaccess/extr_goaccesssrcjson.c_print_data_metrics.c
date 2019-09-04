#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct GPanel_ {int /*<<< orphan*/  (* subitems ) (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_7__ {scalar_t__ json_pretty_print; } ;
struct TYPE_6__ {int /*<<< orphan*/  metrics; } ;
struct TYPE_5__ {int idx; int /*<<< orphan*/  sub_items_size; TYPE_2__* items; } ;
typedef  int /*<<< orphan*/  GPercTotals ;
typedef  int /*<<< orphan*/  GMetrics ;
typedef  int /*<<< orphan*/  GJSON ;
typedef  TYPE_1__ GHolder ;

/* Variables and functions */
 TYPE_4__ conf ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pclose_arr (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pclose_obj (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  popen_arr_attr (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  popen_obj (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_json_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_data_metrics (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
print_data_metrics (GJSON * json, GHolder * h, GPercTotals totals, int sp,
                    const struct GPanel_ *panel)
{
  GMetrics *nmetrics;
  int i, isp = 0, iisp = 0, iiisp = 0;

  /* use tabs to prettify output */
  if (conf.json_pretty_print)
    isp = sp + 1, iisp = sp + 2, iiisp = sp + 3;

  popen_arr_attr (json, "data", isp);
  /* output data metrics */
  for (i = 0; i < h->idx; i++) {
    set_data_metrics (h->items[i].metrics, &nmetrics, totals);

    /* open data metric block */
    popen_obj (json, iisp);
    /* output data metric block */
    print_json_block (json, nmetrics, iiisp);
    /* if there are children nodes, spit them out */
    if (panel->subitems)
      panel->subitems (json, h->items + i, totals, h->sub_items_size, iiisp);
    /* close data metric block */
    pclose_obj (json, iisp, (i == h->idx - 1));

    free (nmetrics);
  }
  pclose_arr (json, isp, 1);
}