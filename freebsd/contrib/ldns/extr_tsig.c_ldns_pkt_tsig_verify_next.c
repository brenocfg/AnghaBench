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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LDNS_RDF_TYPE_DNAME ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/  ldns_pkt_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_pkt_set_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_pkt_set_tsig (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_pkt_tsig (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf2native_int16 (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rdf_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rdf_new_frm_str (int /*<<< orphan*/ ,char const*) ; 
 int ldns_rr_rd_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_rdf (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ldns_tsig_mac_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *,size_t,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * ldns_tsig_prepare_pkt_wire (int /*<<< orphan*/  const*,size_t,size_t*) ; 

bool
ldns_pkt_tsig_verify_next(ldns_pkt *pkt, const uint8_t *wire, size_t wirelen, const char* key_name,
	const char *key_data, const ldns_rdf *orig_mac_rdf, int tsig_timers_only)
{
	ldns_rdf *fudge_rdf;
	ldns_rdf *algorithm_rdf;
	ldns_rdf *time_signed_rdf;
	ldns_rdf *orig_id_rdf;
	ldns_rdf *error_rdf;
	ldns_rdf *other_data_rdf;
	ldns_rdf *pkt_mac_rdf;
	ldns_rdf *my_mac_rdf;
	ldns_rdf *key_name_rdf = ldns_rdf_new_frm_str(LDNS_RDF_TYPE_DNAME, key_name);
	uint16_t pkt_id, orig_pkt_id;
	ldns_status status;

	uint8_t *prepared_wire = NULL;
	size_t prepared_wire_size = 0;

	ldns_rr *orig_tsig = ldns_pkt_tsig(pkt);

	if (!orig_tsig || ldns_rr_rd_count(orig_tsig) <= 6) {
		ldns_rdf_deep_free(key_name_rdf);
		return false;
	}
	algorithm_rdf = ldns_rr_rdf(orig_tsig, 0);
	time_signed_rdf = ldns_rr_rdf(orig_tsig, 1);
	fudge_rdf = ldns_rr_rdf(orig_tsig, 2);
	pkt_mac_rdf = ldns_rr_rdf(orig_tsig, 3);
	orig_id_rdf = ldns_rr_rdf(orig_tsig, 4);
	error_rdf = ldns_rr_rdf(orig_tsig, 5);
	other_data_rdf = ldns_rr_rdf(orig_tsig, 6);

	/* remove temporarily */
	ldns_pkt_set_tsig(pkt, NULL);
	/* temporarily change the id to the original id */
	pkt_id = ldns_pkt_id(pkt);
	orig_pkt_id = ldns_rdf2native_int16(orig_id_rdf);
	ldns_pkt_set_id(pkt, orig_pkt_id);

	prepared_wire = ldns_tsig_prepare_pkt_wire(wire, wirelen, &prepared_wire_size);

	status = ldns_tsig_mac_new(&my_mac_rdf, prepared_wire, prepared_wire_size,
			key_data, key_name_rdf, fudge_rdf, algorithm_rdf,
			time_signed_rdf, error_rdf, other_data_rdf, orig_mac_rdf, tsig_timers_only);

	LDNS_FREE(prepared_wire);

	if (status != LDNS_STATUS_OK) {
		ldns_rdf_deep_free(key_name_rdf);
		return false;
	}
	/* Put back the values */
	ldns_pkt_set_tsig(pkt, orig_tsig);
	ldns_pkt_set_id(pkt, pkt_id);

	ldns_rdf_deep_free(key_name_rdf);

	if (ldns_rdf_compare(pkt_mac_rdf, my_mac_rdf) == 0) {
		ldns_rdf_deep_free(my_mac_rdf);
		return true;
	} else {
		ldns_rdf_deep_free(my_mac_rdf);
		return false;
	}
}