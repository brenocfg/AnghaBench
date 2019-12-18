#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_7__ {int len; TYPE_1__* array; } ;
typedef  TYPE_2__ ldns_radix_node_t ;
struct TYPE_6__ {int /*<<< orphan*/ * edge; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ldns_radix_array_reduce (TYPE_2__*) ; 
 int /*<<< orphan*/  ldns_radix_node_array_free (TYPE_2__*) ; 

__attribute__((used)) static void
ldns_radix_node_array_free_end(ldns_radix_node_t* node)
{
	uint16_t n = 0;
	/** Shorten array. */
	while (n < node->len && node->array[node->len-1-n].edge == NULL) {
		n++;
	}
	if (n == 0) {
		return;
	}
	if (n == node->len) {
		ldns_radix_node_array_free(node);
		return;
	}
	assert(n < node->len);
	node->len -= n;
	ldns_radix_array_reduce(node);
	return;
}