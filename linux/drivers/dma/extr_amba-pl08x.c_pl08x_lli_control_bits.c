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
typedef  int u8 ;
typedef  size_t u32 ;
struct pl08x_driver_data {TYPE_1__* vd; } ;
struct TYPE_2__ {scalar_t__ ftdmac020; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 size_t FTDMAC020_LLI_DST_WIDTH_MSK ; 
 size_t FTDMAC020_LLI_DST_WIDTH_SHIFT ; 
 size_t FTDMAC020_LLI_SRC_WIDTH_MSK ; 
 size_t FTDMAC020_LLI_SRC_WIDTH_SHIFT ; 
 size_t FTDMAC020_LLI_TRANSFER_SIZE_MASK ; 
 size_t FTDMAC020_LLI_TRANSFER_SIZE_SHIFT ; 
 size_t PL080_CONTROL_DWIDTH_MASK ; 
 size_t PL080_CONTROL_DWIDTH_SHIFT ; 
 size_t PL080_CONTROL_SWIDTH_MASK ; 
 size_t PL080_CONTROL_SWIDTH_SHIFT ; 
 size_t PL080_CONTROL_TRANSFER_SIZE_MASK ; 
 size_t PL080_CONTROL_TRANSFER_SIZE_SHIFT ; 
 size_t PL080_WIDTH_16BIT ; 
 size_t PL080_WIDTH_32BIT ; 
 size_t PL080_WIDTH_8BIT ; 

__attribute__((used)) static inline u32 pl08x_lli_control_bits(struct pl08x_driver_data *pl08x,
					 u32 cctl,
					 u8 srcwidth, u8 dstwidth,
					 size_t tsize)
{
	u32 retbits = cctl;

	/*
	 * Remove all src, dst and transfer size bits, then set the
	 * width and size according to the parameters. The bit offsets
	 * are different in the FTDMAC020 so we need to accound for this.
	 */
	if (pl08x->vd->ftdmac020) {
		retbits &= ~FTDMAC020_LLI_DST_WIDTH_MSK;
		retbits &= ~FTDMAC020_LLI_SRC_WIDTH_MSK;
		retbits &= ~FTDMAC020_LLI_TRANSFER_SIZE_MASK;

		switch (srcwidth) {
		case 1:
			retbits |= PL080_WIDTH_8BIT <<
				FTDMAC020_LLI_SRC_WIDTH_SHIFT;
			break;
		case 2:
			retbits |= PL080_WIDTH_16BIT <<
				FTDMAC020_LLI_SRC_WIDTH_SHIFT;
			break;
		case 4:
			retbits |= PL080_WIDTH_32BIT <<
				FTDMAC020_LLI_SRC_WIDTH_SHIFT;
			break;
		default:
			BUG();
			break;
		}

		switch (dstwidth) {
		case 1:
			retbits |= PL080_WIDTH_8BIT <<
				FTDMAC020_LLI_DST_WIDTH_SHIFT;
			break;
		case 2:
			retbits |= PL080_WIDTH_16BIT <<
				FTDMAC020_LLI_DST_WIDTH_SHIFT;
			break;
		case 4:
			retbits |= PL080_WIDTH_32BIT <<
				FTDMAC020_LLI_DST_WIDTH_SHIFT;
			break;
		default:
			BUG();
			break;
		}

		tsize &= FTDMAC020_LLI_TRANSFER_SIZE_MASK;
		retbits |= tsize << FTDMAC020_LLI_TRANSFER_SIZE_SHIFT;
	} else {
		retbits &= ~PL080_CONTROL_DWIDTH_MASK;
		retbits &= ~PL080_CONTROL_SWIDTH_MASK;
		retbits &= ~PL080_CONTROL_TRANSFER_SIZE_MASK;

		switch (srcwidth) {
		case 1:
			retbits |= PL080_WIDTH_8BIT <<
				PL080_CONTROL_SWIDTH_SHIFT;
			break;
		case 2:
			retbits |= PL080_WIDTH_16BIT <<
				PL080_CONTROL_SWIDTH_SHIFT;
			break;
		case 4:
			retbits |= PL080_WIDTH_32BIT <<
				PL080_CONTROL_SWIDTH_SHIFT;
			break;
		default:
			BUG();
			break;
		}

		switch (dstwidth) {
		case 1:
			retbits |= PL080_WIDTH_8BIT <<
				PL080_CONTROL_DWIDTH_SHIFT;
			break;
		case 2:
			retbits |= PL080_WIDTH_16BIT <<
				PL080_CONTROL_DWIDTH_SHIFT;
			break;
		case 4:
			retbits |= PL080_WIDTH_32BIT <<
				PL080_CONTROL_DWIDTH_SHIFT;
			break;
		default:
			BUG();
			break;
		}

		tsize &= PL080_CONTROL_TRANSFER_SIZE_MASK;
		retbits |= tsize << PL080_CONTROL_TRANSFER_SIZE_SHIFT;
	}

	return retbits;
}