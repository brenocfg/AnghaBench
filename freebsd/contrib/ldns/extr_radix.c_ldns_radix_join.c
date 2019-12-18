#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ldns_status ;
struct TYPE_11__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ ldns_radix_t ;
struct TYPE_12__ {int /*<<< orphan*/  klen; int /*<<< orphan*/  key; scalar_t__ data; } ;
typedef  TYPE_2__ ldns_radix_node_t ;

/* Variables and functions */
 scalar_t__ LDNS_STATUS_EXISTS_ERR ; 
 scalar_t__ LDNS_STATUS_NO_DATA ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/  ldns_radix_delete (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* ldns_radix_first (TYPE_1__*) ; 
 scalar_t__ ldns_radix_insert (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__* ldns_radix_next (TYPE_2__*) ; 

ldns_status
ldns_radix_join(ldns_radix_t* tree1, ldns_radix_t* tree2)
{
	ldns_radix_node_t* cur_node, *next_node;
	ldns_status status;
	if (!tree2 || !tree2->root) {
		return LDNS_STATUS_OK;
	}
	/** Add all elements from tree2 into tree1. */

	cur_node = ldns_radix_first(tree2);
	while (cur_node) {
		status = LDNS_STATUS_NO_DATA;
		/** Insert current node into tree1 */
		if (cur_node->data) {
			status = ldns_radix_insert(tree1, cur_node->key,
				cur_node->klen, cur_node->data);
			/** Exist errors may occur */
			if (status != LDNS_STATUS_OK &&
			    status != LDNS_STATUS_EXISTS_ERR) {
				return status;
			}
		}
		next_node = ldns_radix_next(cur_node);
		if (status == LDNS_STATUS_OK) {
			(void) ldns_radix_delete(tree2, cur_node->key,
				cur_node->klen);
		}
		cur_node = next_node;
	}

	return LDNS_STATUS_OK;
}