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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RDF_TYPE_TYPE ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_RRSIG ; 
 int /*<<< orphan*/  LDNS_SECTION_ANY_NOQUESTION ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_pkt_rr_list_by_type (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rdf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rdf_new (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_subtype_by_rdf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ldns_rr_list *
ldns_dnssec_pkt_get_rrsigs_for_type(const ldns_pkt *pkt, ldns_rr_type type)
{
	uint16_t t_netorder;
	ldns_rr_list *sigs;
	ldns_rr_list *sigs_covered;
	ldns_rdf *rdf_t;

	sigs = ldns_pkt_rr_list_by_type(pkt,
	                                LDNS_RR_TYPE_RRSIG,
	                                LDNS_SECTION_ANY_NOQUESTION
							  );

	t_netorder = htons(type); /* rdf are in network order! */
	rdf_t = ldns_rdf_new(LDNS_RDF_TYPE_TYPE,
					 2,
					 &t_netorder);
	sigs_covered = ldns_rr_list_subtype_by_rdf(sigs, rdf_t, 0);

	ldns_rdf_free(rdf_t);
	ldns_rr_list_deep_free(sigs);

	return sigs_covered;

}