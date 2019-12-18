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
struct TYPE_8__ {TYPE_1__* array; } ;
typedef  TYPE_2__ ldns_radix_node_t ;
struct TYPE_7__ {scalar_t__ edge; } ;

/* Variables and functions */
 TYPE_2__* ldns_radix_last_in_subtree_incl_self (TYPE_2__*) ; 

__attribute__((used)) static ldns_radix_node_t*
ldns_radix_prev_from_index(ldns_radix_node_t* node, uint8_t index)
{
	uint8_t i = index;
	while (i > 0) {
		i--;
		if (node->array[i].edge) {
			ldns_radix_node_t* prev =
				ldns_radix_last_in_subtree_incl_self(node);
			if (prev) {
				return prev;
			}
		}
	}
	return NULL;
}