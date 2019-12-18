#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inferior_list {TYPE_1__* head; TYPE_1__* tail; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 

void
change_inferior_id (struct inferior_list *list,
		    int new_id)
{
  if (list->head != list->tail)
    error ("tried to change thread ID after multiple threads are created");

  list->head->id = new_id;
}