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
typedef  scalar_t__ uint16_t ;
struct edns_option {scalar_t__ opt_code; struct edns_option* next; } ;

/* Variables and functions */

int edns_opt_list_remove(struct edns_option** list, uint16_t code)
{
	/* The list should already be allocated in a region. Freeing the
	 * allocated space in a region is not possible. We just unlink the
	 * required elements and they will be freed together with the region. */

	struct edns_option* prev;
	struct edns_option* curr;
	if(!list || !(*list)) return 0;

	/* Unlink and repoint if the element(s) are first in list */
	while(list && *list && (*list)->opt_code == code) {
		*list = (*list)->next;
	}

	if(!list || !(*list)) return 1;
	/* Unlink elements and reattach the list */
	prev = *list;
	curr = (*list)->next;
	while(curr != NULL) {
		if(curr->opt_code == code) {
			prev->next = curr->next;
			curr = curr->next;
		} else {
			prev = curr;
			curr = curr->next;
		}
	}
	return 1;
}