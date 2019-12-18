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
struct ks_sa_rng {TYPE_1__* reg_rng; } ;
struct hwrng {scalar_t__ priv; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  intack; int /*<<< orphan*/  output_h; int /*<<< orphan*/  output_l; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRNG_INTACK_REG_READY ; 
 struct ks_sa_rng* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ks_sa_rng_data_read(struct hwrng *rng, u32 *data)
{
	struct device *dev = (struct device *)rng->priv;
	struct ks_sa_rng *ks_sa_rng = dev_get_drvdata(dev);

	/* Read random data */
	data[0] = readl(&ks_sa_rng->reg_rng->output_l);
	data[1] = readl(&ks_sa_rng->reg_rng->output_h);

	writel(TRNG_INTACK_REG_READY, &ks_sa_rng->reg_rng->intack);

	return sizeof(u32) * 2;
}