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
typedef  int /*<<< orphan*/  u_char ;
struct sshcipher_ctx {int /*<<< orphan*/  evp; struct sshcipher* cipher; } ;
struct sshcipher {int flags; scalar_t__ evptype; } ;

/* Variables and functions */
 int CFLAG_CHACHAPOLY ; 
 int CFLAG_NONE ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 
 int EVP_CIPHER_CTX_iv_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_set_iv (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  EVP_CTRL_GCM_SET_IV_FIXED ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 
 scalar_t__ cipher_authlen (struct sshcipher const*) ; 
 scalar_t__ evp_aes_128_ctr ; 
 int /*<<< orphan*/  ssh_aes_ctr_iv (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

int
cipher_set_keyiv(struct sshcipher_ctx *cc, const u_char *iv, size_t len)
{
#ifdef WITH_OPENSSL
	const struct sshcipher *c = cc->cipher;
	int evplen = 0;
#endif

	if ((cc->cipher->flags & CFLAG_CHACHAPOLY) != 0)
		return 0;
	if ((cc->cipher->flags & CFLAG_NONE) != 0)
		return 0;

#ifdef WITH_OPENSSL
	evplen = EVP_CIPHER_CTX_iv_length(cc->evp);
	if (evplen <= 0)
		return SSH_ERR_LIBCRYPTO_ERROR;
	if ((size_t)evplen != len)
		return SSH_ERR_INVALID_ARGUMENT;
#ifndef OPENSSL_HAVE_EVPCTR
	/* XXX iv arg is const, but ssh_aes_ctr_iv isn't */
	if (c->evptype == evp_aes_128_ctr)
		ssh_aes_ctr_iv(cc->evp, 1, (u_char *)iv, evplen);
	else
#endif
	if (cipher_authlen(c)) {
		/* XXX iv arg is const, but EVP_CIPHER_CTX_ctrl isn't */
		if (!EVP_CIPHER_CTX_ctrl(cc->evp,
		    EVP_CTRL_GCM_SET_IV_FIXED, -1, (void *)iv))
			return SSH_ERR_LIBCRYPTO_ERROR;
	} else if (!EVP_CIPHER_CTX_set_iv(cc->evp, iv, evplen))
		return SSH_ERR_LIBCRYPTO_ERROR;
#endif
	return 0;
}