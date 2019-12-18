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
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr ;
struct TYPE_4__ {size_t parent_count; int /*<<< orphan*/ ** parent_signature; int /*<<< orphan*/ * parent_status; struct TYPE_4__** parents; } ;
typedef  TYPE_1__ ldns_dnssec_trust_tree ;

/* Variables and functions */
 size_t LDNS_DNSSEC_TRUST_TREE_MAX_PARENTS ; 
 int /*<<< orphan*/  LDNS_STATUS_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 

ldns_status
ldns_dnssec_trust_tree_add_parent(ldns_dnssec_trust_tree *tree,
                                  const ldns_dnssec_trust_tree *parent,
                                  const ldns_rr *signature,
                                  const ldns_status parent_status)
{
	if (tree
	    && parent
	    && tree->parent_count < LDNS_DNSSEC_TRUST_TREE_MAX_PARENTS) {
		/*
		  printf("Add parent for: ");
		  ldns_rr_print(stdout, tree->rr);
		  printf("parent: ");
		  ldns_rr_print(stdout, parent->rr);
		*/
		tree->parents[tree->parent_count] =
			(ldns_dnssec_trust_tree *) parent;
		tree->parent_status[tree->parent_count] = parent_status;
		tree->parent_signature[tree->parent_count] = (ldns_rr *) signature;
		tree->parent_count++;
		return LDNS_STATUS_OK;
	} else {
		return LDNS_STATUS_ERR;
	}
}