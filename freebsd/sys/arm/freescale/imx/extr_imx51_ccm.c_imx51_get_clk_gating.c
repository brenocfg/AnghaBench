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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCMC_CCGR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CCMR_CCGR_MODULE (int) ; 
 int CCMR_CCGR_NSOURCE ; 
 int ccm_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccm_softc ; 

int
imx51_get_clk_gating(int clk_src)
{
	uint32_t reg;

	reg = ccm_read_4(ccm_softc,
	    CCMC_CCGR(CCMR_CCGR_MODULE(clk_src)));
	return ((reg >> (clk_src % CCMR_CCGR_NSOURCE) * 2) & 0x03);
}