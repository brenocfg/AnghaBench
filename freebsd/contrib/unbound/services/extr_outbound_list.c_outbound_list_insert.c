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
struct outbound_list {struct outbound_entry* first; } ;
struct outbound_entry {struct outbound_entry* prev; struct outbound_entry* next; } ;

/* Variables and functions */

void 
outbound_list_insert(struct outbound_list* list, struct outbound_entry* e)
{
	if(list->first)
		list->first->prev = e;
	e->next = list->first;
	e->prev = NULL;
	list->first = e;
}