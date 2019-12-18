#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct inferior_list_entry {struct inferior_list_entry* next; } ;
struct inferior_list {struct inferior_list_entry* tail; struct inferior_list_entry* head; } ;

/* Variables and functions */

void
remove_inferior (struct inferior_list *list,
		 struct inferior_list_entry *entry)
{
  struct inferior_list_entry **cur;

  if (list->head == entry)
    {
      list->head = entry->next;
      if (list->tail == entry)
	list->tail = list->head;
      return;
    }

  cur = &list->head;
  while (*cur && (*cur)->next != entry)
    cur = &(*cur)->next;

  if (*cur == NULL)
    return;

  (*cur)->next = entry->next;

  if (list->tail == entry)
    list->tail = *cur;
}