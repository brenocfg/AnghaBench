#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct crypto_shash {int dummy; } ;
struct crypto_ahash {int dummy; } ;
struct TYPE_6__ {unsigned int key_len; int* key; int* ipad; int* opad; unsigned int opad_count; int /*<<< orphan*/  opad_sg; struct crypto_shash* hmac_tfm; } ;
struct TYPE_7__ {TYPE_1__ sha; } ;
struct ccp_ctx {TYPE_2__ u; } ;
struct TYPE_8__ {struct crypto_shash* tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 int HMAC_IPAD_VALUE ; 
 int HMAC_OPAD_VALUE ; 
 int /*<<< orphan*/  SHASH_DESC_ON_STACK (TYPE_3__*,struct crypto_shash*) ; 
 int /*<<< orphan*/  crypto_ahash_set_flags (struct crypto_ahash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_tfm (struct crypto_ahash*) ; 
 unsigned int crypto_shash_blocksize (struct crypto_shash*) ; 
 int crypto_shash_digest (TYPE_3__*,int /*<<< orphan*/  const*,unsigned int,int*) ; 
 unsigned int crypto_shash_digestsize (struct crypto_shash*) ; 
 struct ccp_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* sdesc ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ *,int*,unsigned int) ; 

__attribute__((used)) static int ccp_sha_setkey(struct crypto_ahash *tfm, const u8 *key,
			  unsigned int key_len)
{
	struct ccp_ctx *ctx = crypto_tfm_ctx(crypto_ahash_tfm(tfm));
	struct crypto_shash *shash = ctx->u.sha.hmac_tfm;

	SHASH_DESC_ON_STACK(sdesc, shash);

	unsigned int block_size = crypto_shash_blocksize(shash);
	unsigned int digest_size = crypto_shash_digestsize(shash);
	int i, ret;

	/* Set to zero until complete */
	ctx->u.sha.key_len = 0;

	/* Clear key area to provide zero padding for keys smaller
	 * than the block size
	 */
	memset(ctx->u.sha.key, 0, sizeof(ctx->u.sha.key));

	if (key_len > block_size) {
		/* Must hash the input key */
		sdesc->tfm = shash;

		ret = crypto_shash_digest(sdesc, key, key_len,
					  ctx->u.sha.key);
		if (ret) {
			crypto_ahash_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
			return -EINVAL;
		}

		key_len = digest_size;
	} else {
		memcpy(ctx->u.sha.key, key, key_len);
	}

	for (i = 0; i < block_size; i++) {
		ctx->u.sha.ipad[i] = ctx->u.sha.key[i] ^ HMAC_IPAD_VALUE;
		ctx->u.sha.opad[i] = ctx->u.sha.key[i] ^ HMAC_OPAD_VALUE;
	}

	sg_init_one(&ctx->u.sha.opad_sg, ctx->u.sha.opad, block_size);
	ctx->u.sha.opad_count = block_size;

	ctx->u.sha.key_len = key_len;

	return 0;
}