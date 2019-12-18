#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ size; struct TYPE_5__* head; struct TYPE_5__* metrics; struct TYPE_5__* data; struct TYPE_5__* next; } ;
typedef  TYPE_1__ GSubList ;
typedef  TYPE_1__ GSubItem ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void
delete_sub_list (GSubList * sub_list)
{
  GSubItem *item = NULL;
  GSubItem *next = NULL;

  if (sub_list != NULL && sub_list->size == 0)
    goto clear;
  if (sub_list->size == 0)
    return;

  for (item = sub_list->head; item; item = next) {
    next = item->next;
    free (item->metrics->data);
    free (item->metrics);
    free (item);
  }
clear:
  sub_list->head = NULL;
  sub_list->size = 0;
  free (sub_list);
}