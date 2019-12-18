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
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long ACSR ; 
 int /*<<< orphan*/  MEMCLKCFG ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 unsigned long* df_clkdiv ; 
 unsigned long* smcfs_mult ; 

__attribute__((used)) static unsigned long clk_pxa3xx_smemc_get_rate(struct clk_hw *hw,
					      unsigned long parent_rate)
{
	unsigned long acsr = ACSR;
	unsigned long memclkcfg = __raw_readl(MEMCLKCFG);

	return (parent_rate / 48)  * smcfs_mult[(acsr >> 23) & 0x7] /
		df_clkdiv[(memclkcfg >> 16) & 0x3];
}