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
struct xgene_rng_dev {int /*<<< orphan*/  datum_size; scalar_t__ csr_base; int /*<<< orphan*/  dev; int /*<<< orphan*/  revision; int /*<<< orphan*/  failure_timer; scalar_t__ failure_cnt; } ;
struct hwrng {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_PATCH_LEVEL_RD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR_HW_REV_RD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR_HW_REV_RD (int /*<<< orphan*/ ) ; 
 scalar_t__ RNG_EIP_REV ; 
 int /*<<< orphan*/  RNG_MAX_DATUM ; 
 scalar_t__ RNG_OPTIONS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_rng_expired_timer ; 
 int /*<<< orphan*/  xgene_rng_init_internal (struct xgene_rng_dev*) ; 

__attribute__((used)) static int xgene_rng_init(struct hwrng *rng)
{
	struct xgene_rng_dev *ctx = (struct xgene_rng_dev *) rng->priv;

	ctx->failure_cnt = 0;
	timer_setup(&ctx->failure_timer, xgene_rng_expired_timer, 0);

	ctx->revision = readl(ctx->csr_base + RNG_EIP_REV);

	dev_dbg(ctx->dev, "Rev %d.%d.%d\n",
		MAJOR_HW_REV_RD(ctx->revision),
		MINOR_HW_REV_RD(ctx->revision),
		HW_PATCH_LEVEL_RD(ctx->revision));

	dev_dbg(ctx->dev, "Options 0x%08X",
		readl(ctx->csr_base + RNG_OPTIONS));

	xgene_rng_init_internal(ctx);

	ctx->datum_size = RNG_MAX_DATUM;

	return 0;
}