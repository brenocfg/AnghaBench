#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct nx_gcm_rctx {int* iv; } ;
struct TYPE_4__ {int /*<<< orphan*/  nonce; } ;
struct TYPE_5__ {TYPE_1__ ccm; } ;
struct nx_crypto_ctx {TYPE_2__ priv; } ;
struct blkcipher_desc {int* info; } ;
struct TYPE_6__ {int /*<<< orphan*/  tfm; } ;
struct aead_request {scalar_t__ assoclen; int /*<<< orphan*/  iv; TYPE_3__ base; } ;

/* Variables and functions */
 struct nx_gcm_rctx* aead_request_ctx (struct aead_request*) ; 
 int ccm_nx_decrypt (struct aead_request*,struct blkcipher_desc*,scalar_t__) ; 
 struct nx_crypto_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ccm4309_aes_nx_decrypt(struct aead_request *req)
{
	struct nx_crypto_ctx *nx_ctx = crypto_tfm_ctx(req->base.tfm);
	struct nx_gcm_rctx *rctx = aead_request_ctx(req);
	struct blkcipher_desc desc;
	u8 *iv = rctx->iv;

	iv[0] = 3;
	memcpy(iv + 1, nx_ctx->priv.ccm.nonce, 3);
	memcpy(iv + 4, req->iv, 8);

	desc.info = iv;

	return ccm_nx_decrypt(req, &desc, req->assoclen - 8);
}