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
struct inferior_list_entry {int id; struct inferior_list_entry* next; } ;
struct inferior_list {struct inferior_list_entry* head; } ;

/* Variables and functions */

struct inferior_list_entry *
find_inferior_id (struct inferior_list *list, int id)
{
  struct inferior_list_entry *inf = list->head;

  while (inf != NULL)
    {
      if (inf->id == id)
	return inf;
      inf = inf->next;
    }

  return NULL;
}