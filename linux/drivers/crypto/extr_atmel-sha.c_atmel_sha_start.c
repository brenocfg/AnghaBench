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
struct atmel_sha_reqctx {scalar_t__ op; int flags; } ;
struct atmel_sha_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  resume; struct ahash_request* req; } ;
struct ahash_request {int /*<<< orphan*/  nbytes; } ;

/* Variables and functions */
 int SHA_FLAGS_FINUP ; 
 scalar_t__ SHA_OP_FINAL ; 
 scalar_t__ SHA_OP_UPDATE ; 
 struct atmel_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int atmel_sha_complete (struct atmel_sha_dev*,int) ; 
 int /*<<< orphan*/  atmel_sha_done ; 
 int atmel_sha_final_req (struct atmel_sha_dev*) ; 
 int /*<<< orphan*/  atmel_sha_finish_req (struct ahash_request*,int) ; 
 int atmel_sha_hw_init (struct atmel_sha_dev*) ; 
 int atmel_sha_update_req (struct atmel_sha_dev*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int atmel_sha_start(struct atmel_sha_dev *dd)
{
	struct ahash_request *req = dd->req;
	struct atmel_sha_reqctx *ctx = ahash_request_ctx(req);
	int err;

	dev_dbg(dd->dev, "handling new req, op: %lu, nbytes: %d\n",
						ctx->op, req->nbytes);

	err = atmel_sha_hw_init(dd);
	if (err)
		return atmel_sha_complete(dd, err);

	/*
	 * atmel_sha_update_req() and atmel_sha_final_req() can return either:
	 *  -EINPROGRESS: the hardware is busy and the SHA driver will resume
	 *                its job later in the done_task.
	 *                This is the main path.
	 *
	 * 0: the SHA driver can continue its job then release the hardware
	 *    later, if needed, with atmel_sha_finish_req().
	 *    This is the alternate path.
	 *
	 * < 0: an error has occurred so atmel_sha_complete(dd, err) has already
	 *      been called, hence the hardware has been released.
	 *      The SHA driver must stop its job without calling
	 *      atmel_sha_finish_req(), otherwise atmel_sha_complete() would be
	 *      called a second time.
	 *
	 * Please note that currently, atmel_sha_final_req() never returns 0.
	 */

	dd->resume = atmel_sha_done;
	if (ctx->op == SHA_OP_UPDATE) {
		err = atmel_sha_update_req(dd);
		if (!err && (ctx->flags & SHA_FLAGS_FINUP))
			/* no final() after finup() */
			err = atmel_sha_final_req(dd);
	} else if (ctx->op == SHA_OP_FINAL) {
		err = atmel_sha_final_req(dd);
	}

	if (!err)
		/* done_task will not finish it, so do it here */
		atmel_sha_finish_req(req, err);

	dev_dbg(dd->dev, "exit, err: %d\n", err);

	return err;
}