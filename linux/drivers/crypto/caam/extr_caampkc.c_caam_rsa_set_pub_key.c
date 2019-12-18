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
struct rsa_key {int n_sz; int /*<<< orphan*/  e_sz; int /*<<< orphan*/  n; int /*<<< orphan*/  e; int /*<<< orphan*/ * member_0; } ;
struct crypto_akcipher {int dummy; } ;
struct caam_rsa_key {int n_sz; int /*<<< orphan*/  e_sz; int /*<<< orphan*/  n; int /*<<< orphan*/  e; } ;
struct caam_rsa_ctx {struct caam_rsa_key key; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 struct caam_rsa_ctx* akcipher_tfm_ctx (struct crypto_akcipher*) ; 
 int /*<<< orphan*/  caam_read_raw_data (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ caam_rsa_check_key_length (int) ; 
 int /*<<< orphan*/  caam_rsa_free_key (struct caam_rsa_key*) ; 
 int /*<<< orphan*/  kmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rsa_parse_pub_key (struct rsa_key*,void const*,unsigned int) ; 

__attribute__((used)) static int caam_rsa_set_pub_key(struct crypto_akcipher *tfm, const void *key,
				unsigned int keylen)
{
	struct caam_rsa_ctx *ctx = akcipher_tfm_ctx(tfm);
	struct rsa_key raw_key = {NULL};
	struct caam_rsa_key *rsa_key = &ctx->key;
	int ret;

	/* Free the old RSA key if any */
	caam_rsa_free_key(rsa_key);

	ret = rsa_parse_pub_key(&raw_key, key, keylen);
	if (ret)
		return ret;

	/* Copy key in DMA zone */
	rsa_key->e = kmemdup(raw_key.e, raw_key.e_sz, GFP_DMA | GFP_KERNEL);
	if (!rsa_key->e)
		goto err;

	/*
	 * Skip leading zeros and copy the positive integer to a buffer
	 * allocated in the GFP_DMA | GFP_KERNEL zone. The decryption descriptor
	 * expects a positive integer for the RSA modulus and uses its length as
	 * decryption output length.
	 */
	rsa_key->n = caam_read_raw_data(raw_key.n, &raw_key.n_sz);
	if (!rsa_key->n)
		goto err;

	if (caam_rsa_check_key_length(raw_key.n_sz << 3)) {
		caam_rsa_free_key(rsa_key);
		return -EINVAL;
	}

	rsa_key->e_sz = raw_key.e_sz;
	rsa_key->n_sz = raw_key.n_sz;

	return 0;
err:
	caam_rsa_free_key(rsa_key);
	return -ENOMEM;
}