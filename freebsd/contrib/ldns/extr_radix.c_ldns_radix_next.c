#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_8__ {size_t len; size_t parent_index; TYPE_1__* array; scalar_t__ data; struct TYPE_8__* parent; } ;
typedef  TYPE_2__ ldns_radix_node_t ;
struct TYPE_7__ {TYPE_2__* edge; } ;

/* Variables and functions */
 TYPE_2__* ldns_radix_next_in_subtree (TYPE_2__*) ; 

ldns_radix_node_t*
ldns_radix_next(ldns_radix_node_t* node)
{
	if (!node) {
		return NULL;
	}
	if (node->len) {
		/** Go down: most-left child is the next. */
		ldns_radix_node_t* next = ldns_radix_next_in_subtree(node);
		if (next) {
			return next;
		}
	}
	/** No elements in subtree, get to parent and go down next branch. */
	while (node->parent) {
		uint8_t index = node->parent_index;
		node = node->parent;
		index++;
		for (; index < node->len; index++) {
			if (node->array[index].edge) {
				ldns_radix_node_t* next;
				/** Node itself. */
				if (node->array[index].edge->data) {
					return node->array[index].edge;
				}
				/** Dive into subtree. */
				next = ldns_radix_next_in_subtree(node);
				if (next) {
					return next;
				}
			}
		}
	}
	return NULL;
}