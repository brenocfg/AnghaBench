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
struct sahara_sha_reqctx {int last; int active; int first; } ;
struct sahara_dev {int /*<<< orphan*/  kthread; int /*<<< orphan*/  queue_mutex; int /*<<< orphan*/  queue; } ;
struct ahash_request {int /*<<< orphan*/  base; int /*<<< orphan*/  nbytes; } ;

/* Variables and functions */
 struct sahara_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int crypto_enqueue_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sahara_dev* dev_ptr ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sahara_sha_enqueue(struct ahash_request *req, int last)
{
	struct sahara_sha_reqctx *rctx = ahash_request_ctx(req);
	struct sahara_dev *dev = dev_ptr;
	int ret;

	if (!req->nbytes && !last)
		return 0;

	rctx->last = last;

	if (!rctx->active) {
		rctx->active = 1;
		rctx->first = 1;
	}

	mutex_lock(&dev->queue_mutex);
	ret = crypto_enqueue_request(&dev->queue, &req->base);
	mutex_unlock(&dev->queue_mutex);

	wake_up_process(dev->kthread);

	return ret;
}