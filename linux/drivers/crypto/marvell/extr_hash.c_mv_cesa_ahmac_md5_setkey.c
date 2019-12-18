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
struct mv_cesa_hmac_ctx {void** iv; } ;
struct md5_state {int /*<<< orphan*/ * hash; } ;
struct crypto_ahash {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_tfm (struct crypto_ahash*) ; 
 struct mv_cesa_hmac_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int mv_cesa_ahmac_setkey (char*,int /*<<< orphan*/  const*,unsigned int,struct md5_state*,struct md5_state*) ; 

__attribute__((used)) static int mv_cesa_ahmac_md5_setkey(struct crypto_ahash *tfm, const u8 *key,
				    unsigned int keylen)
{
	struct mv_cesa_hmac_ctx *ctx = crypto_tfm_ctx(crypto_ahash_tfm(tfm));
	struct md5_state istate, ostate;
	int ret, i;

	ret = mv_cesa_ahmac_setkey("mv-md5", key, keylen, &istate, &ostate);
	if (ret)
		return ret;

	for (i = 0; i < ARRAY_SIZE(istate.hash); i++)
		ctx->iv[i] = be32_to_cpu(istate.hash[i]);

	for (i = 0; i < ARRAY_SIZE(ostate.hash); i++)
		ctx->iv[i + 8] = be32_to_cpu(ostate.hash[i]);

	return 0;
}