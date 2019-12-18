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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  flags; struct skcipher_request* data; int /*<<< orphan*/  complete; } ;
struct skcipher_request {unsigned int cryptlen; int /*<<< orphan*/  iv; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; TYPE_1__ base; } ;
struct crypto_skcipher {int dummy; } ;
struct crypto_cts_reqctx {unsigned int offset; struct skcipher_request subreq; } ;
struct crypto_cts_ctx {int /*<<< orphan*/  child; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  crypto_cts_decrypt_done ; 
 int /*<<< orphan*/ * crypto_cts_reqctx_space (struct skcipher_request*) ; 
 int crypto_skcipher_blocksize (struct crypto_skcipher*) ; 
 struct crypto_cts_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int crypto_skcipher_decrypt (struct skcipher_request*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int cts_cbc_decrypt (struct skcipher_request*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 unsigned int rounddown (unsigned int,int) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 
 struct crypto_cts_reqctx* skcipher_request_ctx (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (struct skcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (struct skcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_tfm (struct skcipher_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int crypto_cts_decrypt(struct skcipher_request *req)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	struct crypto_cts_reqctx *rctx = skcipher_request_ctx(req);
	struct crypto_cts_ctx *ctx = crypto_skcipher_ctx(tfm);
	struct skcipher_request *subreq = &rctx->subreq;
	int bsize = crypto_skcipher_blocksize(tfm);
	unsigned int nbytes = req->cryptlen;
	unsigned int offset;
	u8 *space;

	skcipher_request_set_tfm(subreq, ctx->child);

	if (nbytes < bsize)
		return -EINVAL;

	if (nbytes == bsize) {
		skcipher_request_set_callback(subreq, req->base.flags,
					      req->base.complete,
					      req->base.data);
		skcipher_request_set_crypt(subreq, req->src, req->dst, nbytes,
					   req->iv);
		return crypto_skcipher_decrypt(subreq);
	}

	skcipher_request_set_callback(subreq, req->base.flags,
				      crypto_cts_decrypt_done, req);

	space = crypto_cts_reqctx_space(req);

	offset = rounddown(nbytes - 1, bsize);
	rctx->offset = offset;

	if (offset <= bsize)
		memcpy(space, req->iv, bsize);
	else
		scatterwalk_map_and_copy(space, req->src, offset - 2 * bsize,
					 bsize, 0);

	skcipher_request_set_crypt(subreq, req->src, req->dst,
				   offset, req->iv);

	return crypto_skcipher_decrypt(subreq) ?:
	       cts_cbc_decrypt(req);
}