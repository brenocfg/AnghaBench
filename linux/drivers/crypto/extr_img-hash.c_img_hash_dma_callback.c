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
struct img_hash_request_ctx {scalar_t__ sg; scalar_t__ bufcnt; int /*<<< orphan*/  buffer; } ;
struct img_hash_dev {int /*<<< orphan*/  dma_task; int /*<<< orphan*/  req; } ;

/* Variables and functions */
 struct img_hash_request_ctx* ahash_request_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_hash_xmit_cpu (struct img_hash_dev*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void img_hash_dma_callback(void *data)
{
	struct img_hash_dev *hdev = (struct img_hash_dev *)data;
	struct img_hash_request_ctx *ctx = ahash_request_ctx(hdev->req);

	if (ctx->bufcnt) {
		img_hash_xmit_cpu(hdev, ctx->buffer, ctx->bufcnt, 0);
		ctx->bufcnt = 0;
	}
	if (ctx->sg)
		tasklet_schedule(&hdev->dma_task);
}