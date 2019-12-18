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
typedef  int /*<<< orphan*/  u32 ;
struct omap_sham_reqctx {scalar_t__ digest; struct omap_sham_dev* dd; } ;
struct omap_sham_dev {TYPE_1__* pdata; } ;
struct ahash_request {int dummy; } ;
struct TYPE_2__ {int digest_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHA_REG_IDIGEST (struct omap_sham_dev*,int) ; 
 struct omap_sham_reqctx* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  omap_sham_read (struct omap_sham_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_sham_write (struct omap_sham_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_sham_copy_hash_omap2(struct ahash_request *req, int out)
{
	struct omap_sham_reqctx *ctx = ahash_request_ctx(req);
	struct omap_sham_dev *dd = ctx->dd;
	u32 *hash = (u32 *)ctx->digest;
	int i;

	for (i = 0; i < dd->pdata->digest_size / sizeof(u32); i++) {
		if (out)
			hash[i] = omap_sham_read(dd, SHA_REG_IDIGEST(dd, i));
		else
			omap_sham_write(dd, SHA_REG_IDIGEST(dd, i), hash[i]);
	}
}