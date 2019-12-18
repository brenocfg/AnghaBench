#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ root; } ;
typedef  TYPE_1__ ldns_radix_t ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  ldns_radix_node_free ; 
 int /*<<< orphan*/  ldns_radix_traverse_postorder (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
ldns_radix_free(ldns_radix_t* tree)
{
	if (tree) {
		if (tree->root) {
			ldns_radix_traverse_postorder(tree->root,
				ldns_radix_node_free, NULL);
		}
		LDNS_FREE(tree);
	}
	return;
}