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
struct pata_macio_priv {int /*<<< orphan*/  dev; TYPE_1__* timings; } ;
struct ata_port_info {unsigned int pio_mask; unsigned int mwdma_mask; unsigned int udma_mask; } ;
struct TYPE_2__ {int mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void pmac_macio_calc_timing_masks(struct pata_macio_priv *priv,
					 struct ata_port_info *pinfo)
{
	int i = 0;

	pinfo->pio_mask		= 0;
	pinfo->mwdma_mask	= 0;
	pinfo->udma_mask	= 0;

	while (priv->timings[i].mode > 0) {
		unsigned int mask = 1U << (priv->timings[i].mode & 0x0f);
		switch(priv->timings[i].mode & 0xf0) {
		case 0x00: /* PIO */
			pinfo->pio_mask |= (mask >> 8);
			break;
		case 0x20: /* MWDMA */
			pinfo->mwdma_mask |= mask;
			break;
		case 0x40: /* UDMA */
			pinfo->udma_mask |= mask;
			break;
		}
		i++;
	}
	dev_dbg(priv->dev, "Supported masks: PIO=%lx, MWDMA=%lx, UDMA=%lx\n",
		pinfo->pio_mask, pinfo->mwdma_mask, pinfo->udma_mask);
}