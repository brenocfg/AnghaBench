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
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/ * ldns_pkt_answer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_answerfrom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_rr (int /*<<< orphan*/ *,size_t) ; 
 size_t ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_rdf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_rr_short (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
print_pkt_short(ldns_pkt *pkt, bool print_rr_server) {
    ldns_rr_list *rrlist = ldns_pkt_answer(pkt);
    size_t i;

    for (i = 0; i < ldns_rr_list_rr_count(rrlist); i++) {
        if (print_rr_server) {
            printf("Nameserver ");
            print_rdf(ldns_pkt_answerfrom(pkt));
            printf(":\n\t");
        }
        print_rr_short(ldns_rr_list_rr(rrlist, i));
    }
}