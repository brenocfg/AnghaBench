#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ json_pretty_print; } ;
struct TYPE_8__ {TYPE_1__* sub_list; } ;
struct TYPE_7__ {int /*<<< orphan*/  metrics; struct TYPE_7__* next; } ;
struct TYPE_6__ {int size; TYPE_2__* head; } ;
typedef  TYPE_1__ GSubList ;
typedef  TYPE_2__ GSubItem ;
typedef  int /*<<< orphan*/  GPercTotals ;
typedef  int /*<<< orphan*/  GMetrics ;
typedef  int /*<<< orphan*/  GJSON ;
typedef  TYPE_3__ GHolderItem ;

/* Variables and functions */
 int /*<<< orphan*/  NL ; 
 int /*<<< orphan*/  TAB ; 
 TYPE_5__ conf ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlines ; 
 int /*<<< orphan*/  pclose_arr (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pclose_obj (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  pjson (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  popen_obj (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_json_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_data_metrics (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_json_sub_items (GJSON * json, GHolderItem * item, GPercTotals totals,
                      int size, int iisp)
{
  GMetrics *nmetrics;
  GSubItem *iter;
  GSubList *sl = item->sub_list;
  int i = 0, iiisp = 0, iiiisp = 0;

  /* no sub items, nothing to output */
  if (size == 0)
    return;

  /* use tabs to prettify output */
  if (conf.json_pretty_print)
    iiisp = iisp + 1, iiiisp = iiisp + 1;

  if (sl == NULL)
    return;

  pjson (json, ",%.*s%.*s\"items\": [%.*s", nlines, NL, iisp, TAB, nlines, NL);
  for (iter = sl->head; iter; iter = iter->next, i++) {
    set_data_metrics (iter->metrics, &nmetrics, totals);

    popen_obj (json, iiisp);
    print_json_block (json, nmetrics, iiiisp);
    pclose_obj (json, iiisp, (i == sl->size - 1));
    free (nmetrics);
  }
  pclose_arr (json, iisp, 1);
}