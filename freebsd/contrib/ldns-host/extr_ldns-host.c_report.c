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
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  scalar_t__ ldns_pkt_rcode ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 scalar_t__ LDNS_RCODE_NOERROR ; 
 scalar_t__ M_SINGLE_Q ; 
 int /*<<< orphan*/  ldns_pkt_answer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_answerfrom (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_pkt_get_rcode (int /*<<< orphan*/ *) ; 
 int ldns_resolver_port (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rr_list_rr_count (int /*<<< orphan*/ ) ; 
 scalar_t__ o_mode ; 
 int o_print_pkt_server ; 
 int /*<<< orphan*/  o_print_rr_server ; 
 int /*<<< orphan*/  o_rrtype ; 
 char* o_server ; 
 scalar_t__ o_verbose ; 
 int /*<<< orphan*/  print_pkt_short (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_pkt_verbose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_rcode (scalar_t__) ; 
 int /*<<< orphan*/  print_rdf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_rdf_nodot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_received_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_rr_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
report(ldns_resolver *res, ldns_rdf *domain, ldns_pkt *pkt) {
    ldns_pkt_rcode rcode;

    if (o_print_pkt_server) {
        printf("Using domain server:\nName: %s\nAddress: ", o_server);
        print_rdf(ldns_pkt_answerfrom(pkt));
        printf("#%d\nAliases: \n\n", ldns_resolver_port(res));
        o_print_pkt_server = false;
    }
    rcode = ldns_pkt_get_rcode(pkt);
    if (rcode != LDNS_RCODE_NOERROR) {
        printf("Host ");
        print_rdf_nodot(domain);
        printf(" not found: %d(", rcode);
        print_rcode(rcode);
        printf(")\n");
    } else {
        if (o_verbose) {
            print_pkt_verbose(pkt);
        } else {
            print_pkt_short(pkt, o_print_rr_server);
            if (o_mode == M_SINGLE_Q &&
                ldns_rr_list_rr_count(ldns_pkt_answer(pkt)) == 0) {
                print_rdf_nodot(domain);
                printf(" has no ");
                print_rr_type(o_rrtype);
                printf(" record\n");
            }
        }
    }
    if (o_verbose)
        print_received_line(res, pkt);
}