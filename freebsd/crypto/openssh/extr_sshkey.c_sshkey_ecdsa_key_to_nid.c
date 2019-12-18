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
typedef  size_t u_int ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 scalar_t__ EC_GROUP_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/ *) ; 
 int EC_GROUP_get_curve_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EC_GROUP_new_by_curve_name (int) ; 
 int /*<<< orphan*/  EC_GROUP_set_asn1_flag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EC_KEY_get0_group (int /*<<< orphan*/ *) ; 
 int EC_KEY_set_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int NID_X9_62_prime256v1 ; 
 int NID_secp384r1 ; 
 int NID_secp521r1 ; 
 int /*<<< orphan*/  OPENSSL_EC_NAMED_CURVE ; 

int
sshkey_ecdsa_key_to_nid(EC_KEY *k)
{
	EC_GROUP *eg;
	int nids[] = {
		NID_X9_62_prime256v1,
		NID_secp384r1,
#  ifdef OPENSSL_HAS_NISTP521
		NID_secp521r1,
#  endif /* OPENSSL_HAS_NISTP521 */
		-1
	};
	int nid;
	u_int i;
	BN_CTX *bnctx;
	const EC_GROUP *g = EC_KEY_get0_group(k);

	/*
	 * The group may be stored in a ASN.1 encoded private key in one of two
	 * ways: as a "named group", which is reconstituted by ASN.1 object ID
	 * or explicit group parameters encoded into the key blob. Only the
	 * "named group" case sets the group NID for us, but we can figure
	 * it out for the other case by comparing against all the groups that
	 * are supported.
	 */
	if ((nid = EC_GROUP_get_curve_name(g)) > 0)
		return nid;
	if ((bnctx = BN_CTX_new()) == NULL)
		return -1;
	for (i = 0; nids[i] != -1; i++) {
		if ((eg = EC_GROUP_new_by_curve_name(nids[i])) == NULL) {
			BN_CTX_free(bnctx);
			return -1;
		}
		if (EC_GROUP_cmp(g, eg, bnctx) == 0)
			break;
		EC_GROUP_free(eg);
	}
	BN_CTX_free(bnctx);
	if (nids[i] != -1) {
		/* Use the group with the NID attached */
		EC_GROUP_set_asn1_flag(eg, OPENSSL_EC_NAMED_CURVE);
		if (EC_KEY_set_group(k, eg) != 1) {
			EC_GROUP_free(eg);
			return -1;
		}
	}
	return nids[i];
}