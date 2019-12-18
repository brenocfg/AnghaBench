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
struct crypto4xx_ctx {int /*<<< orphan*/  sa_len; int /*<<< orphan*/  sa_out; int /*<<< orphan*/  sa_in; } ;
struct crypto4xx_aead_reqctx {int /*<<< orphan*/  dst; } ;
struct TYPE_2__ {int /*<<< orphan*/  tfm; } ;
struct aead_request {unsigned int cryptlen; int /*<<< orphan*/  assoclen; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__ base; int /*<<< orphan*/  iv; } ;
typedef  int /*<<< orphan*/  iv ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  GCM_AES_IV_SIZE ; 
 struct crypto4xx_aead_reqctx* aead_request_ctx (struct aead_request*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int crypto4xx_aead_fallback (struct aead_request*,struct crypto4xx_ctx*,int) ; 
 scalar_t__ crypto4xx_aead_need_fallback (struct aead_request*,unsigned int,int,int) ; 
 int crypto4xx_build_pd (TYPE_1__*,struct crypto4xx_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto4xx_memcpy_to_le32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_aead_authsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_reqtfm (struct aead_request*) ; 
 struct crypto4xx_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int crypto4xx_crypt_aes_gcm(struct aead_request *req,
					  bool decrypt)
{
	struct crypto4xx_ctx *ctx = crypto_tfm_ctx(req->base.tfm);
	struct crypto4xx_aead_reqctx *rctx = aead_request_ctx(req);
	__le32 iv[4];
	unsigned int len = req->cryptlen;

	if (decrypt)
		len -= crypto_aead_authsize(crypto_aead_reqtfm(req));

	if (crypto4xx_aead_need_fallback(req, len, false, decrypt))
		return crypto4xx_aead_fallback(req, ctx, decrypt);

	crypto4xx_memcpy_to_le32(iv, req->iv, GCM_AES_IV_SIZE);
	iv[3] = cpu_to_le32(1);

	return crypto4xx_build_pd(&req->base, ctx, req->src, req->dst,
				  len, iv, sizeof(iv),
				  decrypt ? ctx->sa_in : ctx->sa_out,
				  ctx->sa_len, req->assoclen, rctx->dst);
}