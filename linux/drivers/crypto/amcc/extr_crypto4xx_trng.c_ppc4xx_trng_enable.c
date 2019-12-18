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
typedef  int /*<<< orphan*/  u32 ;
struct crypto4xx_device {scalar_t__ ce_base; } ;

/* Variables and functions */
 scalar_t__ CRYPTO4XX_DEVICE_CTRL ; 
 int /*<<< orphan*/  PPC4XX_TRNG_EN ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ppc4xx_trng_enable(struct crypto4xx_device *dev, bool enable)
{
	u32 device_ctrl;

	device_ctrl = readl(dev->ce_base + CRYPTO4XX_DEVICE_CTRL);
	if (enable)
		device_ctrl |= PPC4XX_TRNG_EN;
	else
		device_ctrl &= ~PPC4XX_TRNG_EN;
	writel(device_ctrl, dev->ce_base + CRYPTO4XX_DEVICE_CTRL);
}