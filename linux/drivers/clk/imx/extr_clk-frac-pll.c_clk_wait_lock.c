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
 int /*<<< orphan*/  PLL_FRAC_LOCK_TIMEOUT ; 
 int PLL_LOCK_STATUS ; 
 int readl_poll_timeout (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_wait_lock(struct clk_frac_pll *pll)
{
	u32 val;

	return readl_poll_timeout(pll->base, val, val & PLL_LOCK_STATUS, 0,
					PLL_FRAC_LOCK_TIMEOUT);
}