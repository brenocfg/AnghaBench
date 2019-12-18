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
struct sahara_dev {int /*<<< orphan*/  queue_mutex; int /*<<< orphan*/  queue; } ;
struct crypto_async_request {int /*<<< orphan*/  (* complete ) (struct crypto_async_request*,int) ;int /*<<< orphan*/  tfm; } ;
struct ahash_request {int dummy; } ;
struct ablkcipher_request {int dummy; } ;

/* Variables and functions */
 scalar_t__ CRYPTO_ALG_TYPE_AHASH ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 struct ablkcipher_request* ablkcipher_request_cast (struct crypto_async_request*) ; 
 struct ahash_request* ahash_request_cast (struct crypto_async_request*) ; 
 struct crypto_async_request* crypto_dequeue_request (int /*<<< orphan*/ *) ; 
 struct crypto_async_request* crypto_get_backlog (int /*<<< orphan*/ *) ; 
 scalar_t__ crypto_tfm_alg_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sahara_aes_process (struct ablkcipher_request*) ; 
 int sahara_sha_process (struct ahash_request*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  stub1 (struct crypto_async_request*,int) ; 
 int /*<<< orphan*/  stub2 (struct crypto_async_request*,int) ; 

__attribute__((used)) static int sahara_queue_manage(void *data)
{
	struct sahara_dev *dev = (struct sahara_dev *)data;
	struct crypto_async_request *async_req;
	struct crypto_async_request *backlog;
	int ret = 0;

	do {
		__set_current_state(TASK_INTERRUPTIBLE);

		mutex_lock(&dev->queue_mutex);
		backlog = crypto_get_backlog(&dev->queue);
		async_req = crypto_dequeue_request(&dev->queue);
		mutex_unlock(&dev->queue_mutex);

		if (backlog)
			backlog->complete(backlog, -EINPROGRESS);

		if (async_req) {
			if (crypto_tfm_alg_type(async_req->tfm) ==
			    CRYPTO_ALG_TYPE_AHASH) {
				struct ahash_request *req =
					ahash_request_cast(async_req);

				ret = sahara_sha_process(req);
			} else {
				struct ablkcipher_request *req =
					ablkcipher_request_cast(async_req);

				ret = sahara_aes_process(req);
			}

			async_req->complete(async_req, ret);

			continue;
		}

		schedule();
	} while (!kthread_should_stop());

	return 0;
}