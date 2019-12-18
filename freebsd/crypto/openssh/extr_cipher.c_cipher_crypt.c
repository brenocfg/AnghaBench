#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct sshcipher_ctx {int /*<<< orphan*/  evp; scalar_t__ encrypt; TYPE_1__* cipher; int /*<<< orphan*/  ac_ctx; int /*<<< orphan*/  cp_ctx; } ;
struct TYPE_2__ {int flags; int block_size; } ;

/* Variables and functions */
 int CFLAG_AESCTR ; 
 int CFLAG_CHACHAPOLY ; 
 int CFLAG_NONE ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_CTRL_GCM_GET_TAG ; 
 int /*<<< orphan*/  EVP_CTRL_GCM_IV_GEN ; 
 int /*<<< orphan*/  EVP_CTRL_GCM_SET_TAG ; 
 scalar_t__ EVP_Cipher (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 
 int SSH_ERR_MAC_INVALID ; 
 int /*<<< orphan*/  aesctr_encrypt_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int chachapoly_crypt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int,int,scalar_t__) ; 
 int cipher_authlen (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

int
cipher_crypt(struct sshcipher_ctx *cc, u_int seqnr, u_char *dest,
   const u_char *src, u_int len, u_int aadlen, u_int authlen)
{
	if ((cc->cipher->flags & CFLAG_CHACHAPOLY) != 0) {
		return chachapoly_crypt(&cc->cp_ctx, seqnr, dest, src,
		    len, aadlen, authlen, cc->encrypt);
	}
	if ((cc->cipher->flags & CFLAG_NONE) != 0) {
		memcpy(dest, src, aadlen + len);
		return 0;
	}
#ifndef WITH_OPENSSL
	if ((cc->cipher->flags & CFLAG_AESCTR) != 0) {
		if (aadlen)
			memcpy(dest, src, aadlen);
		aesctr_encrypt_bytes(&cc->ac_ctx, src + aadlen,
		    dest + aadlen, len);
		return 0;
	}
	return SSH_ERR_INVALID_ARGUMENT;
#else
	if (authlen) {
		u_char lastiv[1];

		if (authlen != cipher_authlen(cc->cipher))
			return SSH_ERR_INVALID_ARGUMENT;
		/* increment IV */
		if (!EVP_CIPHER_CTX_ctrl(cc->evp, EVP_CTRL_GCM_IV_GEN,
		    1, lastiv))
			return SSH_ERR_LIBCRYPTO_ERROR;
		/* set tag on decyption */
		if (!cc->encrypt &&
		    !EVP_CIPHER_CTX_ctrl(cc->evp, EVP_CTRL_GCM_SET_TAG,
		    authlen, (u_char *)src + aadlen + len))
			return SSH_ERR_LIBCRYPTO_ERROR;
	}
	if (aadlen) {
		if (authlen &&
		    EVP_Cipher(cc->evp, NULL, (u_char *)src, aadlen) < 0)
			return SSH_ERR_LIBCRYPTO_ERROR;
		memcpy(dest, src, aadlen);
	}
	if (len % cc->cipher->block_size)
		return SSH_ERR_INVALID_ARGUMENT;
	if (EVP_Cipher(cc->evp, dest + aadlen, (u_char *)src + aadlen,
	    len) < 0)
		return SSH_ERR_LIBCRYPTO_ERROR;
	if (authlen) {
		/* compute tag (on encrypt) or verify tag (on decrypt) */
		if (EVP_Cipher(cc->evp, NULL, NULL, 0) < 0)
			return cc->encrypt ?
			    SSH_ERR_LIBCRYPTO_ERROR : SSH_ERR_MAC_INVALID;
		if (cc->encrypt &&
		    !EVP_CIPHER_CTX_ctrl(cc->evp, EVP_CTRL_GCM_GET_TAG,
		    authlen, dest + aadlen + len))
			return SSH_ERR_LIBCRYPTO_ERROR;
	}
	return 0;
#endif
}