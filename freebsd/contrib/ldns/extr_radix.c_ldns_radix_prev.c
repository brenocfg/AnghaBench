#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {scalar_t__ len; scalar_t__ data; struct TYPE_6__* parent; int /*<<< orphan*/  parent_index; } ;
typedef  TYPE_1__ ldns_radix_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* ldns_radix_prev_from_index (TYPE_1__*,int /*<<< orphan*/ ) ; 

ldns_radix_node_t*
ldns_radix_prev(ldns_radix_node_t* node)
{
	if (!node) {
		return NULL;
	}

	/** Get to parent and go down previous branch. */
	while (node->parent) {
		uint8_t index = node->parent_index;
		ldns_radix_node_t* prev;
		node = node->parent;
		assert(node->len > 0);
		prev = ldns_radix_prev_from_index(node, index);
		if (prev) {
			return prev;
		}
		if (node->data) {
			return node;
		}
	}
	return NULL;
}