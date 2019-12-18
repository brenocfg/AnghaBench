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
struct TYPE_8__ {size_t len; TYPE_1__* array; } ;
typedef  TYPE_2__ ldns_radix_node_t ;
struct TYPE_7__ {TYPE_2__* edge; } ;

/* Variables and functions */
 void stub1 (TYPE_2__*,void*) ; 

void
ldns_radix_traverse_postorder(ldns_radix_node_t* node,
	void (*func)(ldns_radix_node_t*, void*), void* arg)
{
	uint8_t i;
	if (!node) {
		return;
	}
	for (i=0; i < node->len; i++) {
		ldns_radix_traverse_postorder(node->array[i].edge,
			func, arg);
	}
	/** Call user function */
	(*func)(node, arg);
	return;
}