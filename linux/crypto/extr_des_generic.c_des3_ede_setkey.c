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
struct des3_ede_ctx {int dummy; } ;
struct crypto_tfm {int dummy; } ;

/* Variables and functions */
 int CRYPTO_TFM_REQ_FORBID_WEAK_KEYS ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_WEAK_KEY ; 
 int EINVAL ; 
 int ENOKEY ; 
 struct des3_ede_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 
 int crypto_tfm_get_flags (struct crypto_tfm*) ; 
 int /*<<< orphan*/  crypto_tfm_set_flags (struct crypto_tfm*,int /*<<< orphan*/ ) ; 
 int des3_ede_expand_key (struct des3_ede_ctx*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memset (struct des3_ede_ctx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int des3_ede_setkey(struct crypto_tfm *tfm, const u8 *key,
			   unsigned int keylen)
{
	struct des3_ede_ctx *dctx = crypto_tfm_ctx(tfm);
	int err;

	err = des3_ede_expand_key(dctx, key, keylen);
	if (err == -ENOKEY) {
		if (crypto_tfm_get_flags(tfm) & CRYPTO_TFM_REQ_FORBID_WEAK_KEYS)
			err = -EINVAL;
		else
			err = 0;
	}

	if (err) {
		memset(dctx, 0, sizeof(*dctx));
		crypto_tfm_set_flags(tfm, CRYPTO_TFM_RES_WEAK_KEY);
	}
	return err;
}