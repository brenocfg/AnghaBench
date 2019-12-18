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
struct TYPE_7__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_8__ {TYPE_3__ virt; } ;
struct TYPE_5__ {int /*<<< orphan*/ * addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct skcipher_walk {int nbytes; unsigned int total; TYPE_4__ dst; TYPE_2__ src; } ;
struct skcipher_request {int cryptlen; } ;
struct rctx {int /*<<< orphan*/  t; struct skcipher_request subreq; } ;
struct crypto_skcipher {int dummy; } ;
typedef  int /*<<< orphan*/  le128 ;

/* Variables and functions */
 int XTS_BLOCK_SIZE ; 
 struct crypto_skcipher* crypto_skcipher_reqtfm (struct skcipher_request*) ; 
 int /*<<< orphan*/  gf128mul_x_ble (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le128_xor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct rctx* skcipher_request_ctx (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_tfm (struct skcipher_request*,struct crypto_skcipher*) ; 
 int skcipher_walk_done (struct skcipher_walk*,unsigned int) ; 
 int skcipher_walk_virt (struct skcipher_walk*,struct skcipher_request*,int) ; 
 scalar_t__ unlikely (int const) ; 

__attribute__((used)) static int xor_tweak(struct skcipher_request *req, bool second_pass, bool enc)
{
	struct rctx *rctx = skcipher_request_ctx(req);
	struct crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	const bool cts = (req->cryptlen % XTS_BLOCK_SIZE);
	const int bs = XTS_BLOCK_SIZE;
	struct skcipher_walk w;
	le128 t = rctx->t;
	int err;

	if (second_pass) {
		req = &rctx->subreq;
		/* set to our TFM to enforce correct alignment: */
		skcipher_request_set_tfm(req, tfm);
	}
	err = skcipher_walk_virt(&w, req, false);

	while (w.nbytes) {
		unsigned int avail = w.nbytes;
		le128 *wsrc;
		le128 *wdst;

		wsrc = w.src.virt.addr;
		wdst = w.dst.virt.addr;

		do {
			if (unlikely(cts) &&
			    w.total - w.nbytes + avail < 2 * XTS_BLOCK_SIZE) {
				if (!enc) {
					if (second_pass)
						rctx->t = t;
					gf128mul_x_ble(&t, &t);
				}
				le128_xor(wdst, &t, wsrc);
				if (enc && second_pass)
					gf128mul_x_ble(&rctx->t, &t);
				skcipher_walk_done(&w, avail - bs);
				return 0;
			}

			le128_xor(wdst++, &t, wsrc++);
			gf128mul_x_ble(&t, &t);
		} while ((avail -= bs) >= bs);

		err = skcipher_walk_done(&w, avail);
	}

	return err;
}