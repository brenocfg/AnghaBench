#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct crypto_ahash {int dummy; } ;
struct crypto_aes_ctx {int dummy; } ;
struct TYPE_3__ {unsigned int key_len; int* key; int* k1; int* k2; int kn_len; int /*<<< orphan*/  key_sg; int /*<<< orphan*/  k2_sg; int /*<<< orphan*/  k1_sg; int /*<<< orphan*/  mode; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_1__ aes; } ;
struct ccp_ctx {TYPE_2__ u; } ;
struct ccp_crypto_ahash_alg {int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  aes ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
#define  AES_KEYSIZE_128 130 
#define  AES_KEYSIZE_192 129 
#define  AES_KEYSIZE_256 128 
 int /*<<< orphan*/  CCP_AES_TYPE_128 ; 
 int /*<<< orphan*/  CCP_AES_TYPE_192 ; 
 int /*<<< orphan*/  CCP_AES_TYPE_256 ; 
 int /*<<< orphan*/  CRYPTO_TFM_RES_BAD_KEY_LEN ; 
 int EINVAL ; 
 int /*<<< orphan*/  aes_encrypt (struct crypto_aes_ctx*,int*,int*) ; 
 int aes_expandkey (struct crypto_aes_ctx*,int /*<<< orphan*/  const*,unsigned int) ; 
 int be64_to_cpu (int /*<<< orphan*/ ) ; 
 struct ccp_crypto_ahash_alg* ccp_crypto_ahash_alg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int /*<<< orphan*/  crypto_ahash_set_flags (struct crypto_ahash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_tfm (struct crypto_ahash*) ; 
 struct ccp_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memzero_explicit (struct crypto_aes_ctx*,int) ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ *,int*,unsigned int) ; 

__attribute__((used)) static int ccp_aes_cmac_setkey(struct crypto_ahash *tfm, const u8 *key,
			       unsigned int key_len)
{
	struct ccp_ctx *ctx = crypto_tfm_ctx(crypto_ahash_tfm(tfm));
	struct ccp_crypto_ahash_alg *alg =
		ccp_crypto_ahash_alg(crypto_ahash_tfm(tfm));
	u64 k0_hi, k0_lo, k1_hi, k1_lo, k2_hi, k2_lo;
	u64 rb_hi = 0x00, rb_lo = 0x87;
	struct crypto_aes_ctx aes;
	__be64 *gk;
	int ret;

	switch (key_len) {
	case AES_KEYSIZE_128:
		ctx->u.aes.type = CCP_AES_TYPE_128;
		break;
	case AES_KEYSIZE_192:
		ctx->u.aes.type = CCP_AES_TYPE_192;
		break;
	case AES_KEYSIZE_256:
		ctx->u.aes.type = CCP_AES_TYPE_256;
		break;
	default:
		crypto_ahash_set_flags(tfm, CRYPTO_TFM_RES_BAD_KEY_LEN);
		return -EINVAL;
	}
	ctx->u.aes.mode = alg->mode;

	/* Set to zero until complete */
	ctx->u.aes.key_len = 0;

	/* Set the key for the AES cipher used to generate the keys */
	ret = aes_expandkey(&aes, key, key_len);
	if (ret)
		return ret;

	/* Encrypt a block of zeroes - use key area in context */
	memset(ctx->u.aes.key, 0, sizeof(ctx->u.aes.key));
	aes_encrypt(&aes, ctx->u.aes.key, ctx->u.aes.key);
	memzero_explicit(&aes, sizeof(aes));

	/* Generate K1 and K2 */
	k0_hi = be64_to_cpu(*((__be64 *)ctx->u.aes.key));
	k0_lo = be64_to_cpu(*((__be64 *)ctx->u.aes.key + 1));

	k1_hi = (k0_hi << 1) | (k0_lo >> 63);
	k1_lo = k0_lo << 1;
	if (ctx->u.aes.key[0] & 0x80) {
		k1_hi ^= rb_hi;
		k1_lo ^= rb_lo;
	}
	gk = (__be64 *)ctx->u.aes.k1;
	*gk = cpu_to_be64(k1_hi);
	gk++;
	*gk = cpu_to_be64(k1_lo);

	k2_hi = (k1_hi << 1) | (k1_lo >> 63);
	k2_lo = k1_lo << 1;
	if (ctx->u.aes.k1[0] & 0x80) {
		k2_hi ^= rb_hi;
		k2_lo ^= rb_lo;
	}
	gk = (__be64 *)ctx->u.aes.k2;
	*gk = cpu_to_be64(k2_hi);
	gk++;
	*gk = cpu_to_be64(k2_lo);

	ctx->u.aes.kn_len = sizeof(ctx->u.aes.k1);
	sg_init_one(&ctx->u.aes.k1_sg, ctx->u.aes.k1, sizeof(ctx->u.aes.k1));
	sg_init_one(&ctx->u.aes.k2_sg, ctx->u.aes.k2, sizeof(ctx->u.aes.k2));

	/* Save the supplied key */
	memset(ctx->u.aes.key, 0, sizeof(ctx->u.aes.key));
	memcpy(ctx->u.aes.key, key, key_len);
	ctx->u.aes.key_len = key_len;
	sg_init_one(&ctx->u.aes.key_sg, ctx->u.aes.key, key_len);

	return ret;
}