#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_dnssec_trust_tree ;
struct TYPE_4__ {TYPE_2__* parent; int /*<<< orphan*/ * rrset; } ;
typedef  TYPE_1__ ldns_dnssec_data_chain ;
struct TYPE_5__ {int /*<<< orphan*/ * rrset; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_DNSKEY ; 
 scalar_t__ LDNS_RR_TYPE_DS ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/ * ldns_dnssec_derive_trust_tree_time (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_dnssec_trust_tree_add_parent (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_compare_ds (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_rr (int /*<<< orphan*/ *,size_t) ; 
 size_t ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 

void
ldns_dnssec_derive_trust_tree_ds_rrset_time(
		ldns_dnssec_trust_tree *new_tree,
		ldns_dnssec_data_chain *data_chain, 
		ldns_rr *cur_rr,
		time_t check_time)
{
	size_t j, h;
	ldns_rr_list *cur_rrset = data_chain->rrset;
	ldns_dnssec_trust_tree *cur_parent_tree;
	ldns_rr *cur_parent_rr;

	/* try the parent to see whether there are DSs there */
	if (ldns_rr_get_type(cur_rr) == LDNS_RR_TYPE_DNSKEY &&
	    data_chain->parent &&
	    data_chain->parent->rrset
	    ) {
		for (j = 0;
			j < ldns_rr_list_rr_count(data_chain->parent->rrset);
			j++) {
			cur_parent_rr = ldns_rr_list_rr(data_chain->parent->rrset, j);
			if (ldns_rr_get_type(cur_parent_rr) == LDNS_RR_TYPE_DS) {
				for (h = 0; h < ldns_rr_list_rr_count(cur_rrset); h++) {
					cur_rr = ldns_rr_list_rr(cur_rrset, h);
					if (ldns_rr_compare_ds(cur_rr, cur_parent_rr)) {
						cur_parent_tree =
							ldns_dnssec_derive_trust_tree_time(
							    data_chain->parent, 
							    cur_parent_rr,
							    check_time);
						(void) ldns_dnssec_trust_tree_add_parent(
						            new_tree,
						            cur_parent_tree,
						            NULL,
						            LDNS_STATUS_OK);
					} else {
						/*ldns_rr_print(stdout, cur_parent_rr);*/
					}
				}
			}
		}
	}
}