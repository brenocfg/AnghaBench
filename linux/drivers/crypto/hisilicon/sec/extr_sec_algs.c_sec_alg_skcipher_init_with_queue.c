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
struct sec_alg_tfm_ctx {TYPE_1__* queue; } ;
struct crypto_skcipher {int dummy; } ;
struct TYPE_2__ {int havesoftqueue; int /*<<< orphan*/  softqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_KFIFO (int /*<<< orphan*/ ) ; 
 struct sec_alg_tfm_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int kfifo_alloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_alg_skcipher_exit (struct crypto_skcipher*) ; 
 int sec_alg_skcipher_init (struct crypto_skcipher*) ; 

__attribute__((used)) static int sec_alg_skcipher_init_with_queue(struct crypto_skcipher *tfm)
{
	struct sec_alg_tfm_ctx *ctx = crypto_skcipher_ctx(tfm);
	int ret;

	ret = sec_alg_skcipher_init(tfm);
	if (ret)
		return ret;

	INIT_KFIFO(ctx->queue->softqueue);
	ret = kfifo_alloc(&ctx->queue->softqueue, 512, GFP_KERNEL);
	if (ret) {
		sec_alg_skcipher_exit(tfm);
		return ret;
	}
	ctx->queue->havesoftqueue = true;

	return 0;
}