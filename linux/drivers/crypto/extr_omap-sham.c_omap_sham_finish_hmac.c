#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct omap_sham_hmac_ctx {int /*<<< orphan*/  opad; int /*<<< orphan*/  shash; } ;
struct omap_sham_ctx {struct omap_sham_hmac_ctx* base; } ;
struct TYPE_7__ {int /*<<< orphan*/  tfm; } ;
struct ahash_request {int /*<<< orphan*/  result; TYPE_1__ base; } ;
struct TYPE_8__ {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHASH_DESC_ON_STACK (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int crypto_shash_blocksize (int /*<<< orphan*/ ) ; 
 int crypto_shash_digestsize (int /*<<< orphan*/ ) ; 
 int crypto_shash_finup (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_shash_init (TYPE_2__*) ; 
 scalar_t__ crypto_shash_update (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 struct omap_sham_ctx* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 TYPE_2__* shash ; 

__attribute__((used)) static int omap_sham_finish_hmac(struct ahash_request *req)
{
	struct omap_sham_ctx *tctx = crypto_tfm_ctx(req->base.tfm);
	struct omap_sham_hmac_ctx *bctx = tctx->base;
	int bs = crypto_shash_blocksize(bctx->shash);
	int ds = crypto_shash_digestsize(bctx->shash);
	SHASH_DESC_ON_STACK(shash, bctx->shash);

	shash->tfm = bctx->shash;

	return crypto_shash_init(shash) ?:
	       crypto_shash_update(shash, bctx->opad, bs) ?:
	       crypto_shash_finup(shash, req->result, ds, req->result);
}