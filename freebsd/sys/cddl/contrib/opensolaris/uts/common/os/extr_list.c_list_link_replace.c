#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* list_prev; TYPE_1__* list_next; } ;
typedef  TYPE_3__ list_node_t ;
struct TYPE_8__ {TYPE_3__* list_next; } ;
struct TYPE_7__ {TYPE_3__* list_prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int list_link_active (TYPE_3__*) ; 

void
list_link_replace(list_node_t *lold, list_node_t *lnew)
{
	ASSERT(list_link_active(lold));
	ASSERT(!list_link_active(lnew));

	lnew->list_next = lold->list_next;
	lnew->list_prev = lold->list_prev;
	lold->list_prev->list_next = lnew;
	lold->list_next->list_prev = lnew;
	lold->list_next = lold->list_prev = NULL;
}