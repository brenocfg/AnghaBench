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
struct TYPE_5__ {struct TYPE_5__* next; struct TYPE_5__* prev; } ;
typedef  TYPE_1__ ucl_object_t ;

/* Variables and functions */

ucl_object_t *
ucl_elt_append (ucl_object_t *head, ucl_object_t *elt)
{

	if (head == NULL) {
		elt->next = NULL;
		elt->prev = elt;
		head = elt;
	}
	else {
		elt->prev = head->prev;
		head->prev->next = elt;
		head->prev = elt;
		elt->next = NULL;
	}

	return head;
}