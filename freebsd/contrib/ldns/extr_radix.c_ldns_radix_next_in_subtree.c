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
typedef  size_t uint16_t ;
struct TYPE_6__ {size_t len; TYPE_1__* array; scalar_t__ data; } ;
typedef  TYPE_2__ ldns_radix_node_t ;
struct TYPE_5__ {TYPE_2__* edge; } ;

/* Variables and functions */

__attribute__((used)) static ldns_radix_node_t*
ldns_radix_next_in_subtree(ldns_radix_node_t* node)
{
	uint16_t i;
	ldns_radix_node_t* next;
	/** Try every subnode. */
	for (i = 0; i < node->len; i++) {
		if (node->array[i].edge) {
			/** Node itself. */
			if (node->array[i].edge->data) {
				return node->array[i].edge;
			}
			/** Dive into subtree. */
			next = ldns_radix_next_in_subtree(node->array[i].edge);
			if (next) {
				return next;
			}
		}
	}
	return NULL;
}