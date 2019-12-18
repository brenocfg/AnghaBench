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
struct mv_cesa_engine {int /*<<< orphan*/  lock; struct crypto_async_request* req; } ;
struct mv_cesa_ctx {TYPE_1__* ops; } ;
struct crypto_async_request {int /*<<< orphan*/  tfm; int /*<<< orphan*/  (* complete ) (struct crypto_async_request*,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  (* step ) (struct crypto_async_request*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 struct mv_cesa_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 struct crypto_async_request* mv_cesa_dequeue_req_locked (struct mv_cesa_engine*,struct crypto_async_request**) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct crypto_async_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct crypto_async_request*) ; 

__attribute__((used)) static void mv_cesa_rearm_engine(struct mv_cesa_engine *engine)
{
	struct crypto_async_request *req = NULL, *backlog = NULL;
	struct mv_cesa_ctx *ctx;


	spin_lock_bh(&engine->lock);
	if (!engine->req) {
		req = mv_cesa_dequeue_req_locked(engine, &backlog);
		engine->req = req;
	}
	spin_unlock_bh(&engine->lock);

	if (!req)
		return;

	if (backlog)
		backlog->complete(backlog, -EINPROGRESS);

	ctx = crypto_tfm_ctx(req->tfm);
	ctx->ops->step(req);
}