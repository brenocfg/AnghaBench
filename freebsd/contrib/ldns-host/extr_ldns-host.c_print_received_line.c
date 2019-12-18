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
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ldns_pkt_answerfrom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_querytime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_size (int /*<<< orphan*/ *) ; 
 char* ldns_rdf2str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_resolver_port (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_received_line(ldns_resolver *res, ldns_pkt *pkt) {
    char *from = ldns_rdf2str(ldns_pkt_answerfrom(pkt));

    printf("Received %zu bytes from %s#%d in %d ms\n",
            ldns_pkt_size(pkt), from, ldns_resolver_port(res),
            ldns_pkt_querytime(pkt));
    free(from);
}