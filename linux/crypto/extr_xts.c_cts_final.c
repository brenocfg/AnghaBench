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
struct skcipher_request {int cryptlen; TYPE_1__ base; int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;
struct rctx {int /*<<< orphan*/  tail; int /*<<< orphan*/  t; int /*<<< orphan*/  sg; struct skcipher_request subreq; } ;
struct priv {int /*<<< orphan*/  child; } ;
typedef  int /*<<< orphan*/  le128 ;

/* Variables and functions */
 int XTS_BLOCK_SIZE ; 
 struct priv* crypto_skcipher_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int /*<<< orphan*/  cts_done ; 
 int /*<<< orphan*/  le128_xor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scatterwalk_ffwd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 struct rctx* skcipher_request_ctx (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (struct skcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (struct skcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_tfm (struct skcipher_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cts_final(struct skcipher_request *req,
		     int (*crypt)(struct skcipher_request *req))
{
	struct priv *ctx = crypto_skcipher_ctx(crypto_skcipher_reqtfm(req));
	int offset = req->cryptlen & ~(XTS_BLOCK_SIZE - 1);
	struct rctx *rctx = skcipher_request_ctx(req);
	struct skcipher_request *subreq = &rctx->subreq;
	int tail = req->cryptlen % XTS_BLOCK_SIZE;
	le128 b[2];
	int err;

	rctx->tail = scatterwalk_ffwd(rctx->sg, req->dst,
				      offset - XTS_BLOCK_SIZE);

	scatterwalk_map_and_copy(b, rctx->tail, 0, XTS_BLOCK_SIZE, 0);
	memcpy(b + 1, b, tail);
	scatterwalk_map_and_copy(b, req->src, offset, tail, 0);

	le128_xor(b, &rctx->t, b);

	scatterwalk_map_and_copy(b, rctx->tail, 0, XTS_BLOCK_SIZE + tail, 1);

	skcipher_request_set_tfm(subreq, ctx->child);
	skcipher_request_set_callback(subreq, req->base.flags, cts_done, req);
	skcipher_request_set_crypt(subreq, rctx->tail, rctx->tail,
				   XTS_BLOCK_SIZE, NULL);

	err = crypt(subreq);
	if (err)
		return err;

	scatterwalk_map_and_copy(b, rctx->tail, 0, XTS_BLOCK_SIZE, 0);
	le128_xor(b, &rctx->t, b);
	scatterwalk_map_and_copy(b, rctx->tail, 0, XTS_BLOCK_SIZE, 1);

	return 0;
}