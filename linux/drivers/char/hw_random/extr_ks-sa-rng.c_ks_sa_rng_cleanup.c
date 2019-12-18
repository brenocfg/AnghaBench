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
struct ks_sa_rng {int /*<<< orphan*/  regmap_cfg; TYPE_1__* reg_rng; } ;
struct hwrng {scalar_t__ priv; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int /*<<< orphan*/  SA_CMD_STATUS_OFS ; 
 int /*<<< orphan*/  SA_CMD_STATUS_REG_TRNG_ENABLE ; 
 struct ks_sa_rng* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ks_sa_rng_cleanup(struct hwrng *rng)
{
	struct device *dev = (struct device *)rng->priv;
	struct ks_sa_rng *ks_sa_rng = dev_get_drvdata(dev);

	/* Disable RNG */
	writel(0, &ks_sa_rng->reg_rng->control);
	regmap_write_bits(ks_sa_rng->regmap_cfg, SA_CMD_STATUS_OFS,
			  SA_CMD_STATUS_REG_TRNG_ENABLE, 0);
}