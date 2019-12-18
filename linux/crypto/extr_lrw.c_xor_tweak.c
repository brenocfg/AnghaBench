#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct skcipher_walk {int nbytes; unsigned int total; TYPE_4__ dst; TYPE_2__ src; scalar_t__ iv; } ;
struct skcipher_request {int dummy; } ;
struct rctx {struct skcipher_request subreq; int /*<<< orphan*/  t; } ;
struct priv {int /*<<< orphan*/ * mulinc; } ;
struct crypto_skcipher {int dummy; } ;
typedef  int /*<<< orphan*/  be128 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int LRW_BLOCK_SIZE ; 
 int /*<<< orphan*/  be128_xor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct priv* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 size_t next_index (int /*<<< orphan*/ *) ; 
 struct rctx* skcipher_request_ctx (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_tfm (struct skcipher_request*,struct crypto_skcipher*) ; 
 int skcipher_walk_done (struct skcipher_walk*,unsigned int) ; 
 int skcipher_walk_virt (struct skcipher_walk*,struct skcipher_request*,int) ; 

__attribute__((used)) static int xor_tweak(struct skcipher_request *req, bool second_pass)
{
	const int bs = LRW_BLOCK_SIZE;
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	struct priv *ctx = crypto_skcipher_ctx(tfm);
	struct rctx *rctx = skcipher_request_ctx(req);
	be128 t = rctx->t;
	struct skcipher_walk w;
	__be32 *iv;
	u32 counter[4];
	int err;

	if (second_pass) {
		req = &rctx->subreq;
		/* set to our TFM to enforce correct alignment: */
		skcipher_request_set_tfm(req, tfm);
	}

	err = skcipher_walk_virt(&w, req, false);
	if (err)
		return err;

	iv = (__be32 *)w.iv;
	counter[0] = be32_to_cpu(iv[3]);
	counter[1] = be32_to_cpu(iv[2]);
	counter[2] = be32_to_cpu(iv[1]);
	counter[3] = be32_to_cpu(iv[0]);

	while (w.nbytes) {
		unsigned int avail = w.nbytes;
		be128 *wsrc;
		be128 *wdst;

		wsrc = w.src.virt.addr;
		wdst = w.dst.virt.addr;

		do {
			be128_xor(wdst++, &t, wsrc++);

			/* T <- I*Key2, using the optimization
			 * discussed in the specification */
			be128_xor(&t, &t, &ctx->mulinc[next_index(counter)]);
		} while ((avail -= bs) >= bs);

		if (second_pass && w.nbytes == w.total) {
			iv[0] = cpu_to_be32(counter[3]);
			iv[1] = cpu_to_be32(counter[2]);
			iv[2] = cpu_to_be32(counter[1]);
			iv[3] = cpu_to_be32(counter[0]);
		}

		err = skcipher_walk_done(&w, avail);
	}

	return err;
}