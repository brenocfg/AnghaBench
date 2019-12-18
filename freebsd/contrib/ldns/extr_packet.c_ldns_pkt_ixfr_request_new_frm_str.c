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
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_class ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_IXFR ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/ * ldns_pkt_authsoa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_query_new_frm_str_internal (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_str2rdf_dname (int /*<<< orphan*/ **,char const*) ; 

ldns_status
ldns_pkt_ixfr_request_new_frm_str(ldns_pkt **p, const char *name,
	ldns_rr_class rr_class, uint16_t flags, ldns_rr *soa)
{
	ldns_rr* authsoa_rr = soa;
	if (!authsoa_rr) {
		ldns_rdf *name_rdf;
		if (ldns_str2rdf_dname(&name_rdf, name) == LDNS_STATUS_OK) {
			authsoa_rr = ldns_pkt_authsoa(name_rdf, rr_class);
		}
		ldns_rdf_free(name_rdf);
	}
	return ldns_pkt_query_new_frm_str_internal(p, name, LDNS_RR_TYPE_IXFR,
		rr_class, flags, authsoa_rr);
}