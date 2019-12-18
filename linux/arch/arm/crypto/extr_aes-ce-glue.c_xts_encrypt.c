#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  addr; } ;
struct TYPE_10__ {TYPE_3__ virt; } ;
struct TYPE_7__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {TYPE_1__ virt; } ;
struct skcipher_walk {int nbytes; int total; int /*<<< orphan*/  iv; TYPE_4__ src; TYPE_2__ dst; } ;
struct skcipher_request {int cryptlen; int /*<<< orphan*/  iv; struct scatterlist* dst; struct scatterlist* src; } ;
struct scatterlist {int dummy; } ;
struct crypto_skcipher {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  key_enc; } ;
struct TYPE_12__ {int /*<<< orphan*/  key_enc; } ;
struct crypto_aes_xts_ctx {TYPE_5__ key2; TYPE_6__ key1; } ;

/* Variables and functions */
 int AES_BLOCK_SIZE ; 
 int DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ce_aes_xts_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct crypto_aes_xts_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int /*<<< orphan*/  kernel_neon_begin () ; 
 int /*<<< orphan*/  kernel_neon_end () ; 
 scalar_t__ likely (int) ; 
 int num_rounds (TYPE_6__*) ; 
 struct scatterlist* scatterwalk_ffwd (struct scatterlist*,struct scatterlist*,int) ; 
 int /*<<< orphan*/  skcipher_request_flags (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (struct skcipher_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (struct skcipher_request*,struct scatterlist*,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_set_tfm (struct skcipher_request*,struct crypto_skcipher*) ; 
 int /*<<< orphan*/  skcipher_walk_abort (struct skcipher_walk*) ; 
 int skcipher_walk_done (struct skcipher_walk*,int) ; 
 int skcipher_walk_virt (struct skcipher_walk*,struct skcipher_request*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int xts_encrypt(struct skcipher_request *req)
{
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	struct crypto_aes_xts_ctx *ctx = crypto_skcipher_ctx(tfm);
	int err, first, rounds = num_rounds(&ctx->key1);
	int tail = req->cryptlen % AES_BLOCK_SIZE;
	struct scatterlist sg_src[2], sg_dst[2];
	struct skcipher_request subreq;
	struct scatterlist *src, *dst;
	struct skcipher_walk walk;

	if (req->cryptlen < AES_BLOCK_SIZE)
		return -EINVAL;

	err = skcipher_walk_virt(&walk, req, false);

	if (unlikely(tail > 0 && walk.nbytes < walk.total)) {
		int xts_blocks = DIV_ROUND_UP(req->cryptlen,
					      AES_BLOCK_SIZE) - 2;

		skcipher_walk_abort(&walk);

		skcipher_request_set_tfm(&subreq, tfm);
		skcipher_request_set_callback(&subreq,
					      skcipher_request_flags(req),
					      NULL, NULL);
		skcipher_request_set_crypt(&subreq, req->src, req->dst,
					   xts_blocks * AES_BLOCK_SIZE,
					   req->iv);
		req = &subreq;
		err = skcipher_walk_virt(&walk, req, false);
	} else {
		tail = 0;
	}

	for (first = 1; walk.nbytes >= AES_BLOCK_SIZE; first = 0) {
		int nbytes = walk.nbytes;

		if (walk.nbytes < walk.total)
			nbytes &= ~(AES_BLOCK_SIZE - 1);

		kernel_neon_begin();
		ce_aes_xts_encrypt(walk.dst.virt.addr, walk.src.virt.addr,
				   ctx->key1.key_enc, rounds, nbytes, walk.iv,
				   ctx->key2.key_enc, first);
		kernel_neon_end();
		err = skcipher_walk_done(&walk, walk.nbytes - nbytes);
	}

	if (err || likely(!tail))
		return err;

	dst = src = scatterwalk_ffwd(sg_src, req->src, req->cryptlen);
	if (req->dst != req->src)
		dst = scatterwalk_ffwd(sg_dst, req->dst, req->cryptlen);

	skcipher_request_set_crypt(req, src, dst, AES_BLOCK_SIZE + tail,
				   req->iv);

	err = skcipher_walk_virt(&walk, req, false);
	if (err)
		return err;

	kernel_neon_begin();
	ce_aes_xts_encrypt(walk.dst.virt.addr, walk.src.virt.addr,
			   ctx->key1.key_enc, rounds, walk.nbytes, walk.iv,
			   ctx->key2.key_enc, first);
	kernel_neon_end();

	return skcipher_walk_done(&walk, 0);
}