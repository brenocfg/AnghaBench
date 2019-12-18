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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;
typedef  scalar_t__ ldns_status ;
typedef  scalar_t__ ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr_class ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  const ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_IXFR ; 
 int /*<<< orphan*/  LDNS_SECTION_AUTHORITY ; 
 scalar_t__ LDNS_STATUS_ERR ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/  ldns_pkt_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_pkt_push_rr_soa (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_pkt_query_new (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_answerfrom (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_random_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_set_timestamp (int /*<<< orphan*/ *,struct timeval) ; 
 int /*<<< orphan*/  ldns_rdf_clone (int /*<<< orphan*/  const*) ; 
 int ldns_resolver_nameserver_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const** ldns_resolver_nameservers (int /*<<< orphan*/ *) ; 
 size_t* ldns_resolver_rtt (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_resolver_send_pkt (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_set_nameserver_count (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ldns_resolver_set_nameservers (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  ldns_resolver_set_rtt (int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ ldns_tcp_read (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_tcp_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ldns_status
ldns_resolver_send_to(ldns_pkt **answer, ldns_resolver *res,
    const ldns_rdf *name, ldns_rr_type t, ldns_rr_class c,
    uint16_t flags, uint32_t ixfr_serial, int nameserver,
    bool close_tcp) {
    ldns_status status = LDNS_STATUS_OK;
    ldns_pkt *qpkt;
    struct timeval now;

    int nscnt = ldns_resolver_nameserver_count(res);
    ldns_rdf **ns = ldns_resolver_nameservers(res);
    size_t *rtt = ldns_resolver_rtt(res);

    ldns_resolver_set_nameservers(res, &ns[nameserver]);
    ldns_resolver_set_rtt(res, &rtt[nameserver]);
    ldns_resolver_set_nameserver_count(res, 1);

    /* The next fragment should have been a call to
     * ldns_resolver_prepare_query_pkt(), but starting with ldns
     * version 1.6.17 that function tries to add it's own SOA
     * records when rr_type is LDNS_RR_TYPE_IXFR, and we don't
     * want that.
     */
    qpkt = ldns_pkt_query_new(ldns_rdf_clone(name), t, c, flags);
    if (qpkt == NULL) {
        status = LDNS_STATUS_ERR;
        goto done;
    }
    now.tv_sec = time(NULL);
    now.tv_usec = 0;
    ldns_pkt_set_timestamp(qpkt, now);
    ldns_pkt_set_random_id(qpkt);

    if (t == LDNS_RR_TYPE_IXFR) {
        status = ldns_pkt_push_rr_soa(qpkt,
            LDNS_SECTION_AUTHORITY, name, c, ixfr_serial);
        if (status != LDNS_STATUS_OK) goto done;
    }
    if (close_tcp) {
        status = ldns_resolver_send_pkt(answer, res, qpkt);
    } else {
        status = ldns_tcp_start(res, qpkt, 0);
        if (status != LDNS_STATUS_OK) goto done;
        status = ldns_tcp_read(answer, res);
        if (status != LDNS_STATUS_OK) goto done;
        ldns_pkt_set_answerfrom(*answer, ldns_rdf_clone(ns[0]));
    }

done:
    ldns_pkt_free(qpkt);

    ldns_resolver_set_nameservers(res, ns);
    ldns_resolver_set_rtt(res, rtt);
    ldns_resolver_set_nameserver_count(res, nscnt);
    return status;
}