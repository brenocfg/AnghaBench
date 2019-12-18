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
struct TYPE_6__ {scalar_t__ len; TYPE_1__* array; scalar_t__ data; } ;
typedef  TYPE_2__ ldns_radix_node_t ;
struct TYPE_5__ {TYPE_2__* edge; } ;

/* Variables and functions */

__attribute__((used)) static ldns_radix_node_t*
ldns_radix_last_in_subtree(ldns_radix_node_t* node)
{
	int i;
	/** Look for the most right leaf node. */
	for (i=(int)(node->len)-1; i >= 0; i--) {
		if (node->array[i].edge) {
			/** Keep looking for the most right leaf node. */
			if (node->array[i].edge->len > 0) {
				ldns_radix_node_t* last =
					ldns_radix_last_in_subtree(
					node->array[i].edge);
				if (last) {
					return last;
				}
			}
			/** Could this be the most right leaf node? */
			if (node->array[i].edge->data) {
				return node->array[i].edge;
			}
		}
	}
	return NULL;
}