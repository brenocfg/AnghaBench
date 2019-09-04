#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int idx; scalar_t__ sub_items_size; int /*<<< orphan*/  module; TYPE_1__* items; } ;
struct TYPE_5__ {int /*<<< orphan*/  metrics; } ;
typedef  int /*<<< orphan*/  GPercTotals ;
typedef  int /*<<< orphan*/  GMetrics ;
typedef  TYPE_2__ GHolder ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 char* module_to_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_csv_metric_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_csv_sub_items (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_data_metrics (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_csv_data (FILE * fp, GHolder * h, GPercTotals totals)
{
  GMetrics *nmetrics;
  int i;

  for (i = 0; i < h->idx; i++) {
    set_data_metrics (h->items[i].metrics, &nmetrics, totals);

    fprintf (fp, "\"%d\",", i); /* idx */
    fprintf (fp, ",");  /* no parent */
    fprintf (fp, "\"%s\",", module_to_id (h->module));

    /* output metrics */
    print_csv_metric_block (fp, nmetrics);

    if (h->sub_items_size)
      print_csv_sub_items (fp, h, i, totals);

    free (nmetrics);
  }
}