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
typedef  int /*<<< orphan*/  u16 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ cdce925_pll_calculate_rate (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdce925_pll_find_rate (unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static long cdce925_pll_round_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long *parent_rate)
{
	u16 n, m;

	cdce925_pll_find_rate(rate, *parent_rate, &n, &m);
	return (long)cdce925_pll_calculate_rate(*parent_rate, n, m);
}