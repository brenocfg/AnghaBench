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
struct pl08x_driver_data {int /*<<< orphan*/  mem_buses; TYPE_3__* vd; TYPE_2__* pd; TYPE_1__* adev; } ;
struct TYPE_6__ {scalar_t__ dualmaster; } ;
struct TYPE_5__ {int memcpy_burst_size; int memcpy_bus_width; scalar_t__ memcpy_prot_cache; scalar_t__ memcpy_prot_buff; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PL080_BSIZE_1 ; 
 int PL080_BSIZE_128 ; 
 int PL080_BSIZE_16 ; 
 int PL080_BSIZE_256 ; 
 int PL080_BSIZE_32 ; 
 int PL080_BSIZE_4 ; 
 int PL080_BSIZE_64 ; 
 int PL080_BSIZE_8 ; 
 int PL080_CONTROL_DB_SIZE_SHIFT ; 
 int PL080_CONTROL_DST_INCR ; 
 int PL080_CONTROL_DWIDTH_SHIFT ; 
 int PL080_CONTROL_PROT_BUFF ; 
 int PL080_CONTROL_PROT_CACHE ; 
 int PL080_CONTROL_PROT_SYS ; 
 int PL080_CONTROL_SB_SIZE_SHIFT ; 
 int PL080_CONTROL_SRC_INCR ; 
 int PL080_CONTROL_SWIDTH_SHIFT ; 
 int PL080_WIDTH_16BIT ; 
 int PL080_WIDTH_32BIT ; 
 int PL080_WIDTH_8BIT ; 
#define  PL08X_BURST_SZ_1 138 
#define  PL08X_BURST_SZ_128 137 
#define  PL08X_BURST_SZ_16 136 
#define  PL08X_BURST_SZ_256 135 
#define  PL08X_BURST_SZ_32 134 
#define  PL08X_BURST_SZ_4 133 
#define  PL08X_BURST_SZ_64 132 
#define  PL08X_BURST_SZ_8 131 
#define  PL08X_BUS_WIDTH_16_BITS 130 
#define  PL08X_BUS_WIDTH_32_BITS 129 
#define  PL08X_BUS_WIDTH_8_BITS 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int pl08x_select_bus (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 pl08x_memcpy_cctl(struct pl08x_driver_data *pl08x)
{
	u32 cctl = 0;

	/* Conjure cctl */
	switch (pl08x->pd->memcpy_burst_size) {
	default:
		dev_err(&pl08x->adev->dev,
			"illegal burst size for memcpy, set to 1\n");
		/* Fall through */
	case PL08X_BURST_SZ_1:
		cctl |= PL080_BSIZE_1 << PL080_CONTROL_SB_SIZE_SHIFT |
			PL080_BSIZE_1 << PL080_CONTROL_DB_SIZE_SHIFT;
		break;
	case PL08X_BURST_SZ_4:
		cctl |= PL080_BSIZE_4 << PL080_CONTROL_SB_SIZE_SHIFT |
			PL080_BSIZE_4 << PL080_CONTROL_DB_SIZE_SHIFT;
		break;
	case PL08X_BURST_SZ_8:
		cctl |= PL080_BSIZE_8 << PL080_CONTROL_SB_SIZE_SHIFT |
			PL080_BSIZE_8 << PL080_CONTROL_DB_SIZE_SHIFT;
		break;
	case PL08X_BURST_SZ_16:
		cctl |= PL080_BSIZE_16 << PL080_CONTROL_SB_SIZE_SHIFT |
			PL080_BSIZE_16 << PL080_CONTROL_DB_SIZE_SHIFT;
		break;
	case PL08X_BURST_SZ_32:
		cctl |= PL080_BSIZE_32 << PL080_CONTROL_SB_SIZE_SHIFT |
			PL080_BSIZE_32 << PL080_CONTROL_DB_SIZE_SHIFT;
		break;
	case PL08X_BURST_SZ_64:
		cctl |= PL080_BSIZE_64 << PL080_CONTROL_SB_SIZE_SHIFT |
			PL080_BSIZE_64 << PL080_CONTROL_DB_SIZE_SHIFT;
		break;
	case PL08X_BURST_SZ_128:
		cctl |= PL080_BSIZE_128 << PL080_CONTROL_SB_SIZE_SHIFT |
			PL080_BSIZE_128 << PL080_CONTROL_DB_SIZE_SHIFT;
		break;
	case PL08X_BURST_SZ_256:
		cctl |= PL080_BSIZE_256 << PL080_CONTROL_SB_SIZE_SHIFT |
			PL080_BSIZE_256 << PL080_CONTROL_DB_SIZE_SHIFT;
		break;
	}

	switch (pl08x->pd->memcpy_bus_width) {
	default:
		dev_err(&pl08x->adev->dev,
			"illegal bus width for memcpy, set to 8 bits\n");
		/* Fall through */
	case PL08X_BUS_WIDTH_8_BITS:
		cctl |= PL080_WIDTH_8BIT << PL080_CONTROL_SWIDTH_SHIFT |
			PL080_WIDTH_8BIT << PL080_CONTROL_DWIDTH_SHIFT;
		break;
	case PL08X_BUS_WIDTH_16_BITS:
		cctl |= PL080_WIDTH_16BIT << PL080_CONTROL_SWIDTH_SHIFT |
			PL080_WIDTH_16BIT << PL080_CONTROL_DWIDTH_SHIFT;
		break;
	case PL08X_BUS_WIDTH_32_BITS:
		cctl |= PL080_WIDTH_32BIT << PL080_CONTROL_SWIDTH_SHIFT |
			PL080_WIDTH_32BIT << PL080_CONTROL_DWIDTH_SHIFT;
		break;
	}

	/* Protection flags */
	if (pl08x->pd->memcpy_prot_buff)
		cctl |= PL080_CONTROL_PROT_BUFF;
	if (pl08x->pd->memcpy_prot_cache)
		cctl |= PL080_CONTROL_PROT_CACHE;

	/* We are the kernel, so we are in privileged mode */
	cctl |= PL080_CONTROL_PROT_SYS;

	/* Both to be incremented or the code will break */
	cctl |= PL080_CONTROL_SRC_INCR | PL080_CONTROL_DST_INCR;

	if (pl08x->vd->dualmaster)
		cctl |= pl08x_select_bus(false,
					 pl08x->mem_buses,
					 pl08x->mem_buses);

	return cctl;
}