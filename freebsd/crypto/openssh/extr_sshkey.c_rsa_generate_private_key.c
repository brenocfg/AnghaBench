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
typedef  int u_int ;
typedef  int /*<<< orphan*/  RSA ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSA_F4 ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_generate_key_ex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RSA_new () ; 
 int SSHBUF_MAX_BIGNUM ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int SSH_ERR_KEY_LENGTH ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 
 int SSH_RSA_MINIMUM_MODULUS_SIZE ; 

__attribute__((used)) static int
rsa_generate_private_key(u_int bits, RSA **rsap)
{
	RSA *private = NULL;
	BIGNUM *f4 = NULL;
	int ret = SSH_ERR_INTERNAL_ERROR;

	if (rsap == NULL)
		return SSH_ERR_INVALID_ARGUMENT;
	if (bits < SSH_RSA_MINIMUM_MODULUS_SIZE ||
	    bits > SSHBUF_MAX_BIGNUM * 8)
		return SSH_ERR_KEY_LENGTH;
	*rsap = NULL;
	if ((private = RSA_new()) == NULL || (f4 = BN_new()) == NULL) {
		ret = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	if (!BN_set_word(f4, RSA_F4) ||
	    !RSA_generate_key_ex(private, bits, f4, NULL)) {
		ret = SSH_ERR_LIBCRYPTO_ERROR;
		goto out;
	}
	*rsap = private;
	private = NULL;
	ret = 0;
 out:
	RSA_free(private);
	BN_free(f4);
	return ret;
}