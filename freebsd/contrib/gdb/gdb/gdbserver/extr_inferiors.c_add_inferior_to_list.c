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
add_inferior_to_list (struct inferior_list *list,
		      struct inferior_list_entry *new_inferior)
{
  new_inferior->next = NULL;
  if (list->tail != NULL)
    list->tail->next = new_inferior;
  else
    list->head = new_inferior;
  list->tail = new_inferior;
}