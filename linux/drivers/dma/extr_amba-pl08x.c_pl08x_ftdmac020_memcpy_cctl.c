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
struct pl08x_driver_data {int /*<<< orphan*/  mem_buses; TYPE_1__* vd; TYPE_3__* adev; TYPE_2__* pd; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int memcpy_bus_width; } ;
struct TYPE_4__ {scalar_t__ dualmaster; } ;

/* Variables and functions */
 int FTDMAC020_LLI_DST_WIDTH_SHIFT ; 
 int FTDMAC020_LLI_SRC_WIDTH_SHIFT ; 
 int FTDMAC020_LLI_TC_MSK ; 
 int PL080_WIDTH_16BIT ; 
 int PL080_WIDTH_32BIT ; 
 int PL080_WIDTH_8BIT ; 
#define  PL08X_BUS_WIDTH_16_BITS 130 
#define  PL08X_BUS_WIDTH_32_BITS 129 
#define  PL08X_BUS_WIDTH_8_BITS 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int pl08x_select_bus (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 pl08x_ftdmac020_memcpy_cctl(struct pl08x_driver_data *pl08x)
{
	u32 cctl = 0;

	/* Conjure cctl */
	switch (pl08x->pd->memcpy_bus_width) {
	default:
		dev_err(&pl08x->adev->dev,
			"illegal bus width for memcpy, set to 8 bits\n");
		/* Fall through */
	case PL08X_BUS_WIDTH_8_BITS:
		cctl |= PL080_WIDTH_8BIT << FTDMAC020_LLI_SRC_WIDTH_SHIFT |
			PL080_WIDTH_8BIT << FTDMAC020_LLI_DST_WIDTH_SHIFT;
		break;
	case PL08X_BUS_WIDTH_16_BITS:
		cctl |= PL080_WIDTH_16BIT << FTDMAC020_LLI_SRC_WIDTH_SHIFT |
			PL080_WIDTH_16BIT << FTDMAC020_LLI_DST_WIDTH_SHIFT;
		break;
	case PL08X_BUS_WIDTH_32_BITS:
		cctl |= PL080_WIDTH_32BIT << FTDMAC020_LLI_SRC_WIDTH_SHIFT |
			PL080_WIDTH_32BIT << FTDMAC020_LLI_DST_WIDTH_SHIFT;
		break;
	}

	/*
	 * By default mask the TC IRQ on all LLIs, it will be unmasked on
	 * the last LLI item by other code.
	 */
	cctl |= FTDMAC020_LLI_TC_MSK;

	/*
	 * Both to be incremented so leave bits FTDMAC020_LLI_SRCAD_CTL
	 * and FTDMAC020_LLI_DSTAD_CTL as zero
	 */
	if (pl08x->vd->dualmaster)
		cctl |= pl08x_select_bus(true,
					 pl08x->mem_buses,
					 pl08x->mem_buses);

	return cctl;
}