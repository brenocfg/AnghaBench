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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_DNSKEY ; 
 int /*<<< orphan*/  LDNS_SECTION_ANSWER ; 
 int /*<<< orphan*/  LDNS_SHA1 ; 
 int /*<<< orphan*/  LDNS_SHA256 ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 scalar_t__ ldns_calc_keytag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_key_rr2ds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_pkt_rr_list_by_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_list_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_rr (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_print_ds (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 

void
print_ds_of_keys(ldns_pkt *p)
{
	ldns_rr_list *keys;
	uint16_t i;
	ldns_rr *ds;

	/* TODO fix the section stuff, here or in ldns */
	keys = ldns_pkt_rr_list_by_type(p, LDNS_RR_TYPE_DNSKEY,
			LDNS_SECTION_ANSWER);

	/* this also returns the question section rr, which does not
	 * have any data.... and this inturn crashes everything */

	if (keys) {
		for (i = 0; i < ldns_rr_list_rr_count(keys); i++) {
			fprintf(stdout, ";\n; equivalent DS records for key %u:\n",
				(unsigned int)ldns_calc_keytag(ldns_rr_list_rr(keys, i)));

			ds = ldns_key_rr2ds(ldns_rr_list_rr(keys, i), LDNS_SHA1);
			local_print_ds(stdout, "; sha1: ", ds);
			ds = ldns_key_rr2ds(ldns_rr_list_rr(keys, i), LDNS_SHA256);
			local_print_ds(stdout, "; sha256: ", ds);
		}
		ldns_rr_list_deep_free(keys);
	}
}