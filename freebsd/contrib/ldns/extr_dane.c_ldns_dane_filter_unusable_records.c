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
typedef  int /*<<< orphan*/  ldns_rr ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_TLSA ; 
 int ldns_rdf2native_int8 (int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_new () ; 
 int /*<<< orphan*/  ldns_rr_list_push_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_rr (int /*<<< orphan*/  const*,size_t) ; 
 size_t ldns_rr_list_rr_count (int /*<<< orphan*/  const*) ; 
 int ldns_rr_rd_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_rdf (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ldns_rr_list*
ldns_dane_filter_unusable_records(const ldns_rr_list* tlsas)
{
	size_t i;
	ldns_rr_list* r = ldns_rr_list_new();
	ldns_rr* tlsa_rr;

	if (! r) {
		return NULL;
	}
	for (i = 0; i < ldns_rr_list_rr_count(tlsas); i++) {
		tlsa_rr = ldns_rr_list_rr(tlsas, i);
		if (ldns_rr_get_type(tlsa_rr) == LDNS_RR_TYPE_TLSA &&
		    ldns_rr_rd_count(tlsa_rr) == 4 &&
		    ldns_rdf2native_int8(ldns_rr_rdf(tlsa_rr, 0)) <= 3 &&
		    ldns_rdf2native_int8(ldns_rr_rdf(tlsa_rr, 1)) <= 1 &&
		    ldns_rdf2native_int8(ldns_rr_rdf(tlsa_rr, 2)) <= 2) {

			if (! ldns_rr_list_push_rr(r, tlsa_rr)) {
				ldns_rr_list_free(r);
				return NULL;
			}
		}
	}
	return r;
}