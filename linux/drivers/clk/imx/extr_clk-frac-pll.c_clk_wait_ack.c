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
struct clk_frac_pll {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int PLL_BYPASS_MASK ; 
 int /*<<< orphan*/  PLL_FRAC_ACK_TIMEOUT ; 
 int PLL_NEWDIV_ACK ; 
 int PLL_PD_MASK ; 
 int readl_poll_timeout (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_wait_ack(struct clk_frac_pll *pll)
{
	u32 val;

	/* return directly if the pll is in powerdown or in bypass */
	if (readl_relaxed(pll->base) & (PLL_PD_MASK | PLL_BYPASS_MASK))
		return 0;

	/* Wait for the pll's divfi and divff to be reloaded */
	return readl_poll_timeout(pll->base, val, val & PLL_NEWDIV_ACK, 0,
					PLL_FRAC_ACK_TIMEOUT);
}