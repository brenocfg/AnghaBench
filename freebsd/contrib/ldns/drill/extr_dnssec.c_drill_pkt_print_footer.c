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
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_pkt ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/ * ldns_get_rr_list_name_by_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_answerfrom (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_pkt_querytime (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_pkt_size (int /*<<< orphan*/ *) ; 
 char* ldns_rdf2str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rdf_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_resolver_port (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_rdf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int verbosity ; 

void
drill_pkt_print_footer(FILE *fd, ldns_resolver *r, ldns_pkt *p)
{
	ldns_rr_list *hostnames;
	char *answerfrom_str;

	if (verbosity < 5) {
		return;
	}

	hostnames = ldns_get_rr_list_name_by_addr(r, ldns_pkt_answerfrom(p), 0, 0);

	fprintf(fd, ";; Received %d bytes from %s#%d(",
			(int) ldns_pkt_size(p),
			ldns_rdf2str(ldns_pkt_answerfrom(p)),
			(int) ldns_resolver_port(r));
	/* if we can resolve this print it, other print the ip again */
	if (hostnames) {
		ldns_rdf_print(fd,
				ldns_rr_rdf(ldns_rr_list_rr(hostnames, 0), 0));
		ldns_rr_list_deep_free(hostnames);
	} else {
		answerfrom_str = ldns_rdf2str(ldns_pkt_answerfrom(p));
		if (answerfrom_str) {
			fprintf(fd, "%s", answerfrom_str);
			LDNS_FREE(answerfrom_str);
		}
	}
	fprintf(fd, ") in %u ms\n\n", (unsigned int)ldns_pkt_querytime(p));
}