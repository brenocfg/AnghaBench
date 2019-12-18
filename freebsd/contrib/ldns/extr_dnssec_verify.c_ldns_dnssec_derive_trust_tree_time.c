#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
struct TYPE_14__ {int /*<<< orphan*/ * rrset; int /*<<< orphan*/ * rr; } ;
typedef  TYPE_1__ ldns_dnssec_trust_tree ;
struct TYPE_15__ {scalar_t__ parent; int /*<<< orphan*/ * signatures; int /*<<< orphan*/ * rrset; } ;
typedef  TYPE_2__ ldns_dnssec_data_chain ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_NSEC ; 
 scalar_t__ ldns_dname_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_dnssec_derive_trust_tree_dnskey_rrset_time (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_dnssec_derive_trust_tree_ds_rrset_time (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_dnssec_derive_trust_tree_no_sig_time (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_dnssec_derive_trust_tree_normal_rrset_time (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ldns_dnssec_trust_tree_new () ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_rr (int /*<<< orphan*/ *,size_t) ; 
 size_t ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_owner (int /*<<< orphan*/ *) ; 

ldns_dnssec_trust_tree *
ldns_dnssec_derive_trust_tree_time(
		ldns_dnssec_data_chain *data_chain, 
		ldns_rr *rr, 
		time_t check_time
		)
{
	ldns_rr_list *cur_rrset;
	ldns_rr_list *cur_sigs;
	ldns_rr *cur_rr = NULL;
	ldns_rr *cur_sig_rr;
	size_t i, j;

	ldns_dnssec_trust_tree *new_tree = ldns_dnssec_trust_tree_new();
        if(!new_tree)
                return NULL;
	
	if (data_chain && data_chain->rrset) {
		cur_rrset = data_chain->rrset;
	
		cur_sigs = data_chain->signatures;

		if (rr) {
			cur_rr = rr;
		}

		if (!cur_rr && ldns_rr_list_rr_count(cur_rrset) > 0) {
			cur_rr = ldns_rr_list_rr(cur_rrset, 0);
		}

		if (cur_rr) {
			new_tree->rr = cur_rr;
			new_tree->rrset = cur_rrset;
			/* there are three possibilities:
			   1 - 'normal' rrset, signed by a key
			   2 - dnskey signed by other dnskey
			   3 - dnskey proven by higher level DS
			   (data denied by nsec is a special case that can
			   occur in multiple places)
				   
			*/
			if (cur_sigs) {
				for (i = 0; i < ldns_rr_list_rr_count(cur_sigs); i++) {
					/* find the appropriate key in the parent list */
					cur_sig_rr = ldns_rr_list_rr(cur_sigs, i);

					if (ldns_rr_get_type(cur_rr) == LDNS_RR_TYPE_NSEC) {
						if (ldns_dname_compare(ldns_rr_owner(cur_sig_rr),
										   ldns_rr_owner(cur_rr)))
							{
								/* find first that does match */

								for (j = 0;
								     j < ldns_rr_list_rr_count(cur_rrset) && 
										ldns_dname_compare(ldns_rr_owner(cur_sig_rr),ldns_rr_owner(cur_rr)) != 0;
								     j++) {
									cur_rr = ldns_rr_list_rr(cur_rrset, j);
									
								}
								if (ldns_dname_compare(ldns_rr_owner(cur_sig_rr), 
												   ldns_rr_owner(cur_rr)))
									{
										break;
									}
							}
							
					}
					/* option 1 */
					if (data_chain->parent) {
						ldns_dnssec_derive_trust_tree_normal_rrset_time(
						    new_tree,
						    data_chain,
						    cur_sig_rr,
						    check_time);
					}

					/* option 2 */
					ldns_dnssec_derive_trust_tree_dnskey_rrset_time(
					    new_tree,
					    data_chain,
					    cur_rr,
					    cur_sig_rr,
					    check_time);
				}
					
				ldns_dnssec_derive_trust_tree_ds_rrset_time(
						new_tree, data_chain, 
						cur_rr, check_time);
			} else {
				/* no signatures? maybe it's nsec data */
					
				/* just add every rr from parent as new parent */
				ldns_dnssec_derive_trust_tree_no_sig_time(
					new_tree, data_chain, check_time);
			}
		}
	}

	return new_tree;
}