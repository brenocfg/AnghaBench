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
typedef  int u32 ;
struct iproc_arm_pll {scalar_t__ base; } ;

/* Variables and functions */
 int IPROC_CLK_PLLARMA_NDIV_INT_MASK ; 
 int IPROC_CLK_PLLARMA_NDIV_INT_SHIFT ; 
 scalar_t__ IPROC_CLK_PLLARMA_OFFSET ; 
 int IPROC_CLK_PLLARMB_NDIV_FRAC_MASK ; 
 scalar_t__ IPROC_CLK_PLLARMB_OFFSET ; 
 int IPROC_CLK_PLLARM_NDIV_FRAC_OFFSET_MASK ; 
 int IPROC_CLK_PLLARM_NDIV_INT_OFFSET_MASK ; 
 int IPROC_CLK_PLLARM_NDIV_INT_OFFSET_SHIFT ; 
 scalar_t__ IPROC_CLK_PLLARM_OFFSET_OFFSET ; 
 int IPROC_CLK_PLLARM_SW_CTL_SHIFT ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static unsigned int __get_ndiv(struct iproc_arm_pll *pll)
{
	u32 val;
	unsigned int ndiv_int, ndiv_frac, ndiv;

	val = readl(pll->base + IPROC_CLK_PLLARM_OFFSET_OFFSET);
	if (val & (1 << IPROC_CLK_PLLARM_SW_CTL_SHIFT)) {
		/*
		 * offset mode is active. Read the ndiv from the PLLARM OFFSET
		 * register
		 */
		ndiv_int = (val >> IPROC_CLK_PLLARM_NDIV_INT_OFFSET_SHIFT) &
			IPROC_CLK_PLLARM_NDIV_INT_OFFSET_MASK;
		if (ndiv_int == 0)
			ndiv_int = 256;

		ndiv_frac = val & IPROC_CLK_PLLARM_NDIV_FRAC_OFFSET_MASK;
	} else {
		/* offset mode not active */
		val = readl(pll->base + IPROC_CLK_PLLARMA_OFFSET);
		ndiv_int = (val >> IPROC_CLK_PLLARMA_NDIV_INT_SHIFT) &
			IPROC_CLK_PLLARMA_NDIV_INT_MASK;
		if (ndiv_int == 0)
			ndiv_int = 1024;

		val = readl(pll->base + IPROC_CLK_PLLARMB_OFFSET);
		ndiv_frac = val & IPROC_CLK_PLLARMB_NDIV_FRAC_MASK;
	}

	ndiv = (ndiv_int << 20) | ndiv_frac;

	return ndiv;
}