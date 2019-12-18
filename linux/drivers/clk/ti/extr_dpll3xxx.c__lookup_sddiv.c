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
typedef  int u8 ;
typedef  unsigned long u16 ;
struct clk_hw_omap {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_hw_get_parent (int /*<<< orphan*/ *) ; 
 unsigned long clk_hw_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _lookup_sddiv(struct clk_hw_omap *clk, u8 *sd_div, u16 m, u8 n)
{
	unsigned long clkinp, sd; /* watch out for overflow */
	int mod1, mod2;

	clkinp = clk_hw_get_rate(clk_hw_get_parent(&clk->hw));

	/*
	 * target sigma-delta to near 250MHz
	 * sd = ceil[(m/(n+1)) * (clkinp_MHz / 250)]
	 */
	clkinp /= 100000; /* shift from MHz to 10*Hz for 38.4 and 19.2 */
	mod1 = (clkinp * m) % (250 * n);
	sd = (clkinp * m) / (250 * n);
	mod2 = sd % 10;
	sd /= 10;

	if (mod1 || mod2)
		sd++;
	*sd_div = sd;
}