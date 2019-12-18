#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct regional {int dummy; } ;
struct query_info {int dummy; } ;
struct dns_msg {int dummy; } ;
struct auth_zone {int dummy; } ;
struct auth_rrset {scalar_t__ type; } ;
struct auth_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_DNAME ; 
 scalar_t__ LDNS_RR_TYPE_NS ; 
 scalar_t__ az_empty_nonterminal (struct auth_zone*,struct query_info*,struct auth_data*) ; 
 struct auth_data* az_find_wildcard (struct auth_zone*,struct query_info*,struct auth_data*) ; 
 int az_generate_dname_answer (struct auth_zone*,struct query_info*,struct regional*,struct dns_msg*,struct auth_data*,struct auth_rrset*) ; 
 int az_generate_notype_answer (struct auth_zone*,struct regional*,struct dns_msg*,struct auth_data*) ; 
 int az_generate_nxdomain_answer (struct auth_zone*,struct regional*,struct dns_msg*,struct auth_data*,struct auth_data*) ; 
 int az_generate_referral_answer (struct auth_zone*,struct regional*,struct dns_msg*,struct auth_data*,struct auth_rrset*) ; 
 int az_generate_wildcard_answer (struct auth_zone*,struct query_info*,struct regional*,struct dns_msg*,struct auth_data*,struct auth_data*,struct auth_data*) ; 

__attribute__((used)) static int
az_generate_answer_nonexistnode(struct auth_zone* z, struct query_info* qinfo,
	struct regional* region, struct dns_msg* msg, struct auth_data* ce,
	struct auth_rrset* rrset, struct auth_data* node)
{
	struct auth_data* wildcard;

	/* we do not have an exact matching name (that exists) */
	/* see if we have a NS or DNAME in the ce */
	if(ce && rrset && rrset->type == LDNS_RR_TYPE_NS) {
		return az_generate_referral_answer(z, region, msg, ce, rrset);
	}
	if(ce && rrset && rrset->type == LDNS_RR_TYPE_DNAME) {
		return az_generate_dname_answer(z, qinfo, region, msg, ce,
			rrset);
	}
	/* if there is an empty nonterminal, wildcard and nxdomain don't
	 * happen, it is a notype answer */
	if(az_empty_nonterminal(z, qinfo, node)) {
		return az_generate_notype_answer(z, region, msg, node);
	}
	/* see if we have a wildcard under the ce */
	if((wildcard=az_find_wildcard(z, qinfo, ce)) != NULL) {
		return az_generate_wildcard_answer(z, qinfo, region, msg,
			ce, wildcard, node);
	}
	/* generate nxdomain answer */
	return az_generate_nxdomain_answer(z, region, msg, ce, node);
}