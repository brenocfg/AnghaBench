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
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 scalar_t__ LDNS_RESOLV_INET ; 
 scalar_t__ LDNS_RESOLV_INET6 ; 
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 scalar_t__ LDNS_RR_TYPE_A ; 
 scalar_t__ LDNS_RR_TYPE_AAAA ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_SOA ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/ ** alloca (size_t) ; 
 int /*<<< orphan*/  doquery (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_get_rr_list_addr_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_pkt_answer (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_resolver_ip6 (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_resolver_push_nameserver_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_remove_nameservers (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_rr (int /*<<< orphan*/ *,size_t) ; 
 size_t ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_ns_nsdname (int /*<<< orphan*/ *) ; 
 int o_print_pkt_server ; 
 int o_recursive ; 
 int /*<<< orphan*/  o_rrtype ; 
 int /*<<< orphan*/ * search (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int) ; 

__attribute__((used)) static bool
dosoa(ldns_resolver *res, ldns_rdf *domain, bool absolute) {
    ldns_rr_list *answer, **nsaddrs;
    ldns_rdf *dname, *addr;
    ldns_pkt *pkt;
    ldns_rr *rr;
    size_t i, j, n, cnt;

    if ((dname = search(res, domain, &pkt, absolute, true)) == NULL)
        return false;

    answer = ldns_pkt_answer(pkt);
    cnt = ldns_rr_list_rr_count(answer);
    nsaddrs = alloca(cnt*sizeof(*nsaddrs));
    for (n = 0, i = 0; i < cnt; i++)
        if ((addr = ldns_rr_ns_nsdname(ldns_rr_list_rr(answer, i))) != NULL)
            nsaddrs[n++] = ldns_get_rr_list_addr_by_name(res, 
                addr, LDNS_RR_CLASS_IN, 0); 

    o_print_pkt_server = false;
    o_recursive = false;
    o_rrtype = LDNS_RR_TYPE_SOA;
    for (i = 0; i < n; i++) {
        cnt = ldns_rr_list_rr_count(nsaddrs[i]);
        for (j = 0; j < cnt; j++) {
            ldns_resolver_remove_nameservers(res);
            rr = ldns_rr_list_rr(nsaddrs[i], j);
            if ((ldns_resolver_ip6(res) == LDNS_RESOLV_INET &&
                ldns_rr_get_type(rr) == LDNS_RR_TYPE_AAAA) ||
                (ldns_resolver_ip6(res) == LDNS_RESOLV_INET6 &&
                ldns_rr_get_type(rr) == LDNS_RR_TYPE_A))
                continue;
            if (ldns_resolver_push_nameserver_rr(res, rr) == LDNS_STATUS_OK)
                /* bind9-host queries for domain, not dname here */
                doquery(res, dname);
        }
    }
    return 0;
}