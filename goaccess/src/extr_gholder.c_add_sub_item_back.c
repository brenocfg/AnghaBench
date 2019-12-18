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
struct TYPE_6__ {struct TYPE_6__* prev; struct TYPE_6__* next; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; TYPE_2__* tail; TYPE_2__* head; } ;
typedef  TYPE_1__ GSubList ;
typedef  TYPE_2__ GSubItem ;
typedef  int /*<<< orphan*/  GModule ;
typedef  int /*<<< orphan*/  GMetrics ;

/* Variables and functions */
 TYPE_2__* new_gsubitem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
add_sub_item_back (GSubList * sub_list, GModule module, GMetrics * nmetrics)
{
  GSubItem *sub_item = new_gsubitem (module, nmetrics);
  if (sub_list->tail) {
    sub_list->tail->next = sub_item;
    sub_item->prev = sub_list->tail;
    sub_list->tail = sub_item;
  } else {
    sub_list->head = sub_item;
    sub_list->tail = sub_item;
  }
  sub_list->size++;
}