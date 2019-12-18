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
typedef  int u64 ;
struct mtk_cryp {int dummy; } ;
struct mtk_aes_reqctx {int mode; } ;
struct mtk_aes_gcm_ctx {scalar_t__ textlen; scalar_t__ authsize; } ;
struct mtk_aes_base_ctx {int dummy; } ;
struct aead_request {int /*<<< orphan*/  base; int /*<<< orphan*/  assoclen; scalar_t__ cryptlen; } ;

/* Variables and functions */
 int AES_FLAGS_ENCRYPT ; 
 int AES_FLAGS_GCM ; 
 int EINVAL ; 
 int ENODEV ; 
 struct mtk_aes_reqctx* aead_request_ctx (struct aead_request*) ; 
 struct mtk_aes_base_ctx* crypto_aead_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_aead_reqtfm (struct aead_request*) ; 
 struct mtk_cryp* mtk_aes_find_dev (struct mtk_aes_base_ctx*) ; 
 struct mtk_aes_gcm_ctx* mtk_aes_gcm_ctx_cast (struct mtk_aes_base_ctx*) ; 
 int mtk_aes_handle_queue (struct mtk_cryp*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtk_aes_gcm_crypt(struct aead_request *req, u64 mode)
{
	struct mtk_aes_base_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	struct mtk_aes_gcm_ctx *gctx = mtk_aes_gcm_ctx_cast(ctx);
	struct mtk_aes_reqctx *rctx = aead_request_ctx(req);
	struct mtk_cryp *cryp;
	bool enc = !!(mode & AES_FLAGS_ENCRYPT);

	cryp = mtk_aes_find_dev(ctx);
	if (!cryp)
		return -ENODEV;

	/* Compute text length. */
	gctx->textlen = req->cryptlen - (enc ? 0 : gctx->authsize);

	/* Empty messages are not supported yet */
	if (!gctx->textlen && !req->assoclen)
		return -EINVAL;

	rctx->mode = AES_FLAGS_GCM | mode;

	return mtk_aes_handle_queue(cryp, enc, &req->base);
}