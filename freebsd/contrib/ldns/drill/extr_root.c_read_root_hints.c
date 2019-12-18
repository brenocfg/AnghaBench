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
typedef  int /*<<< orphan*/  ldns_zone ;
typedef  scalar_t__ ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_A ; 
 scalar_t__ LDNS_RR_TYPE_AAAA ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 char* ldns_get_errorstr_by_id (scalar_t__) ; 
 int /*<<< orphan*/  ldns_rr_clone (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_new () ; 
 int /*<<< orphan*/  ldns_rr_list_push_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_rr_list_rr (int /*<<< orphan*/ ,size_t) ; 
 size_t ldns_rr_list_rr_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_zone_deep_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_zone_new_frm_fp_l (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ldns_zone_rrs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

ldns_rr_list *
read_root_hints(const char *filename)
{
	FILE *fp = NULL;
	int line_nr = 0;
	ldns_zone *z;
	ldns_status status;
	ldns_rr_list *addresses = NULL;
	ldns_rr *rr;
	size_t i;

	fp = fopen(filename, "r");
	if (!fp) {
		fprintf(stderr, "Unable to open %s for reading: %s\n", filename, strerror(errno));
		return NULL;
	}

	status = ldns_zone_new_frm_fp_l(&z, fp, NULL, 0, 0, &line_nr);
	fclose(fp);
	if (status != LDNS_STATUS_OK) {
		fprintf(stderr, "Error reading root hints file: %s\n", ldns_get_errorstr_by_id(status));
		return NULL;
	} else {
		addresses = ldns_rr_list_new();
		for (i = 0; i < ldns_rr_list_rr_count(ldns_zone_rrs(z)); i++) { 
			rr = ldns_rr_list_rr(ldns_zone_rrs(z), i);
			/*if ((address_family == 0 || address_family == 1) &&
			*/
			if ( ldns_rr_get_type(rr) == LDNS_RR_TYPE_A ) {
				ldns_rr_list_push_rr(addresses, ldns_rr_clone(rr));
			}
			/*if ((address_family == 0 || address_family == 2) &&*/
			if ( ldns_rr_get_type(rr) == LDNS_RR_TYPE_AAAA) {
				ldns_rr_list_push_rr(addresses, ldns_rr_clone(rr));
			}
		}
		ldns_zone_deep_free(z);
		return addresses;
	}
}