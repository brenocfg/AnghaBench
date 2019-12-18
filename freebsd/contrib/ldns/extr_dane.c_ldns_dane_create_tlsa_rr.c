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
typedef  scalar_t__ ldns_tlsa_selector ;
typedef  scalar_t__ ldns_tlsa_matching_type ;
typedef  scalar_t__ ldns_tlsa_certificate_usage ;
typedef  scalar_t__ ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RDF_TYPE_INT8 ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_TLSA ; 
 scalar_t__ LDNS_STATUS_MEM_ERR ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_dane_cert2rdf (int /*<<< orphan*/ **,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * ldns_native2rdf_int8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_new_frm_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_set_rdf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

ldns_status
ldns_dane_create_tlsa_rr(ldns_rr** tlsa,
		ldns_tlsa_certificate_usage certificate_usage,
		ldns_tlsa_selector          selector,
		ldns_tlsa_matching_type     matching_type,
		X509* cert)
{
	ldns_rdf* rdf;
	ldns_status s;

	assert(tlsa != NULL);
	assert(cert != NULL);

	/* create rr */
	*tlsa = ldns_rr_new_frm_type(LDNS_RR_TYPE_TLSA);
	if (*tlsa == NULL) {
		return LDNS_STATUS_MEM_ERR;
	}

	rdf = ldns_native2rdf_int8(LDNS_RDF_TYPE_INT8,
			(uint8_t)certificate_usage);
	if (rdf == NULL) {
		goto memerror;
	}
	(void) ldns_rr_set_rdf(*tlsa, rdf, 0);

	rdf = ldns_native2rdf_int8(LDNS_RDF_TYPE_INT8, (uint8_t)selector);
	if (rdf == NULL) {
		goto memerror;
	}
	(void) ldns_rr_set_rdf(*tlsa, rdf, 1);

	rdf = ldns_native2rdf_int8(LDNS_RDF_TYPE_INT8, (uint8_t)matching_type);
	if (rdf == NULL) {
		goto memerror;
	}
	(void) ldns_rr_set_rdf(*tlsa, rdf, 2);

	s = ldns_dane_cert2rdf(&rdf, cert, selector, matching_type);
	if (s == LDNS_STATUS_OK) {
		(void) ldns_rr_set_rdf(*tlsa, rdf, 3);
		return LDNS_STATUS_OK;
	}
	ldns_rr_free(*tlsa);
	*tlsa = NULL;
	return s;

memerror:
	ldns_rr_free(*tlsa);
	*tlsa = NULL;
	return LDNS_STATUS_MEM_ERR;
}