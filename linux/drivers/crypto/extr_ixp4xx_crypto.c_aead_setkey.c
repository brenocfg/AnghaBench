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
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 int aead_setup (struct crypto_aead*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_authsize (struct crypto_aead*) ; 
 struct ixp_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_flags (struct crypto_aead*,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_authenc_extractkeys (struct crypto_authenc_keys*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memzero_explicit (struct crypto_authenc_keys*,int) ; 

__attribute__((used)) static int aead_setkey(struct crypto_aead *tfm, const u8 *key,
			unsigned int keylen)
{
	struct ixp_ctx *ctx = crypto_aead_ctx(tfm);
	struct crypto_authenc_keys keys;

	if (crypto_authenc_extractkeys(&keys, key, keylen) != 0)
		goto badkey;

	if (keys.authkeylen > sizeof(ctx->authkey))
		goto badkey;

	if (keys.enckeylen > sizeof(ctx->enckey))
		goto badkey;

	memcpy(ctx->authkey, keys.authkey, keys.authkeylen);
	memcpy(ctx->enckey, keys.enckey, keys.enckeylen);
	ctx->authkey_len = keys.authkeylen;
	ctx->enckey_len = keys.enckeylen;

	memzero_explicit(&keys, sizeof(keys));
	return aead_setup(tfm, crypto_aead_authsize(tfm));
badkey:
	crypto_aead_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
	memzero_explicit(&keys, sizeof(keys));
	return -EINVAL;
}