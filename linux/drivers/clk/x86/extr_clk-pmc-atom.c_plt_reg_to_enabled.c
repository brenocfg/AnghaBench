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

/* Variables and functions */
#define  PMC_CLK_CTL_FORCE_OFF 131 
#define  PMC_CLK_CTL_FORCE_ON 130 
#define  PMC_CLK_CTL_GATED_ON_D3 129 
#define  PMC_CLK_CTL_RESERVED 128 
 int PMC_MASK_CLK_CTL ; 

__attribute__((used)) static inline int plt_reg_to_enabled(int reg)
{
	switch (reg & PMC_MASK_CLK_CTL) {
	case PMC_CLK_CTL_GATED_ON_D3:
	case PMC_CLK_CTL_FORCE_ON:
		return 1;	/* enabled */
	case PMC_CLK_CTL_FORCE_OFF:
	case PMC_CLK_CTL_RESERVED:
	default:
		return 0;	/* disabled */
	}
}