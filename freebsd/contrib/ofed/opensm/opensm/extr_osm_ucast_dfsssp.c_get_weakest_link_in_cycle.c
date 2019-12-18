#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ status; TYPE_2__* linklist; } ;
typedef  TYPE_1__ cdg_node_t ;
struct TYPE_6__ {scalar_t__ num_pairs; scalar_t__ removed; struct TYPE_6__* next; TYPE_1__* node; } ;
typedef  TYPE_2__ cdg_link_t ;

/* Variables and functions */
 scalar_t__ GRAY ; 
 void* UNKNOWN ; 

__attribute__((used)) static cdg_link_t *get_weakest_link_in_cycle(cdg_node_t * cycle)
{
	cdg_node_t *current = cycle, *node_with_weakest_link = NULL;
	cdg_link_t *link = NULL, *weakest_link = NULL;

	link = current->linklist;
	while (link) {
		if (link->node->status == GRAY) {
			weakest_link = link;
			node_with_weakest_link = current;
			current = link->node;
			break;
		}
		link = link->next;
	}

	while (1) {
		current->status = UNKNOWN;
		link = current->linklist;
		while (link) {
			if (link->node->status == GRAY) {
				if ((link->num_pairs - link->removed) <
				    (weakest_link->num_pairs -
				     weakest_link->removed)) {
					weakest_link = link;
					node_with_weakest_link = current;
				}
				current = link->node;
				break;
			}
			link = link->next;
		}
		/* if complete cycle is traversed */
		if (current == cycle) {
			current->status = UNKNOWN;
			break;
		}
	}

	if (node_with_weakest_link->linklist == weakest_link) {
		node_with_weakest_link->linklist = weakest_link->next;
	} else {
		link = node_with_weakest_link->linklist;
		while (link) {
			if (link->next == weakest_link) {
				link->next = weakest_link->next;
				break;
			}
			link = link->next;
		}
	}

	return weakest_link;
}