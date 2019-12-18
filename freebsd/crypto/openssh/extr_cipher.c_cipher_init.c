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
typedef  int /*<<< orphan*/  u_char ;
struct sshcipher_ctx {int plaintext; int encrypt; int /*<<< orphan*/ * evp; int /*<<< orphan*/  ac_ctx; struct sshcipher const* cipher; int /*<<< orphan*/  cp_ctx; } ;
struct sshcipher {int flags; int key_len; int /*<<< orphan*/ * (* evptype ) () ;} ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int CFLAG_AESCTR ; 
 int CFLAG_CHACHAPOLY ; 
 int CFLAG_NONE ; 
 int CIPHER_ENCRYPT ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int EVP_CIPHER_CTX_key_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 scalar_t__ EVP_CIPHER_CTX_set_key_length (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EVP_CTRL_GCM_SET_IV_FIXED ; 
 scalar_t__ EVP_CipherInit (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 
 int /*<<< orphan*/  aesctr_ivsetup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  aesctr_keysetup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int) ; 
 struct sshcipher_ctx* calloc (int,int) ; 
 int chachapoly_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ cipher_authlen (struct sshcipher const*) ; 
 int cipher_ivlen (struct sshcipher const*) ; 
 int /*<<< orphan*/  explicit_bzero (struct sshcipher_ctx*,int) ; 
 int /*<<< orphan*/  free (struct sshcipher_ctx*) ; 
 int /*<<< orphan*/ * stub1 () ; 

int
cipher_init(struct sshcipher_ctx **ccp, const struct sshcipher *cipher,
    const u_char *key, u_int keylen, const u_char *iv, u_int ivlen,
    int do_encrypt)
{
	struct sshcipher_ctx *cc = NULL;
	int ret = SSH_ERR_INTERNAL_ERROR;
#ifdef WITH_OPENSSL
	const EVP_CIPHER *type;
	int klen;
#endif

	*ccp = NULL;
	if ((cc = calloc(sizeof(*cc), 1)) == NULL)
		return SSH_ERR_ALLOC_FAIL;

	cc->plaintext = (cipher->flags & CFLAG_NONE) != 0;
	cc->encrypt = do_encrypt;

	if (keylen < cipher->key_len ||
	    (iv != NULL && ivlen < cipher_ivlen(cipher))) {
		ret = SSH_ERR_INVALID_ARGUMENT;
		goto out;
	}

	cc->cipher = cipher;
	if ((cc->cipher->flags & CFLAG_CHACHAPOLY) != 0) {
		ret = chachapoly_init(&cc->cp_ctx, key, keylen);
		goto out;
	}
	if ((cc->cipher->flags & CFLAG_NONE) != 0) {
		ret = 0;
		goto out;
	}
#ifndef WITH_OPENSSL
	if ((cc->cipher->flags & CFLAG_AESCTR) != 0) {
		aesctr_keysetup(&cc->ac_ctx, key, 8 * keylen, 8 * ivlen);
		aesctr_ivsetup(&cc->ac_ctx, iv);
		ret = 0;
		goto out;
	}
	ret = SSH_ERR_INVALID_ARGUMENT;
	goto out;
#else /* WITH_OPENSSL */
	type = (*cipher->evptype)();
	if ((cc->evp = EVP_CIPHER_CTX_new()) == NULL) {
		ret = SSH_ERR_ALLOC_FAIL;
		goto out;
	}
	if (EVP_CipherInit(cc->evp, type, NULL, (u_char *)iv,
	    (do_encrypt == CIPHER_ENCRYPT)) == 0) {
		ret = SSH_ERR_LIBCRYPTO_ERROR;
		goto out;
	}
	if (cipher_authlen(cipher) &&
	    !EVP_CIPHER_CTX_ctrl(cc->evp, EVP_CTRL_GCM_SET_IV_FIXED,
	    -1, (u_char *)iv)) {
		ret = SSH_ERR_LIBCRYPTO_ERROR;
		goto out;
	}
	klen = EVP_CIPHER_CTX_key_length(cc->evp);
	if (klen > 0 && keylen != (u_int)klen) {
		if (EVP_CIPHER_CTX_set_key_length(cc->evp, keylen) == 0) {
			ret = SSH_ERR_LIBCRYPTO_ERROR;
			goto out;
		}
	}
	if (EVP_CipherInit(cc->evp, NULL, (u_char *)key, NULL, -1) == 0) {
		ret = SSH_ERR_LIBCRYPTO_ERROR;
		goto out;
	}
	ret = 0;
#endif /* WITH_OPENSSL */
 out:
	if (ret == 0) {
		/* success */
		*ccp = cc;
	} else {
		if (cc != NULL) {
#ifdef WITH_OPENSSL
			EVP_CIPHER_CTX_free(cc->evp);
#endif /* WITH_OPENSSL */
			explicit_bzero(cc, sizeof(*cc));
			free(cc);
		}
	}
	return ret;
}