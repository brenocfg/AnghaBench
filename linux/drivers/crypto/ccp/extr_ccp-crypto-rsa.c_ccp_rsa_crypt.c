#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct crypto_akcipher {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src_len; int /*<<< orphan*/  src; int /*<<< orphan*/  mod_len; int /*<<< orphan*/ * mod; int /*<<< orphan*/  exp_len; int /*<<< orphan*/ * exp; int /*<<< orphan*/  key_size; } ;
struct TYPE_10__ {TYPE_3__ rsa; } ;
struct TYPE_11__ {TYPE_4__ u; int /*<<< orphan*/  engine; int /*<<< orphan*/  entry; } ;
struct ccp_rsa_req_ctx {TYPE_5__ cmd; } ;
struct TYPE_7__ {int /*<<< orphan*/  n_len; int /*<<< orphan*/  n_sg; int /*<<< orphan*/  d_len; int /*<<< orphan*/  d_sg; int /*<<< orphan*/  e_len; int /*<<< orphan*/  e_sg; int /*<<< orphan*/  key_len; } ;
struct TYPE_8__ {TYPE_1__ rsa; } ;
struct ccp_ctx {TYPE_2__ u; } ;
struct akcipher_request {int /*<<< orphan*/  base; int /*<<< orphan*/  dst; int /*<<< orphan*/  src_len; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCP_ENGINE_RSA ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct ccp_rsa_req_ctx* akcipher_request_ctx (struct akcipher_request*) ; 
 struct ccp_ctx* akcipher_tfm_ctx (struct crypto_akcipher*) ; 
 int ccp_crypto_enqueue_request (int /*<<< orphan*/ *,TYPE_5__*) ; 
 struct crypto_akcipher* crypto_akcipher_reqtfm (struct akcipher_request*) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ccp_rsa_crypt(struct akcipher_request *req, bool encrypt)
{
	struct crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	struct ccp_ctx *ctx = akcipher_tfm_ctx(tfm);
	struct ccp_rsa_req_ctx *rctx = akcipher_request_ctx(req);
	int ret = 0;

	memset(&rctx->cmd, 0, sizeof(rctx->cmd));
	INIT_LIST_HEAD(&rctx->cmd.entry);
	rctx->cmd.engine = CCP_ENGINE_RSA;

	rctx->cmd.u.rsa.key_size = ctx->u.rsa.key_len; /* in bits */
	if (encrypt) {
		rctx->cmd.u.rsa.exp = &ctx->u.rsa.e_sg;
		rctx->cmd.u.rsa.exp_len = ctx->u.rsa.e_len;
	} else {
		rctx->cmd.u.rsa.exp = &ctx->u.rsa.d_sg;
		rctx->cmd.u.rsa.exp_len = ctx->u.rsa.d_len;
	}
	rctx->cmd.u.rsa.mod = &ctx->u.rsa.n_sg;
	rctx->cmd.u.rsa.mod_len = ctx->u.rsa.n_len;
	rctx->cmd.u.rsa.src = req->src;
	rctx->cmd.u.rsa.src_len = req->src_len;
	rctx->cmd.u.rsa.dst = req->dst;

	ret = ccp_crypto_enqueue_request(&req->base, &rctx->cmd);

	return ret;
}