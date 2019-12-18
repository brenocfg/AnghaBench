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
typedef  int /*<<< orphan*/  u8 ;
struct crypto_aes_ctx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  crt_flags; } ;
struct crypto_aead {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 int ce_aes_expandkey (struct crypto_aes_ctx*,int /*<<< orphan*/  const*,unsigned int) ; 
 struct crypto_aes_ctx* crypto_aead_ctx (struct crypto_aead*) ; 

__attribute__((used)) static int ccm_setkey(struct crypto_aead *tfm, const u8 *in_key,
		      unsigned int key_len)
{
	struct crypto_aes_ctx *ctx = crypto_aead_ctx(tfm);
	int ret;

	ret = ce_aes_expandkey(ctx, in_key, key_len);
	if (!ret)
		return 0;

	tfm->base.crt_flags |= CRYPTO_TFM_RES_BAD_KEY_LEN;
	return -EINVAL;
}