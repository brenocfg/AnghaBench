#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* sub_list; } ;
struct TYPE_6__ {int /*<<< orphan*/  metrics; struct TYPE_6__* next; } ;
struct TYPE_5__ {TYPE_2__* head; } ;
typedef  TYPE_1__ GSubList ;
typedef  TYPE_2__ GSubItem ;
typedef  int /*<<< orphan*/  GModule ;
typedef  TYPE_3__ GHolderItem ;
typedef  int /*<<< orphan*/  GDash ;

/* Variables and functions */
 int /*<<< orphan*/  set_dash_metrics (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
add_sub_item_to_dash (GDash ** dash, GHolderItem item, GModule module, int *i)
{
  GSubList *sub_list = item.sub_list;
  GSubItem *iter;

  if (sub_list == NULL)
    return;

  for (iter = sub_list->head; iter; iter = iter->next, (*i)++) {
    set_dash_metrics (dash, iter->metrics, module, 1);
  }
}