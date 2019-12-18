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
typedef  size_t uint8_t ;
struct TYPE_9__ {size_t parent_index; size_t len; TYPE_1__* array; struct TYPE_9__* parent; } ;
typedef  TYPE_2__ ldns_radix_node_t ;
struct TYPE_8__ {int /*<<< orphan*/ * edge; scalar_t__ len; int /*<<< orphan*/ * str; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ldns_radix_node_array_free (TYPE_2__*) ; 
 int /*<<< orphan*/  ldns_radix_node_array_free_end (TYPE_2__*) ; 
 int /*<<< orphan*/  ldns_radix_node_array_free_front (TYPE_2__*) ; 
 int /*<<< orphan*/  ldns_radix_node_free (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ldns_radix_cleanup_leaf(ldns_radix_node_t* node)
{
	uint8_t parent_index = node->parent_index;
	ldns_radix_node_t* parent = node->parent;
	/** Delete lead node and fix parent array. */
	assert(parent_index < parent->len);
	ldns_radix_node_free(node, NULL);
	LDNS_FREE(parent->array[parent_index].str);
	parent->array[parent_index].str = NULL;
	parent->array[parent_index].len = 0;
	parent->array[parent_index].edge = NULL;
	/** Fix array in parent. */
	if (parent->len == 1) {
		ldns_radix_node_array_free(parent);
	} else if (parent_index == 0) {
		ldns_radix_node_array_free_front(parent);
	} else {
		ldns_radix_node_array_free_end(parent);
	}
	return;
}