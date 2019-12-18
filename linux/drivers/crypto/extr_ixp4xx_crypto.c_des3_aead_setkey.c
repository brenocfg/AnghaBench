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
typedef  int /*<<< orphan*/  u8 ;
struct ixp_ctx {int authkey_len; int enckey_len; int /*<<< orphan*/  enckey; int /*<<< orphan*/  authkey; } ;
struct crypto_authenc_keys {int authkeylen; int enckeylen; int /*<<< orphan*/  enckey; int /*<<< orphan*/  authkey; } ;
struct crypto_aead {int dummy; } ;
typedef  int /*<<< orphan*/  keys ;

/* Variables and functions */
 int EINVAL ; 
 int aead_setup (struct crypto_aead*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_authsize (struct crypto_aead*) ; 
 struct ixp_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int crypto_authenc_extractkeys (struct crypto_authenc_keys*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memzero_explicit (struct crypto_authenc_keys*,int) ; 
 scalar_t__ unlikely (int) ; 
 int verify_aead_des3_key (struct crypto_aead*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int des3_aead_setkey(struct crypto_aead *tfm, const u8 *key,
			    unsigned int keylen)
{
	struct ixp_ctx *ctx = crypto_aead_ctx(tfm);
	struct crypto_authenc_keys keys;
	int err;

	err = crypto_authenc_extractkeys(&keys, key, keylen);
	if (unlikely(err))
		goto badkey;

	err = -EINVAL;
	if (keys.authkeylen > sizeof(ctx->authkey))
		goto badkey;

	err = verify_aead_des3_key(tfm, keys.enckey, keys.enckeylen);
	if (err)
		goto badkey;

	memcpy(ctx->authkey, keys.authkey, keys.authkeylen);
	memcpy(ctx->enckey, keys.enckey, keys.enckeylen);
	ctx->authkey_len = keys.authkeylen;
	ctx->enckey_len = keys.enckeylen;

	memzero_explicit(&keys, sizeof(keys));
	return aead_setup(tfm, crypto_aead_authsize(tfm));
badkey:
	memzero_explicit(&keys, sizeof(keys));
	return err;
}