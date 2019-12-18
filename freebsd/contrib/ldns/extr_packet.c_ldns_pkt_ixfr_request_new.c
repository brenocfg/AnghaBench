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
typedef  int /*<<< orphan*/  ldns_rr_class ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_IXFR ; 
 int /*<<< orphan*/ * ldns_pkt_authsoa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_pkt_query_new_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

ldns_pkt *
ldns_pkt_ixfr_request_new(ldns_rdf *rr_name, ldns_rr_class rr_class,
	uint16_t flags, ldns_rr* soa)
{
	ldns_rr* authsoa_rr = soa;
	if (!authsoa_rr) {
		authsoa_rr = ldns_pkt_authsoa(rr_name, rr_class);
	}
	return ldns_pkt_query_new_internal(rr_name, LDNS_RR_TYPE_IXFR,
		rr_class, flags, authsoa_rr);
}