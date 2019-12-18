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
struct hifn_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIFN_1_DMA_CNFG ; 
 int HIFN_DMACNFG_DMARESET ; 
 int HIFN_DMACNFG_MODE ; 
 int HIFN_DMACNFG_MSTRESET ; 
 int /*<<< orphan*/  hifn_reset_puc (struct hifn_device*) ; 
 int /*<<< orphan*/  hifn_stop_device (struct hifn_device*) ; 
 int /*<<< orphan*/  hifn_write_1 (struct hifn_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void hifn_reset_dma(struct hifn_device *dev, int full)
{
	hifn_stop_device(dev);

	/*
	 * Setting poll frequency and others to 0.
	 */
	hifn_write_1(dev, HIFN_1_DMA_CNFG, HIFN_DMACNFG_MSTRESET |
			HIFN_DMACNFG_DMARESET | HIFN_DMACNFG_MODE);
	mdelay(1);

	/*
	 * Reset DMA.
	 */
	if (full) {
		hifn_write_1(dev, HIFN_1_DMA_CNFG, HIFN_DMACNFG_MODE);
		mdelay(1);
	} else {
		hifn_write_1(dev, HIFN_1_DMA_CNFG, HIFN_DMACNFG_MODE |
				HIFN_DMACNFG_MSTRESET);
		hifn_reset_puc(dev);
	}

	hifn_write_1(dev, HIFN_1_DMA_CNFG, HIFN_DMACNFG_MSTRESET |
			HIFN_DMACNFG_DMARESET | HIFN_DMACNFG_MODE);

	hifn_reset_puc(dev);
}