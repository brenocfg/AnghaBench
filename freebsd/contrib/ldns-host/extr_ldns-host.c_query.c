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
typedef  scalar_t__ ldns_status ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  scalar_t__ ldns_pkt_rcode ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 scalar_t__ LDNS_RCODE_NOERROR ; 
 scalar_t__ LDNS_RCODE_SERVFAIL ; 
 int /*<<< orphan*/  LDNS_RD ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ ldns_pkt_get_rcode (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_pkt_tc (int /*<<< orphan*/ *) ; 
 int ldns_resolver_nameserver_count (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_resolver_send_to (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ldns_resolver_set_usevc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_resolver_usevc (int /*<<< orphan*/ *) ; 
 scalar_t__ o_ignore_servfail ; 
 int /*<<< orphan*/  o_ixfr_serial ; 
 scalar_t__ o_recursive ; 
 int /*<<< orphan*/  o_rrclass ; 
 int /*<<< orphan*/  o_rrtype ; 
 scalar_t__ o_verbose ; 
 int /*<<< orphan*/  print_rdf_nodot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static bool
query(ldns_resolver *res, ldns_rdf *domain, ldns_pkt **pkt, bool close_tcp) {
    ldns_status status;
    ldns_pkt_rcode rcode;
    int i, cnt;

    if (o_verbose) {
        printf("Trying \"");
        print_rdf_nodot(domain);
        printf("\"\n");
    }
    for (cnt = ldns_resolver_nameserver_count(res), i = 0; i < cnt; i++) {
        status = ldns_resolver_send_to(pkt, res, domain, o_rrtype,
            o_rrclass, o_recursive ? LDNS_RD : 0, o_ixfr_serial, i,
            close_tcp);
        if (status != LDNS_STATUS_OK) {
            *pkt = NULL;
            continue;
        }
        if (ldns_pkt_tc(*pkt) && !ldns_resolver_usevc(res)) {
            if (o_verbose)
                printf(";; Truncated, retrying in TCP mode.\n");
            ldns_resolver_set_usevc(res, true);
            status = ldns_resolver_send_to(pkt, res, domain, o_rrtype,
                o_rrclass, o_recursive ? LDNS_RD : 0, o_ixfr_serial, i,
                close_tcp);
            ldns_resolver_set_usevc(res, false);
            if (status != LDNS_STATUS_OK)
                continue;
        }
        rcode = ldns_pkt_get_rcode(*pkt);
        if (o_ignore_servfail && rcode == LDNS_RCODE_SERVFAIL && cnt > 1)
            continue;
        return rcode == LDNS_RCODE_NOERROR;
    }
    if (*pkt == NULL) {
        printf(";; connection timed out; no servers could be reached\n");
        exit(1);
    }
    return false;
}