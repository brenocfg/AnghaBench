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
 int /*<<< orphan*/  DDR_PHY_TIMING ; 
 unsigned int DDR_PHY_TIMING_CK ; 
 unsigned int DDR_PHY_TIMING_INC ; 
 unsigned int DDR_PHY_TIMING_I_CE ; 
 unsigned int DDR_PHY_TIMING_I_RST ; 
 unsigned int DDR_PHY_TIMING_W_CE ; 
 unsigned int DDR_PHY_TIMING_W_RST ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 

void set_ddr_timing(unsigned int w, unsigned int i)
{
	unsigned int reg;
	unsigned int wnow = 16;
	unsigned int inow = 32;

	/* reset all timing controls to known value (31) */
	writel(DDR_PHY_TIMING_W_RST | DDR_PHY_TIMING_I_RST, DDR_PHY_TIMING);
	writel(DDR_PHY_TIMING_W_RST | DDR_PHY_TIMING_I_RST | DDR_PHY_TIMING_CK,
	       DDR_PHY_TIMING);
	writel(DDR_PHY_TIMING_W_RST | DDR_PHY_TIMING_I_RST, DDR_PHY_TIMING);

	/* step up or down read delay to the requested value */
	while (wnow != w) {
		if (wnow < w) {
			reg = DDR_PHY_TIMING_INC;
			wnow++;
		} else {
			reg = 0;
			wnow--;
		}
		writel(DDR_PHY_TIMING_W_CE | reg, DDR_PHY_TIMING);
		writel(DDR_PHY_TIMING_CK | DDR_PHY_TIMING_W_CE | reg,
		       DDR_PHY_TIMING);
		writel(DDR_PHY_TIMING_W_CE | reg, DDR_PHY_TIMING);
	}

	/* now write delay */
	while (inow != i) {
		if (inow < i) {
			reg = DDR_PHY_TIMING_INC;
			inow++;
		} else {
			reg = 0;
			inow--;
		}
		writel(DDR_PHY_TIMING_I_CE | reg, DDR_PHY_TIMING);
		writel(DDR_PHY_TIMING_CK | DDR_PHY_TIMING_I_CE | reg,
		       DDR_PHY_TIMING);
		writel(DDR_PHY_TIMING_I_CE | reg, DDR_PHY_TIMING);
	}
}