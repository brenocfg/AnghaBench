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
struct samsung_pll_rate_table {int mdiv; int pdiv; } ;

/* Variables and functions */
 int PLL35XX_MDIV_MASK ; 
 int PLL35XX_MDIV_SHIFT ; 
 int PLL35XX_PDIV_MASK ; 
 int PLL35XX_PDIV_SHIFT ; 

__attribute__((used)) static inline bool samsung_pll35xx_mp_change(
		const struct samsung_pll_rate_table *rate, u32 pll_con)
{
	u32 old_mdiv, old_pdiv;

	old_mdiv = (pll_con >> PLL35XX_MDIV_SHIFT) & PLL35XX_MDIV_MASK;
	old_pdiv = (pll_con >> PLL35XX_PDIV_SHIFT) & PLL35XX_PDIV_MASK;

	return (rate->mdiv != old_mdiv || rate->pdiv != old_pdiv);
}