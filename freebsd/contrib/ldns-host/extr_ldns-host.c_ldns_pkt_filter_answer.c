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
typedef  scalar_t__ ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_A ; 
 scalar_t__ LDNS_RR_TYPE_AAAA ; 
 scalar_t__ LDNS_RR_TYPE_ANY ; 
 scalar_t__ LDNS_RR_TYPE_AXFR ; 
 scalar_t__ LDNS_RR_TYPE_NS ; 
 scalar_t__ LDNS_RR_TYPE_PTR ; 
 int /*<<< orphan*/ * ldns_pkt_answer (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_rr (int /*<<< orphan*/ *,int) ; 
 int ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_set_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_set_rr_count (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ldns_pkt_filter_answer(ldns_pkt *pkt, ldns_rr_type type) {
    int i, j, cnt;
    ldns_rr_list *rrlist;
    ldns_rr *rr;
    ldns_rr_type rrtype;

    rrlist = ldns_pkt_answer(pkt);
    cnt = ldns_rr_list_rr_count(rrlist);
    for (i = j = 0; i < cnt; i++) {
        rr = ldns_rr_list_rr(rrlist, i);
        rrtype = ldns_rr_get_type(rr);
        if (type == LDNS_RR_TYPE_ANY ||
            type == rrtype ||
            (type == LDNS_RR_TYPE_AXFR &&
                (rrtype == LDNS_RR_TYPE_A ||
                rrtype == LDNS_RR_TYPE_AAAA ||
                rrtype == LDNS_RR_TYPE_NS ||
                rrtype == LDNS_RR_TYPE_PTR)))
            ldns_rr_list_set_rr(rrlist, rr, j++);
    }
    ldns_rr_list_set_rr_count(rrlist, j);
}