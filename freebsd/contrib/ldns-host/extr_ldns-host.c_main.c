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
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
typedef  scalar_t__ ldns_status ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 scalar_t__ DEFAULT_TCP_TIMEOUT ; 
 scalar_t__ DEFAULT_UDP_TIMEOUT ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_PTR ; 
 scalar_t__ LDNS_STATUS_MEM_ERR ; 
 scalar_t__ LDNS_STATUS_OK ; 
 scalar_t__ M_AXFR ; 
 scalar_t__ M_IXFR ; 
 scalar_t__ M_SINGLE_Q ; 
 scalar_t__ M_SOA ; 
 int /*<<< orphan*/  die (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  doquery (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dosearch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dosoa (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dozonetransfer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ldns_get_errorstr_by_id (scalar_t__) ; 
 int /*<<< orphan*/ * ldns_rdf_reverse_a (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ldns_rdf_reverse_aaaa (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ ldns_resolver_nameserver_count (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_resolver_new_default (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ldns_resolver_push_default_servers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_set_defnames (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_resolver_set_fallback (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_resolver_set_ip6 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_resolver_set_retry (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ldns_resolver_set_timeout (int /*<<< orphan*/ *,struct timeval) ; 
 int /*<<< orphan*/  ldns_resolver_set_usevc (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ldns_str2rdf_a (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_str2rdf_aaaa (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ ndots (int /*<<< orphan*/ ) ; 
 scalar_t__ o_ip6_int ; 
 int /*<<< orphan*/  o_ipversion ; 
 scalar_t__ o_mode ; 
 int /*<<< orphan*/  o_name ; 
 scalar_t__ o_ndots ; 
 scalar_t__ o_retries ; 
 int /*<<< orphan*/  o_rrtype ; 
 scalar_t__ o_server ; 
 scalar_t__ o_tcp ; 
 scalar_t__ o_timeout ; 
 int /*<<< orphan*/  parse_args (int,char**) ; 
 int /*<<< orphan*/  resolver_set_nameserver_str (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  safe_str2rdf_dname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
main(int argc, char *argv[]) {
    ldns_rdf *addr, *dname;
    ldns_resolver *res;
    ldns_status status;
    struct timeval restimeout;

    parse_args(argc, argv);

    status = ldns_resolver_new_default(&res);
    if (status != LDNS_STATUS_OK)
        die(1, "error creating resolver: %s", ldns_get_errorstr_by_id(status));
    if (ldns_resolver_nameserver_count(res) == 0)
        ldns_resolver_push_default_servers(res);

    ldns_resolver_set_usevc(res, o_tcp);
    restimeout.tv_sec = o_timeout > 0 ? o_timeout :
        o_tcp ? DEFAULT_TCP_TIMEOUT : DEFAULT_UDP_TIMEOUT;
    restimeout.tv_usec = 0;
    ldns_resolver_set_timeout(res, restimeout);
    ldns_resolver_set_retry(res, o_retries+1);
    ldns_resolver_set_ip6(res, o_ipversion);
    ldns_resolver_set_defnames(res, false);
    ldns_resolver_set_fallback(res, false);

    if (o_server)
        resolver_set_nameserver_str(res, o_server);

    if (ldns_str2rdf_a(&addr, o_name) == LDNS_STATUS_OK) {
        dname = ldns_rdf_reverse_a(addr, "in-addr.arpa");
        if (dname == NULL)
            die(1, "can't reverse '%s': %s", o_name,
                ldns_get_errorstr_by_id(LDNS_STATUS_MEM_ERR));
        o_mode = M_SINGLE_Q;
        o_rrtype = LDNS_RR_TYPE_PTR;
        return !doquery(res, dname);
    } else if (ldns_str2rdf_aaaa(&addr, o_name) == LDNS_STATUS_OK) {
        dname = ldns_rdf_reverse_aaaa(addr, o_ip6_int ? "ip6.int" : "ip6.arpa");
        if (dname == NULL)
            die(1, "can't reverse '%s': %s", o_name,
                ldns_get_errorstr_by_id(LDNS_STATUS_MEM_ERR));
        o_mode = M_SINGLE_Q;
        o_rrtype = LDNS_RR_TYPE_PTR;
        return !doquery(res, dname);
    }
    return !(o_mode == M_SOA ? dosoa :
             o_mode == M_AXFR ? dozonetransfer :
             o_mode == M_IXFR ? dozonetransfer :
             dosearch)
        (res, safe_str2rdf_dname(o_name), ndots(o_name) >= o_ndots);
}