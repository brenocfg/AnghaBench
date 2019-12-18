#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
struct TYPE_9__ {int /*<<< orphan*/  rr; } ;
typedef  TYPE_1__ ldns_dnssec_trust_tree ;
struct TYPE_10__ {TYPE_6__* parent; int /*<<< orphan*/  packet_nodata; int /*<<< orphan*/  packet_qtype; int /*<<< orphan*/  packet_rcode; } ;
typedef  TYPE_2__ ldns_dnssec_data_chain ;
struct TYPE_11__ {int /*<<< orphan*/  signatures; int /*<<< orphan*/ * rrset; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_NSEC ; 
 scalar_t__ LDNS_RR_TYPE_NSEC3 ; 
 int /*<<< orphan*/  LDNS_STATUS_DNSSEC_NSEC_RR_NOT_COVERED ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 TYPE_1__* ldns_dnssec_derive_trust_tree_time (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_dnssec_trust_tree_add_parent (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_dnssec_verify_denial (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_dnssec_verify_denial_nsec3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_rr (int /*<<< orphan*/ *,size_t) ; 
 size_t ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 

void
ldns_dnssec_derive_trust_tree_no_sig_time(
		ldns_dnssec_trust_tree *new_tree, 
		ldns_dnssec_data_chain *data_chain,
		time_t check_time)
{
	size_t i;
	ldns_rr_list *cur_rrset;
	ldns_rr *cur_parent_rr;
	ldns_dnssec_trust_tree *cur_parent_tree;
	ldns_status result;
	
	if (data_chain->parent && data_chain->parent->rrset) {
		cur_rrset = data_chain->parent->rrset;
		/* nsec? */
		if (cur_rrset && ldns_rr_list_rr_count(cur_rrset) > 0) {
			if (ldns_rr_get_type(ldns_rr_list_rr(cur_rrset, 0)) ==
			    LDNS_RR_TYPE_NSEC3) {
				result = ldns_dnssec_verify_denial_nsec3(
					        new_tree->rr,
						   cur_rrset,
						   data_chain->parent->signatures,
						   data_chain->packet_rcode,
						   data_chain->packet_qtype,
						   data_chain->packet_nodata);
			} else if (ldns_rr_get_type(ldns_rr_list_rr(cur_rrset, 0)) ==
					 LDNS_RR_TYPE_NSEC) {
				result = ldns_dnssec_verify_denial(
					        new_tree->rr,
						   cur_rrset,
						   data_chain->parent->signatures);
			} else {
				/* unsigned zone, unsigned parent */
				result = LDNS_STATUS_OK;
			}
		} else {
			result = LDNS_STATUS_DNSSEC_NSEC_RR_NOT_COVERED;
		}
		for (i = 0; i < ldns_rr_list_rr_count(cur_rrset); i++) {
			cur_parent_rr = ldns_rr_list_rr(cur_rrset, i);
			cur_parent_tree = 
				ldns_dnssec_derive_trust_tree_time(
						data_chain->parent, 
						cur_parent_rr,
						check_time);
			(void) ldns_dnssec_trust_tree_add_parent(new_tree,
			            cur_parent_tree, NULL, result);
		}
	}
}