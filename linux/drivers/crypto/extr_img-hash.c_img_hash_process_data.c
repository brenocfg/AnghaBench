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
struct img_hash_request_ctx {scalar_t__ bufcnt; } ;
struct img_hash_dev {int /*<<< orphan*/  dev; struct ahash_request* req; } ;
struct ahash_request {scalar_t__ nbytes; } ;

/* Variables and functions */
 scalar_t__ IMG_HASH_DMA_THRESHOLD ; 
 struct img_hash_request_ctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int img_hash_write_via_cpu (struct img_hash_dev*) ; 
 int img_hash_write_via_dma (struct img_hash_dev*) ; 

__attribute__((used)) static int img_hash_process_data(struct img_hash_dev *hdev)
{
	struct ahash_request *req = hdev->req;
	struct img_hash_request_ctx *ctx = ahash_request_ctx(req);
	int err = 0;

	ctx->bufcnt = 0;

	if (req->nbytes >= IMG_HASH_DMA_THRESHOLD) {
		dev_dbg(hdev->dev, "process data request(%d bytes) using DMA\n",
			req->nbytes);
		err = img_hash_write_via_dma(hdev);
	} else {
		dev_dbg(hdev->dev, "process data request(%d bytes) using CPU\n",
			req->nbytes);
		err = img_hash_write_via_cpu(hdev);
	}
	return err;
}