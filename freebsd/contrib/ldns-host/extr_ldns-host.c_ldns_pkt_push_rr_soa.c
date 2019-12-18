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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_class ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  const ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt_section ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RDF_TYPE_DNAME ; 
 int /*<<< orphan*/  LDNS_RDF_TYPE_INT32 ; 
 int /*<<< orphan*/  LDNS_RDF_TYPE_PERIOD ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_SOA ; 
 int /*<<< orphan*/  LDNS_STATUS_MEM_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 scalar_t__ htonl (scalar_t__) ; 
 int /*<<< orphan*/  ldns_pkt_push_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* ldns_rdf_clone (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* ldns_rdf_new_frm_data (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  ldns_rr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_new_frm_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_rr_rdf (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_rr_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_set_owner (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rr_set_rdf (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ldns_rr_set_ttl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ldns_status
ldns_pkt_push_rr_soa(ldns_pkt *pkt, ldns_pkt_section sec,
    const ldns_rdf *name, ldns_rr_class c, uint32_t serial) {
    ldns_rdf *rdf;
    ldns_rr *rr;
    uint32_t n;

    if ((rr = ldns_rr_new_frm_type(LDNS_RR_TYPE_SOA)) == NULL)
        return LDNS_STATUS_MEM_ERR;
    ldns_rr_set_class(rr, c);
    ldns_rr_set_owner(rr, ldns_rdf_clone(name));
    ldns_rr_set_ttl(rr, 0);

    n = 0;
    if ((rdf = ldns_rdf_new_frm_data(LDNS_RDF_TYPE_DNAME, 1, &n)) == NULL)
        goto memerr;
    ldns_rr_set_rdf(rr, rdf, 0);
    ldns_rr_set_rdf(rr, ldns_rdf_clone(rdf), 1);

    n = htonl(serial);
    if ((rdf = ldns_rdf_new_frm_data(LDNS_RDF_TYPE_INT32, 4, &n)) == NULL)
        goto memerr;
    ldns_rr_set_rdf(rr, rdf, 2);

    n = 0;
    if ((rdf = ldns_rdf_new_frm_data(LDNS_RDF_TYPE_PERIOD, 4, &n)) == NULL)
        goto memerr;
    ldns_rr_set_rdf(rr, rdf, 3);
    ldns_rr_set_rdf(rr, ldns_rdf_clone(rdf), 4);
    ldns_rr_set_rdf(rr, ldns_rdf_clone(rdf), 5);
    ldns_rr_set_rdf(rr, ldns_rdf_clone(rdf), 6);

    if (ldns_rr_rdf(rr, 1) == NULL || ldns_rr_rdf(rr, 4) == NULL ||
        ldns_rr_rdf(rr, 5) == NULL || ldns_rr_rdf(rr, 6) == NULL ||
        !ldns_pkt_push_rr(pkt, sec, rr))
        goto memerr;
    return LDNS_STATUS_OK;

memerr:
    ldns_rr_free(rr);
    return LDNS_STATUS_MEM_ERR;
}