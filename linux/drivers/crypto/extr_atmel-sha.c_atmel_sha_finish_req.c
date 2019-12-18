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
struct atmel_sha_reqctx {int /*<<< orphan*/  flags; struct atmel_sha_dev* dd; } ;
struct atmel_sha_dev {int flags; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHA_FLAGS_ERROR ; 
 int SHA_FLAGS_FINAL ; 
 struct atmel_sha_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  atmel_sha_complete (struct atmel_sha_dev*,int) ; 
 int /*<<< orphan*/  atmel_sha_copy_hash (struct ahash_request*) ; 
 int atmel_sha_finish (struct ahash_request*) ; 

__attribute__((used)) static void atmel_sha_finish_req(struct ahash_request *req, int err)
{
	struct atmel_sha_reqctx *ctx = ahash_request_ctx(req);
	struct atmel_sha_dev *dd = ctx->dd;

	if (!err) {
		atmel_sha_copy_hash(req);
		if (SHA_FLAGS_FINAL & dd->flags)
			err = atmel_sha_finish(req);
	} else {
		ctx->flags |= SHA_FLAGS_ERROR;
	}

	/* atomic operation is not needed here */
	(void)atmel_sha_complete(dd, err);
}