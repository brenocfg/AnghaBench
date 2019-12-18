#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {TYPE_1__* device; } ;
struct TYPE_6__ {TYPE_2__ chan; } ;
struct omap_chan {int /*<<< orphan*/  dma_ch; TYPE_3__ vc; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCR ; 
 int CCR_RD_ACTIVE ; 
 int CCR_WR_ACTIVE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int omap_dma_chan_read (struct omap_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void omap_dma_drain_chan(struct omap_chan *c)
{
	int i;
	u32 val;

	/* Wait for sDMA FIFO to drain */
	for (i = 0; ; i++) {
		val = omap_dma_chan_read(c, CCR);
		if (!(val & (CCR_RD_ACTIVE | CCR_WR_ACTIVE)))
			break;

		if (i > 100)
			break;

		udelay(5);
	}

	if (val & (CCR_RD_ACTIVE | CCR_WR_ACTIVE))
		dev_err(c->vc.chan.device->dev,
			"DMA drain did not complete on lch %d\n",
			c->dma_ch);
}