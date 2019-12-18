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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {int /*<<< orphan*/  ctr; } ;
struct sshcipher_ctx {int /*<<< orphan*/  evp; struct sshcipher* cipher; TYPE_1__ ac_ctx; } ;
struct sshcipher {int flags; scalar_t__ evptype; } ;

/* Variables and functions */
 int CFLAG_AESCTR ; 
 int CFLAG_CHACHAPOLY ; 
 int CFLAG_NONE ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_get_iv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int EVP_CIPHER_CTX_iv_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CTRL_GCM_IV_GEN ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 
 scalar_t__ cipher_authlen (struct sshcipher const*) ; 
 scalar_t__ evp_aes_128_ctr ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ssh_aes_ctr_iv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

int
cipher_get_keyiv(struct sshcipher_ctx *cc, u_char *iv, size_t len)
{
#ifdef WITH_OPENSSL
	const struct sshcipher *c = cc->cipher;
	int evplen;
#endif

	if ((cc->cipher->flags & CFLAG_CHACHAPOLY) != 0) {
		if (len != 0)
			return SSH_ERR_INVALID_ARGUMENT;
		return 0;
	}
	if ((cc->cipher->flags & CFLAG_AESCTR) != 0) {
		if (len != sizeof(cc->ac_ctx.ctr))
			return SSH_ERR_INVALID_ARGUMENT;
		memcpy(iv, cc->ac_ctx.ctr, len);
		return 0;
	}
	if ((cc->cipher->flags & CFLAG_NONE) != 0)
		return 0;

#ifdef WITH_OPENSSL
	evplen = EVP_CIPHER_CTX_iv_length(cc->evp);
	if (evplen == 0)
		return 0;
	else if (evplen < 0)
		return SSH_ERR_LIBCRYPTO_ERROR;
	if ((size_t)evplen != len)
		return SSH_ERR_INVALID_ARGUMENT;
#ifndef OPENSSL_HAVE_EVPCTR
	if (c->evptype == evp_aes_128_ctr)
		ssh_aes_ctr_iv(cc->evp, 0, iv, len);
	else
#endif
	if (cipher_authlen(c)) {
		if (!EVP_CIPHER_CTX_ctrl(cc->evp, EVP_CTRL_GCM_IV_GEN,
		   len, iv))
		       return SSH_ERR_LIBCRYPTO_ERROR;
	} else if (!EVP_CIPHER_CTX_get_iv(cc->evp, iv, len))
	       return SSH_ERR_LIBCRYPTO_ERROR;
#endif
	return 0;
}