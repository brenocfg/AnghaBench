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
typedef  int /*<<< orphan*/  br_x509_pkey ;
typedef  int /*<<< orphan*/  br_x509_certificate ;
typedef  int /*<<< orphan*/  br_name_element ;

/* Variables and functions */
 scalar_t__ VEC_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ check_forbidden_digests (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  forbidden_anchors ; 
 int /*<<< orphan*/  free_certificates (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * read_certificates (char const*,size_t*) ; 
 int /*<<< orphan*/  trust_anchors ; 
 int /*<<< orphan*/  ve_error_set (char*) ; 
 int /*<<< orphan*/  ve_trust_init () ; 
 int /*<<< orphan*/ * verify_signer_xcs (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfreepkey (int /*<<< orphan*/ *) ; 

__attribute__((used)) static br_x509_pkey *
verify_signer(const char *certs,
    br_name_element *elts, size_t num_elts)
{
	br_x509_certificate *xcs;
	br_x509_pkey *pk;
	size_t num;

	pk = NULL;

	ve_trust_init();
	xcs = read_certificates(certs, &num);
	if (xcs == NULL) {
		ve_error_set("cannot read certificates\n");
		return (NULL);
	}

	/*
	 * Check if either
	 * 1. There is a direct match between cert from forbidden_anchors
	 * and a cert from chain.
	 * 2. CA that signed the chain is found in forbidden_anchors.
	 */
	if (VEC_LEN(forbidden_anchors) > 0)
		pk = verify_signer_xcs(xcs, num, elts, num_elts, &forbidden_anchors);
	if (pk != NULL) {
		ve_error_set("Certificate is on forbidden list\n");
		xfreepkey(pk);
		pk = NULL;
		goto out;
	}

	pk = verify_signer_xcs(xcs, num, elts, num_elts, &trust_anchors);
	if (pk == NULL)
		goto out;

	/*
	 * Check if hash of tbs part of any certificate in chain
	 * is on the forbidden list.
	 */
	if (check_forbidden_digests(xcs, num)) {
		ve_error_set("Certificate hash is on forbidden list\n");
		xfreepkey(pk);
		pk = NULL;
	}
out:
	free_certificates(xcs, num);
	return (pk);
}