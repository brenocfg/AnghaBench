#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  module; TYPE_1__* items; } ;
struct TYPE_8__ {int /*<<< orphan*/  metrics; struct TYPE_8__* next; } ;
struct TYPE_7__ {TYPE_3__* head; } ;
struct TYPE_6__ {TYPE_2__* sub_list; } ;
typedef  TYPE_2__ GSubList ;
typedef  TYPE_3__ GSubItem ;
typedef  int /*<<< orphan*/  GPercTotals ;
typedef  int /*<<< orphan*/  GMetrics ;
typedef  TYPE_4__ GHolder ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 char* module_to_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_csv_metric_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_data_metrics (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_csv_sub_items (FILE * fp, GHolder * h, int idx, GPercTotals totals)
{
  GMetrics *nmetrics;
  GSubList *sub_list = h->items[idx].sub_list;
  GSubItem *iter;

  int i = 0;

  if (sub_list == NULL)
    return;

  for (iter = sub_list->head; iter; iter = iter->next, i++) {
    set_data_metrics (iter->metrics, &nmetrics, totals);

    fprintf (fp, "\"%d\",", i); /* idx */
    fprintf (fp, "\"%d\",", idx);       /* parent idx */
    fprintf (fp, "\"%s\",", module_to_id (h->module));

    /* output metrics */
    print_csv_metric_block (fp, nmetrics);
    free (nmetrics);
  }
}