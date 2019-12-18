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
typedef  int u32 ;
struct pl08x_driver_data {TYPE_1__* vd; } ;
struct TYPE_2__ {scalar_t__ ftdmac020; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int FTDMAC020_LLI_DST_WIDTH_MSK ; 
 int FTDMAC020_LLI_DST_WIDTH_SHIFT ; 
 int FTDMAC020_LLI_SRC_WIDTH_MSK ; 
 int FTDMAC020_LLI_SRC_WIDTH_SHIFT ; 
 int PL080_CONTROL_DWIDTH_MASK ; 
 int PL080_CONTROL_DWIDTH_SHIFT ; 
 int PL080_CONTROL_SWIDTH_MASK ; 
 int PL080_CONTROL_SWIDTH_SHIFT ; 
#define  PL080_WIDTH_16BIT 130 
#define  PL080_WIDTH_32BIT 129 
#define  PL080_WIDTH_8BIT 128 

__attribute__((used)) static inline unsigned int
pl08x_get_bytes_for_lli(struct pl08x_driver_data *pl08x,
			u32 cctl,
			bool source)
{
	u32 val;

	if (pl08x->vd->ftdmac020) {
		if (source)
			val = (cctl & FTDMAC020_LLI_SRC_WIDTH_MSK) >>
				FTDMAC020_LLI_SRC_WIDTH_SHIFT;
		else
			val = (cctl & FTDMAC020_LLI_DST_WIDTH_MSK) >>
				FTDMAC020_LLI_DST_WIDTH_SHIFT;
	} else {
		if (source)
			val = (cctl & PL080_CONTROL_SWIDTH_MASK) >>
				PL080_CONTROL_SWIDTH_SHIFT;
		else
			val = (cctl & PL080_CONTROL_DWIDTH_MASK) >>
				PL080_CONTROL_DWIDTH_SHIFT;
	}

	switch (val) {
	case PL080_WIDTH_8BIT:
		return 1;
	case PL080_WIDTH_16BIT:
		return 2;
	case PL080_WIDTH_32BIT:
		return 4;
	default:
		break;
	}
	BUG();
	return 0;
}