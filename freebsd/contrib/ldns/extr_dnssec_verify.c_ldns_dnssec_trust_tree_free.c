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
struct TYPE_4__ {size_t parent_count; struct TYPE_4__** parents; } ;
typedef  TYPE_1__ ldns_dnssec_trust_tree ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (TYPE_1__*) ; 

void
ldns_dnssec_trust_tree_free(ldns_dnssec_trust_tree *tree)
{
	size_t i;
	if (tree) {
		for (i = 0; i < tree->parent_count; i++) {
			ldns_dnssec_trust_tree_free(tree->parents[i]);
		}
	}
	LDNS_FREE(tree);
}