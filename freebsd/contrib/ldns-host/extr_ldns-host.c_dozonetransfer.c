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
typedef  int /*<<< orphan*/  ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 scalar_t__ LDNS_RCODE_NOERROR ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_AXFR ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_IXFR ; 
 scalar_t__ LDNS_RR_TYPE_SOA ; 
 scalar_t__ LDNS_STATUS_OK ; 
 scalar_t__ M_AXFR ; 
 scalar_t__ M_IXFR ; 
 int /*<<< orphan*/  ldns_pkt_answer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_answerfrom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_filter_answer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_pkt_get_rcode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_set_answerfrom (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rdf_clone (int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_clone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_rr (int /*<<< orphan*/ *,size_t) ; 
 size_t ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rr_soa_get_serial (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_tcp_close (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_tcp_read (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ o_ixfr_serial ; 
 scalar_t__ o_mode ; 
 int /*<<< orphan*/  o_rrtype ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  report (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * search (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int) ; 

__attribute__((used)) static bool
dozonetransfer(ldns_resolver *res, ldns_rdf *domain, bool absolute) {
    ldns_pkt *pkt, *nextpkt;
    ldns_rdf *dname;
    ldns_rr_type rrtype;
    ldns_rr_list *rrl;
    ldns_rr *rr;
    size_t i, nsoa = 0;
    uint32_t first_serial = 0;

    rrtype = o_rrtype;
    o_rrtype = (o_mode == M_AXFR) ? LDNS_RR_TYPE_AXFR : LDNS_RR_TYPE_IXFR;
    dname = search(res, domain, &pkt, absolute, false);

    for (;;) {
        rrl = ldns_rr_list_clone(ldns_pkt_answer(pkt));
        ldns_pkt_filter_answer(pkt, rrtype);
        report(res, dname != NULL ? dname : domain, pkt);
        if ((dname == NULL) ||
                (ldns_pkt_get_rcode(pkt) != LDNS_RCODE_NOERROR)) {
            printf("; Transfer failed.\n");
            ldns_tcp_close(res);
            return false;
        }
        for (i = 0; i < ldns_rr_list_rr_count(rrl); i++) {
            rr = ldns_rr_list_rr(rrl, i);
            if (nsoa == 0) {
                if (ldns_rr_get_type(rr) != LDNS_RR_TYPE_SOA) {
                    printf("; Transfer failed. "
                           "Didn't start with SOA answer.\n");
                    ldns_tcp_close(res);
                    return false;
                }
                first_serial = ldns_rr_soa_get_serial(rr);
                if ((o_mode == M_IXFR) && (first_serial <= o_ixfr_serial)) {
                    ldns_tcp_close(res);
                    return true;
                }
            }
            if (ldns_rr_get_type(rr) == LDNS_RR_TYPE_SOA) {
                nsoa = nsoa < 2 ? nsoa + 1 : 1;
                if ((nsoa == 2) &&
                        (ldns_rr_soa_get_serial(rr) == first_serial)) {
                    ldns_tcp_close(res);
                    return true;
                }
            }
        }
        if (ldns_tcp_read(&nextpkt, res) != LDNS_STATUS_OK) {
            printf("; Transfer failed.\n");
            return false;
        }
        ldns_pkt_set_answerfrom(nextpkt,
                ldns_rdf_clone(ldns_pkt_answerfrom(pkt)));
        ldns_pkt_free(pkt);
        ldns_rr_list_free(rrl);
        pkt = nextpkt;
    }
}