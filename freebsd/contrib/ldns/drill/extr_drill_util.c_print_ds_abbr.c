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
 scalar_t__ LDNS_RR_TYPE_DS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ldns_rdf_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_rdf (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ldns_rr_ttl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_class_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
print_ds_abbr(FILE *fp, ldns_rr *ds)
{
	if (!ds || (ldns_rr_get_type(ds) != LDNS_RR_TYPE_DS)) {
		return;
	}

	ldns_rdf_print(fp, ldns_rr_owner(ds));
	fprintf(fp, " %d", (int)ldns_rr_ttl(ds));
	print_class_type(fp, ds);
	ldns_rdf_print(fp, ldns_rr_rdf(ds, 0)); fprintf(fp, " ");
	ldns_rdf_print(fp, ldns_rr_rdf(ds, 1)); fprintf(fp, " ");
	ldns_rdf_print(fp, ldns_rr_rdf(ds, 2)); fprintf(fp, " ");
	ldns_rdf_print(fp, ldns_rr_rdf(ds, 3)); fprintf(fp, " ");
}