#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sec_request {int dummy; } ;
struct sec_alg_tfm_ctx {TYPE_1__* queue; int /*<<< orphan*/  backlog; int /*<<< orphan*/  lock; } ;
struct crypto_skcipher {int dummy; } ;
struct TYPE_4__ {int havesoftqueue; int /*<<< orphan*/  queuelock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 struct sec_alg_tfm_ctx* crypto_skcipher_ctx (struct crypto_skcipher*) ; 
 int /*<<< orphan*/  crypto_skcipher_set_reqsize (struct crypto_skcipher*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* sec_queue_alloc_start_safe () ; 

__attribute__((used)) static int sec_alg_skcipher_init(struct crypto_skcipher *tfm)
{
	struct sec_alg_tfm_ctx *ctx = crypto_skcipher_ctx(tfm);

	mutex_init(&ctx->lock);
	INIT_LIST_HEAD(&ctx->backlog);
	crypto_skcipher_set_reqsize(tfm, sizeof(struct sec_request));

	ctx->queue = sec_queue_alloc_start_safe();
	if (IS_ERR(ctx->queue))
		return PTR_ERR(ctx->queue);

	mutex_init(&ctx->queue->queuelock);
	ctx->queue->havesoftqueue = false;

	return 0;
}