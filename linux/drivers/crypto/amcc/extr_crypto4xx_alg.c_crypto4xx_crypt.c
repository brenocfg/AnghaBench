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
struct skcipher_request {int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  base; int /*<<< orphan*/  iv; } ;
struct crypto_skcipher {int dummy; } ;
struct crypto4xx_ctx {int /*<<< orphan*/  sa_len; int /*<<< orphan*/  sa_out; int /*<<< orphan*/  sa_in; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int AES_IV_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto4xx_build_pd (int /*<<< orphan*/ *,struct crypto4xx_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto4xx_memcpy_to_le32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int const) ; 
 struct crypto4xx_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 

__attribute__((used)) static inline int crypto4xx_crypt(struct skcipher_request *req,
				  const unsigned int ivlen, bool decrypt,
				  bool check_blocksize)
{
	struct crypto_skcipher *cipher = crypto_skcipher_reqtfm(req);
	struct crypto4xx_ctx *ctx = crypto_skcipher_ctx(cipher);
	__le32 iv[AES_IV_SIZE];

	if (check_blocksize && !IS_ALIGNED(req->cryptlen, AES_BLOCK_SIZE))
		return -EINVAL;

	if (ivlen)
		crypto4xx_memcpy_to_le32(iv, req->iv, ivlen);

	return crypto4xx_build_pd(&req->base, ctx, req->src, req->dst,
		req->cryptlen, iv, ivlen, decrypt ? ctx->sa_in : ctx->sa_out,
		ctx->sa_len, 0, NULL);
}