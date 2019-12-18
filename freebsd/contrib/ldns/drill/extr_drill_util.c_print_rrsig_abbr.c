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
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_RRSIG ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ldns_rdf_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_rdf (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ldns_rr_ttl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_class_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
print_rrsig_abbr(FILE *fp, ldns_rr *sig) {
	if (!sig || (ldns_rr_get_type(sig) != LDNS_RR_TYPE_RRSIG)) {
		return;
	}

	ldns_rdf_print(fp, ldns_rr_owner(sig));
	fprintf(fp, " %d", (int)ldns_rr_ttl(sig));
	print_class_type(fp, sig);

	/* print a number of rdf's */
	/* typecovered */
	ldns_rdf_print(fp, ldns_rr_rdf(sig, 0)); fprintf(fp, " ");
	/* algo */
	ldns_rdf_print(fp, ldns_rr_rdf(sig, 1)); fprintf(fp, " ");
	/* labels */
	ldns_rdf_print(fp, ldns_rr_rdf(sig, 2)); fprintf(fp, " (\n\t\t\t");
	/* expir */
	ldns_rdf_print(fp, ldns_rr_rdf(sig, 4)); fprintf(fp, " ");
	/* incep */	
	ldns_rdf_print(fp, ldns_rr_rdf(sig, 5)); fprintf(fp, " ");
	/* key-id */	
	ldns_rdf_print(fp, ldns_rr_rdf(sig, 6)); fprintf(fp, " ");
	/* key owner */
	ldns_rdf_print(fp, ldns_rr_rdf(sig, 7)); fprintf(fp, ")");
}