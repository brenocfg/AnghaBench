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
struct crypto4xx_device {int /*<<< orphan*/  trng_base; } ;
struct crypto4xx_core_device {scalar_t__ trng; int /*<<< orphan*/  device; struct crypto4xx_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_hwrng_unregister (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  ppc4xx_trng_enable (struct crypto4xx_device*,int) ; 

void ppc4xx_trng_remove(struct crypto4xx_core_device *core_dev)
{
	if (core_dev && core_dev->trng) {
		struct crypto4xx_device *dev = core_dev->dev;

		devm_hwrng_unregister(core_dev->device, core_dev->trng);
		ppc4xx_trng_enable(dev, false);
		iounmap(dev->trng_base);
		kfree(core_dev->trng);
	}
}