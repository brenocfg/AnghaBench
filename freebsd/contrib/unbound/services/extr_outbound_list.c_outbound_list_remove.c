#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct outbound_list {TYPE_2__* first; } ;
struct outbound_entry {TYPE_2__* next; TYPE_1__* prev; int /*<<< orphan*/  qsent; } ;
struct TYPE_4__ {TYPE_1__* prev; } ;
struct TYPE_3__ {TYPE_2__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  outnet_serviced_query_stop (int /*<<< orphan*/ ,struct outbound_entry*) ; 

void 
outbound_list_remove(struct outbound_list* list, struct outbound_entry* e)
{
	if(!e)
		return;
	outnet_serviced_query_stop(e->qsent, e);
	if(e->next)
		e->next->prev = e->prev;
	if(e->prev)
		e->prev->next = e->next;
	else	list->first = e->next;
	/* in region, no free needed */
}