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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct skcipher_request {int /*<<< orphan*/  iv; int /*<<< orphan*/  cryptlen; int /*<<< orphan*/  dst; TYPE_1__ base; } ;
struct rctx {int /*<<< orphan*/  t; struct skcipher_request subreq; } ;
struct priv {int /*<<< orphan*/  table; int /*<<< orphan*/  child; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypt_done ; 
 struct priv* crypto_skcipher_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int /*<<< orphan*/  gf128mul_64k_bbe (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct rctx* skcipher_request_ctx (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (struct skcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (struct skcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_tfm (struct skcipher_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_crypt(struct skcipher_request *req)
{
	struct priv *ctx = crypto_skcipher_ctx(crypto_skcipher_reqtfm(req));
	struct rctx *rctx = skcipher_request_ctx(req);
	struct skcipher_request *subreq = &rctx->subreq;

	skcipher_request_set_tfm(subreq, ctx->child);
	skcipher_request_set_callback(subreq, req->base.flags, crypt_done, req);
	/* pass req->iv as IV (will be used by xor_tweak, ECB will ignore it) */
	skcipher_request_set_crypt(subreq, req->dst, req->dst,
				   req->cryptlen, req->iv);

	/* calculate first value of T */
	memcpy(&rctx->t, req->iv, sizeof(rctx->t));

	/* T <- I*Key2 */
	gf128mul_64k_bbe(&rctx->t, ctx->table);
}