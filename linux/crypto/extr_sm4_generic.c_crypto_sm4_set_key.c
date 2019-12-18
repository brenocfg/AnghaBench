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
typedef  int /*<<< orphan*/  u32 ;
struct crypto_tfm {int /*<<< orphan*/  crt_flags; } ;
struct crypto_sm4_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 int crypto_sm4_expand_key (struct crypto_sm4_ctx*,int /*<<< orphan*/  const*,unsigned int) ; 
 struct crypto_sm4_ctx* crypto_tfm_ctx (struct crypto_tfm*) ; 

int crypto_sm4_set_key(struct crypto_tfm *tfm, const u8 *in_key,
		       unsigned int key_len)
{
	struct crypto_sm4_ctx *ctx = crypto_tfm_ctx(tfm);
	u32 *flags = &tfm->crt_flags;
	int ret;

	ret = crypto_sm4_expand_key(ctx, in_key, key_len);
	if (!ret)
		return 0;

	*flags |= CRYPTO_TFM_RES_BAD_KEY_LEN;
	return -EINVAL;
}