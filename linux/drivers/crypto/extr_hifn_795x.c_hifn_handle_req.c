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
struct hifn_device {scalar_t__ started; int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
struct hifn_context {struct hifn_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  tfm; } ;
struct ablkcipher_request {int /*<<< orphan*/  nbytes; TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 scalar_t__ HIFN_QUEUE_LENGTH ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int ablkcipher_enqueue_request (int /*<<< orphan*/ *,struct ablkcipher_request*) ; 
 struct hifn_context* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int hifn_setup_session (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int hifn_handle_req(struct ablkcipher_request *req)
{
	struct hifn_context *ctx = crypto_tfm_ctx(req->base.tfm);
	struct hifn_device *dev = ctx->dev;
	int err = -EAGAIN;

	if (dev->started + DIV_ROUND_UP(req->nbytes, PAGE_SIZE) <= HIFN_QUEUE_LENGTH)
		err = hifn_setup_session(req);

	if (err == -EAGAIN) {
		unsigned long flags;

		spin_lock_irqsave(&dev->lock, flags);
		err = ablkcipher_enqueue_request(&dev->queue, req);
		spin_unlock_irqrestore(&dev->lock, flags);
	}

	return err;
}