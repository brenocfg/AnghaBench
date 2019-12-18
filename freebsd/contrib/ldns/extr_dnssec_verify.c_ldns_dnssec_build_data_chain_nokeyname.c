#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt ;
struct TYPE_5__ {TYPE_4__* parent; } ;
typedef  TYPE_1__ ldns_dnssec_data_chain ;
struct TYPE_6__ {int /*<<< orphan*/  packet_qtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_DS ; 
 TYPE_4__* ldns_dnssec_build_data_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_pkt_ancount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_resolver_query (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_rr_list_rr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_list_rr_count (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_rr_owner (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ldns_dnssec_data_chain *
ldns_dnssec_build_data_chain_nokeyname(ldns_resolver *res,
                                       uint16_t qflags,
                                       ldns_rr *orig_rr,
                                       const ldns_rr_list *rrset,
                                       ldns_dnssec_data_chain *new_chain)
{
	ldns_rdf *possible_parent_name;
	ldns_pkt *my_pkt;
	/* apparently we were not able to find a signing key, so
	   we assume the chain ends here
	*/
	/* try parents for auth denial of DS */
	if (orig_rr) {
		possible_parent_name = ldns_rr_owner(orig_rr);
	} else if (rrset && ldns_rr_list_rr_count(rrset) > 0) {
		possible_parent_name = ldns_rr_owner(ldns_rr_list_rr(rrset, 0));
	} else {
		/* no information to go on, give up */
		return new_chain;
	}

	my_pkt = ldns_resolver_query(res,
	              possible_parent_name,
	              LDNS_RR_TYPE_DS,
	              LDNS_RR_CLASS_IN,
	              qflags);
	if (!my_pkt) {
		return new_chain;
	}

	if (ldns_pkt_ancount(my_pkt) > 0) {
		/* add error, no sigs but DS in parent */
		/*ldns_pkt_print(stdout, my_pkt);*/
		ldns_pkt_free(my_pkt);
	} else {
		/* are there signatures? */
		new_chain->parent =  ldns_dnssec_build_data_chain(res, 
		                          qflags, 
		                          NULL,
		                          my_pkt,
		                          NULL);

		new_chain->parent->packet_qtype = LDNS_RR_TYPE_DS;
		
	}
	return new_chain;
}