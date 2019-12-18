#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
struct TYPE_8__ {int /*<<< orphan*/ * rrset; int /*<<< orphan*/ * rr; } ;
typedef  TYPE_1__ ldns_dnssec_trust_tree ;
struct TYPE_9__ {int /*<<< orphan*/ * rrset; } ;
typedef  TYPE_2__ ldns_dnssec_data_chain ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_DNSKEY ; 
 scalar_t__ ldns_calc_keytag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_dnssec_trust_tree_add_parent (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ldns_dnssec_trust_tree_new () ; 
 scalar_t__ ldns_rdf2native_int16 (int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_rr (int /*<<< orphan*/ *,size_t) ; 
 size_t ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_rrsig_keytag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_verify_rrsig_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ldns_dnssec_derive_trust_tree_dnskey_rrset_time(
		ldns_dnssec_trust_tree *new_tree, 
		ldns_dnssec_data_chain *data_chain, 
		ldns_rr *cur_rr, 
		ldns_rr *cur_sig_rr,
		time_t check_time)
{
	size_t j;
	ldns_rr_list *cur_rrset = data_chain->rrset;
	ldns_dnssec_trust_tree *cur_parent_tree;
	ldns_rr *cur_parent_rr;
	uint16_t cur_keytag;
	ldns_status cur_status;

	cur_keytag = ldns_rdf2native_int16(ldns_rr_rrsig_keytag(cur_sig_rr));

	for (j = 0; j < ldns_rr_list_rr_count(cur_rrset); j++) {
		cur_parent_rr = ldns_rr_list_rr(cur_rrset, j);
		if (cur_parent_rr != cur_rr &&
		    ldns_rr_get_type(cur_parent_rr) == LDNS_RR_TYPE_DNSKEY) {
			if (ldns_calc_keytag(cur_parent_rr) == cur_keytag
			    ) {
				cur_parent_tree = ldns_dnssec_trust_tree_new();
				cur_parent_tree->rr = cur_parent_rr;
				cur_parent_tree->rrset = cur_rrset;
				cur_status = ldns_verify_rrsig_time(
						cur_rrset, cur_sig_rr, 
						cur_parent_rr, check_time);
				(void) ldns_dnssec_trust_tree_add_parent(new_tree,
				            cur_parent_tree, cur_sig_rr, cur_status);
			}
		}
	}
}