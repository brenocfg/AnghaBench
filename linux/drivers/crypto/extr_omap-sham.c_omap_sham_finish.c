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
struct omap_sham_reqctx {int flags; int /*<<< orphan*/  bufcnt; scalar_t__ digcnt; struct omap_sham_dev* dd; } ;
struct omap_sham_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; } ;
struct ahash_request {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLAGS_AUTO_XOR ; 
 int /*<<< orphan*/  FLAGS_HMAC ; 
 struct omap_sham_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_sham_copy_ready_hash (struct ahash_request*) ; 
 int omap_sham_finish_hmac (struct ahash_request*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap_sham_finish(struct ahash_request *req)
{
	struct omap_sham_reqctx *ctx = ahash_request_ctx(req);
	struct omap_sham_dev *dd = ctx->dd;
	int err = 0;

	if (ctx->digcnt) {
		omap_sham_copy_ready_hash(req);
		if ((ctx->flags & BIT(FLAGS_HMAC)) &&
				!test_bit(FLAGS_AUTO_XOR, &dd->flags))
			err = omap_sham_finish_hmac(req);
	}

	dev_dbg(dd->dev, "digcnt: %d, bufcnt: %d\n", ctx->digcnt, ctx->bufcnt);

	return err;
}