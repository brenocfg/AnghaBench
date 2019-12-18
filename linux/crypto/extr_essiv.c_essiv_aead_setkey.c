#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_7__ {struct crypto_aead* aead; } ;
struct essiv_tfm_ctx {int /*<<< orphan*/  essiv_cipher; int /*<<< orphan*/  hash; TYPE_1__ u; } ;
struct crypto_authenc_keys {int /*<<< orphan*/  authkeylen; int /*<<< orphan*/  authkey; int /*<<< orphan*/  enckeylen; int /*<<< orphan*/  enckey; } ;
struct crypto_aead {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_MASK ; 
 int CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int CRYPTO_TFM_RES_MASK ; 
 int EINVAL ; 
 int HASH_MAX_DIGESTSIZE ; 
 int /*<<< orphan*/  SHASH_DESC_ON_STACK (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_clear_flags (struct crypto_aead*,int) ; 
 struct essiv_tfm_ctx* crypto_aead_ctx (struct crypto_aead*) ; 
 int crypto_aead_get_flags (struct crypto_aead*) ; 
 int /*<<< orphan*/  crypto_aead_set_flags (struct crypto_aead*,int) ; 
 int crypto_aead_setkey (struct crypto_aead*,int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ crypto_authenc_extractkeys (struct crypto_authenc_keys*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  crypto_cipher_clear_flags (int /*<<< orphan*/ ,int) ; 
 int crypto_cipher_get_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_cipher_set_flags (int /*<<< orphan*/ ,int) ; 
 int crypto_cipher_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_shash_digestsize (int /*<<< orphan*/ ) ; 
 int crypto_shash_finup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ crypto_shash_init (TYPE_2__*) ; 
 scalar_t__ crypto_shash_update (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* desc ; 

__attribute__((used)) static int essiv_aead_setkey(struct crypto_aead *tfm, const u8 *key,
			     unsigned int keylen)
{
	struct essiv_tfm_ctx *tctx = crypto_aead_ctx(tfm);
	SHASH_DESC_ON_STACK(desc, tctx->hash);
	struct crypto_authenc_keys keys;
	u8 salt[HASH_MAX_DIGESTSIZE];
	int err;

	crypto_aead_clear_flags(tctx->u.aead, CRYPTO_TFM_REQ_MASK);
	crypto_aead_set_flags(tctx->u.aead, crypto_aead_get_flags(tfm) &
					    CRYPTO_TFM_REQ_MASK);
	err = crypto_aead_setkey(tctx->u.aead, key, keylen);
	crypto_aead_set_flags(tfm, crypto_aead_get_flags(tctx->u.aead) &
				   CRYPTO_TFM_RES_MASK);
	if (err)
		return err;

	if (crypto_authenc_extractkeys(&keys, key, keylen) != 0) {
		crypto_aead_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}

	desc->tfm = tctx->hash;
	err = crypto_shash_init(desc) ?:
	      crypto_shash_update(desc, keys.enckey, keys.enckeylen) ?:
	      crypto_shash_finup(desc, keys.authkey, keys.authkeylen, salt);
	if (err)
		return err;

	crypto_cipher_clear_flags(tctx->essiv_cipher, CRYPTO_TFM_REQ_MASK);
	crypto_cipher_set_flags(tctx->essiv_cipher, crypto_aead_get_flags(tfm) &
						    CRYPTO_TFM_REQ_MASK);
	err = crypto_cipher_setkey(tctx->essiv_cipher, salt,
				   crypto_shash_digestsize(tctx->hash));
	crypto_aead_set_flags(tfm, crypto_cipher_get_flags(tctx->essiv_cipher) &
				   CRYPTO_TFM_RES_MASK);

	return err;
}