#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ ldns_rr_type ;
typedef  int /*<<< orphan*/  const ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr_class ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  const ldns_pkt ;
struct TYPE_8__ {int packet_nodata; int /*<<< orphan*/  rrset; void* packet_qtype; int /*<<< orphan*/  packet_rcode; struct TYPE_8__* parent; } ;
typedef  TYPE_1__ ldns_dnssec_data_chain ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_DNSKEY ; 
 scalar_t__ LDNS_RR_TYPE_NSEC ; 
 scalar_t__ LDNS_RR_TYPE_NSEC3 ; 
 int /*<<< orphan*/  LDNS_SECTION_ANY_NOQUESTION ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_dnssec_build_data_chain_dnskey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ldns_dnssec_build_data_chain_nokeyname (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int /*<<< orphan*/  ldns_dnssec_build_data_chain_other (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 TYPE_1__* ldns_dnssec_data_chain_new () ; 
 int /*<<< orphan*/  const* ldns_dnssec_pkt_get_rrsigs_for_name_and_type (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  const* ldns_dnssec_pkt_get_rrsigs_for_type (int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  ldns_dnssec_pkt_has_rrsigs (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_pkt_ancount (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_pkt_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_pkt_get_rcode (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* ldns_pkt_rr_list_by_type (int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* ldns_resolver_query (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_get_class (int /*<<< orphan*/ *) ; 
 void* ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_clone (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rr_list_deep_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rr_list_new () ; 
 int /*<<< orphan*/  ldns_rr_list_push_rr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_rr (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_list_rr_count (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_rr_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_rdf (int /*<<< orphan*/ *,int) ; 

ldns_dnssec_data_chain *
ldns_dnssec_build_data_chain(ldns_resolver *res,
					    uint16_t qflags,
					    const ldns_rr_list *rrset,
					    const ldns_pkt *pkt,
					    ldns_rr *orig_rr)
{
	ldns_rr_list *signatures = NULL;
	ldns_rr_list *dss = NULL;
	
	ldns_rr_list *my_rrset;

	ldns_pkt *my_pkt;

	ldns_rdf *name = NULL, *key_name = NULL;
	ldns_rr_type type = 0;
	ldns_rr_class c = 0;

	bool other_rrset = false;

	ldns_dnssec_data_chain *new_chain = ldns_dnssec_data_chain_new();

	assert(pkt != NULL);

	if (!ldns_dnssec_pkt_has_rrsigs(pkt)) {
		/* hmm. no dnssec data in the packet. go up to try and deny
		 * DS? */
		return new_chain;
	}

	if (orig_rr) {
		new_chain->rrset = ldns_rr_list_new();
		ldns_rr_list_push_rr(new_chain->rrset, orig_rr);
		new_chain->parent = ldns_dnssec_build_data_chain(res,
											    qflags,
											    rrset,
											    pkt,
											    NULL);
		new_chain->packet_rcode = ldns_pkt_get_rcode(pkt);
		new_chain->packet_qtype = ldns_rr_get_type(orig_rr);
		if (ldns_pkt_ancount(pkt) == 0) {
			new_chain->packet_nodata = true;
		}
		return new_chain;
	}
	
	if (!rrset || ldns_rr_list_rr_count(rrset) < 1) {
		/* hmm, no data, do we have denial? only works if pkt was given,
		   otherwise caller has to do the check himself */
		new_chain->packet_nodata = true;
		if (pkt) {
			my_rrset = ldns_pkt_rr_list_by_type(pkt,
										 LDNS_RR_TYPE_NSEC,
										 LDNS_SECTION_ANY_NOQUESTION
										 );
			if (my_rrset) {
				if (ldns_rr_list_rr_count(my_rrset) > 0) {
					type = LDNS_RR_TYPE_NSEC;
					other_rrset = true;
				} else {
					ldns_rr_list_deep_free(my_rrset);
					my_rrset = NULL;
				}
			} else {
				/* nothing, try nsec3 */
				my_rrset = ldns_pkt_rr_list_by_type(pkt,
						     LDNS_RR_TYPE_NSEC3,
							LDNS_SECTION_ANY_NOQUESTION);
				if (my_rrset) {
					if (ldns_rr_list_rr_count(my_rrset) > 0) {
						type = LDNS_RR_TYPE_NSEC3;
						other_rrset = true;
					} else {
						ldns_rr_list_deep_free(my_rrset);
						my_rrset = NULL;
					}
				} else {
					/* nothing, stop */
					/* try parent zone? for denied insecure? */
					return new_chain;
				}
			}
		} else {
			return new_chain;
		}
	} else {
		my_rrset = (ldns_rr_list *) rrset;
	}
	
	if (my_rrset && ldns_rr_list_rr_count(my_rrset) > 0) {
		new_chain->rrset = ldns_rr_list_clone(my_rrset);
		name = ldns_rr_owner(ldns_rr_list_rr(my_rrset, 0));
		type = ldns_rr_get_type(ldns_rr_list_rr(my_rrset, 0));
		c = ldns_rr_get_class(ldns_rr_list_rr(my_rrset, 0));
	}
	
	if (other_rrset) {
		ldns_rr_list_deep_free(my_rrset);
	}
	
	/* normally there will only be 1 signature 'set'
	   but there can be more than 1 denial (wildcards)
	   so check for NSEC
	*/
	if (type == LDNS_RR_TYPE_NSEC || type == LDNS_RR_TYPE_NSEC3) {
		/* just throw in all signatures, the tree builder must sort
		   this out */
		if (pkt) {
			signatures = ldns_dnssec_pkt_get_rrsigs_for_type(pkt, type);
		} else {
			my_pkt = ldns_resolver_query(res, name, type, c, qflags);
			if (my_pkt) {
			signatures = ldns_dnssec_pkt_get_rrsigs_for_type(pkt, type);
			ldns_pkt_free(my_pkt);
			}
		}
	} else {
		if (pkt) {
			signatures =
				ldns_dnssec_pkt_get_rrsigs_for_name_and_type(pkt,
													name,
													type);
		}
		if (!signatures) {
			my_pkt = ldns_resolver_query(res, name, type, c, qflags);
			if (my_pkt) {
			signatures =
				ldns_dnssec_pkt_get_rrsigs_for_name_and_type(my_pkt,
													name,
													type);
			ldns_pkt_free(my_pkt);
			}
		}
	}

	if (signatures && ldns_rr_list_rr_count(signatures) > 0) {
		key_name = ldns_rr_rdf(ldns_rr_list_rr(signatures, 0), 7);
	}
	if (!key_name) {
		if (signatures) {
			ldns_rr_list_deep_free(signatures);
		}
		return ldns_dnssec_build_data_chain_nokeyname(res,
		                                              qflags,
		                                              orig_rr,
		                                              rrset,
		                                              new_chain);
	}
	if (type != LDNS_RR_TYPE_DNSKEY) {
		ldns_dnssec_build_data_chain_dnskey(res,
		                                    qflags,
		                                    pkt,
		                                    signatures,
		                                    new_chain,
		                                    key_name,
		                                    c
		                                   );
	} else {
		ldns_dnssec_build_data_chain_other(res,
		                                   qflags,
		                                   new_chain,
		                                   key_name,
		                                   c,
		                                   dss
		                                  );
	}
	if (signatures) {
		ldns_rr_list_deep_free(signatures);
	}
	return new_chain;
}