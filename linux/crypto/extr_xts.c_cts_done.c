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
struct skcipher_request {int dummy; } ;
struct rctx {int /*<<< orphan*/  tail; int /*<<< orphan*/  t; } ;
struct crypto_async_request {struct skcipher_request* data; } ;
typedef  int /*<<< orphan*/  le128 ;

/* Variables and functions */
 int /*<<< orphan*/  XTS_BLOCK_SIZE ; 
 int /*<<< orphan*/  le128_xor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skcipher_request_complete (struct skcipher_request*,int) ; 
 struct rctx* skcipher_request_ctx (struct skcipher_request*) ; 

__attribute__((used)) static void cts_done(struct crypto_async_request *areq, int err)
{
	struct skcipher_request *req = areq->data;
	le128 b;

	if (!err) {
		struct rctx *rctx = skcipher_request_ctx(req);

		scatterwalk_map_and_copy(&b, rctx->tail, 0, XTS_BLOCK_SIZE, 0);
		le128_xor(&b, &rctx->t, &b);
		scatterwalk_map_and_copy(&b, rctx->tail, 0, XTS_BLOCK_SIZE, 1);
	}

	skcipher_request_complete(req, err);
}