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
struct TYPE_6__ {scalar_t__ data; } ;
typedef  TYPE_1__ ldns_radix_node_t ;

/* Variables and functions */
 TYPE_1__* ldns_radix_last_in_subtree (TYPE_1__*) ; 

__attribute__((used)) static ldns_radix_node_t*
ldns_radix_last_in_subtree_incl_self(ldns_radix_node_t* node)
{
	ldns_radix_node_t* last = ldns_radix_last_in_subtree(node);
	if (last) {
		return last;
	} else if (node->data) {
		return node;
	}
	return NULL;
}