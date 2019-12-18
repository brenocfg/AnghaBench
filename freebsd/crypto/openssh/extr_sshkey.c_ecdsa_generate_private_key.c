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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int EC_KEY_generate_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_new_by_curve_name (int) ; 
 int /*<<< orphan*/  EC_KEY_set_asn1_flag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_EC_NAMED_CURVE ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int SSH_ERR_KEY_LENGTH ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 
 int sshkey_ecdsa_bits_to_nid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ecdsa_generate_private_key(u_int bits, int *nid, EC_KEY **ecdsap)
{
	EC_KEY *private;
	int ret = SSH_ERR_INTERNAL_ERROR;

	if (nid == NULL || ecdsap == NULL)
		return SSH_ERR_INVALID_ARGUMENT;
	if ((*nid = sshkey_ecdsa_bits_to_nid(bits)) == -1)
		return SSH_ERR_KEY_LENGTH;
	*ecdsap = NULL;
	if ((private = EC_KEY_new_by_curve_name(*nid)) == NULL) {
		ret = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	if (EC_KEY_generate_key(private) != 1) {
		ret = SSH_ERR_LIBCRYPTO_ERROR;
		goto out;
	}
	EC_KEY_set_asn1_flag(private, OPENSSL_EC_NAMED_CURVE);
	*ecdsap = private;
	private = NULL;
	ret = 0;
 out:
	EC_KEY_free(private);
	return ret;
}