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
 scalar_t__ LDNS_RR_TYPE_DNSKEY ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ ldns_calc_keytag (int /*<<< orphan*/ *) ; 
 int ldns_rdf2native_int16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rdf_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_dnskey_key_size (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_owner (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_rdf (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ldns_rr_ttl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_class_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
print_dnskey_abbr(FILE *fp, ldns_rr *key)
{
        if (!key || (ldns_rr_get_type(key) != LDNS_RR_TYPE_DNSKEY)) {
                return;
        }

        ldns_rdf_print(fp, ldns_rr_owner(key));
        fprintf(fp, " %d", (int)ldns_rr_ttl(key));
	print_class_type(fp, key);

        /* print a number of rdf's */
        /* flags */
        ldns_rdf_print(fp, ldns_rr_rdf(key, 0)); fprintf(fp, " ");
        /* proto */
        ldns_rdf_print(fp, ldns_rr_rdf(key, 1)); fprintf(fp, " ");
        /* algo */
        ldns_rdf_print(fp, ldns_rr_rdf(key, 2));

	if (ldns_rdf2native_int16(ldns_rr_rdf(key, 0)) == 256) {
		fprintf(fp, " ;{id = %u (zsk), size = %db}", (unsigned int)ldns_calc_keytag(key),
				(int)ldns_rr_dnskey_key_size(key));
		return;
	}
	if (ldns_rdf2native_int16(ldns_rr_rdf(key, 0)) == 257) {
		fprintf(fp, " ;{id = %u (ksk), size = %db}", (unsigned int)ldns_calc_keytag(key),
				(int)ldns_rr_dnskey_key_size(key));
		return;
	}
	fprintf(fp, " ;{id = %u, size = %db}", (unsigned int)ldns_calc_keytag(key),
			(int)ldns_rr_dnskey_key_size(key));
}