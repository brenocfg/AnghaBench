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
struct TYPE_2__ {union acpi_operand_object* prev; union acpi_operand_object* next; } ;
union acpi_operand_object {TYPE_1__ mutex; } ;
struct acpi_thread_state {union acpi_operand_object* acquired_mutex_list; } ;

/* Variables and functions */

__attribute__((used)) static void
acpi_ex_link_mutex(union acpi_operand_object *obj_desc,
		   struct acpi_thread_state *thread)
{
	union acpi_operand_object *list_head;

	list_head = thread->acquired_mutex_list;

	/* This object will be the first object in the list */

	obj_desc->mutex.prev = NULL;
	obj_desc->mutex.next = list_head;

	/* Update old first object to point back to this object */

	if (list_head) {
		list_head->mutex.prev = obj_desc;
	}

	/* Update list head */

	thread->acquired_mutex_list = obj_desc;
}