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
struct TYPE_7__ {TYPE_2__* root; } ;
typedef  TYPE_1__ ldns_radix_t ;
struct TYPE_8__ {scalar_t__ data; } ;
typedef  TYPE_2__ ldns_radix_node_t ;

/* Variables and functions */
 TYPE_2__* ldns_radix_next (TYPE_2__*) ; 

ldns_radix_node_t*
ldns_radix_first(const ldns_radix_t* tree)
{
	ldns_radix_node_t* first = NULL;
	if (!tree || !tree->root) {
		return NULL;
	}
	first = tree->root;
	if (first->data) {
		return first;
	}
	return ldns_radix_next(first);
}