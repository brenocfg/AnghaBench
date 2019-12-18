#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ status; struct TYPE_8__* pre; TYPE_2__* linklist; } ;
typedef  TYPE_1__ cdg_node_t ;
struct TYPE_9__ {struct TYPE_9__* next; scalar_t__ removed; scalar_t__ num_pairs; int /*<<< orphan*/ * srcdest_pairs; TYPE_1__* node; } ;
typedef  TYPE_2__ cdg_link_t ;

/* Variables and functions */
 scalar_t__ BLACK ; 
 scalar_t__ GRAY ; 
 scalar_t__ UNKNOWN ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_1__* get_next_cdg_node (TYPE_1__*) ; 

__attribute__((used)) static cdg_node_t *search_cycle_in_channel_dep_graph(cdg_node_t * cdg,
						     cdg_node_t * start_node)
{
	cdg_node_t *cycle = NULL;
	cdg_node_t *current = start_node, *next_node = NULL, *tmp = NULL;
	cdg_link_t *link = NULL;

	while (current) {
		current->status = GRAY;
		link = current->linklist;
		next_node = NULL;
		while (link) {
			if (link->node->status == UNKNOWN) {
				next_node = link->node;
				break;
			}
			if (link->node->status == GRAY) {
				cycle = link->node;
				goto Exit;
			}
			link = link->next;
		}
		if (next_node) {
			next_node->pre = current;
			current = next_node;
		} else {
			/* found a sink in the graph, go to last node */
			current->status = BLACK;

			/* srcdest_pairs of this node aren't relevant, free the allocated memory */
			link = current->linklist;
			while (link) {
				if (link->num_pairs)
					free(link->srcdest_pairs);
				link->srcdest_pairs = NULL;
				link->num_pairs = 0;
				link->removed = 0;
				link = link->next;
			}

			if (current->pre) {
				tmp = current;
				current = current->pre;
				tmp->pre = NULL;
			} else {
				/* search for other subgraphs in cdg */
				current = get_next_cdg_node(cdg);
				if (!current)
					break;	/* all relevant nodes traversed, no more cycles found */
			}
		}
	}

Exit:
	return cycle;
}