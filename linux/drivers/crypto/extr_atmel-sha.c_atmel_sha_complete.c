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
struct atmel_sha_dev {int flags; int /*<<< orphan*/  queue_task; scalar_t__ force_complete; scalar_t__ is_async; int /*<<< orphan*/  iclk; struct ahash_request* req; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* complete ) (TYPE_1__*,int) ;} ;
struct ahash_request {TYPE_1__ base; } ;

/* Variables and functions */
 int SHA_FLAGS_BUSY ; 
 int SHA_FLAGS_CPU ; 
 int SHA_FLAGS_DMA_READY ; 
 int SHA_FLAGS_DUMP_REG ; 
 int SHA_FLAGS_FINAL ; 
 int SHA_FLAGS_OUTPUT_READY ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int atmel_sha_complete(struct atmel_sha_dev *dd, int err)
{
	struct ahash_request *req = dd->req;

	dd->flags &= ~(SHA_FLAGS_BUSY | SHA_FLAGS_FINAL | SHA_FLAGS_CPU |
		       SHA_FLAGS_DMA_READY | SHA_FLAGS_OUTPUT_READY |
		       SHA_FLAGS_DUMP_REG);

	clk_disable(dd->iclk);

	if ((dd->is_async || dd->force_complete) && req->base.complete)
		req->base.complete(&req->base, err);

	/* handle new request */
	tasklet_schedule(&dd->queue_task);

	return err;
}