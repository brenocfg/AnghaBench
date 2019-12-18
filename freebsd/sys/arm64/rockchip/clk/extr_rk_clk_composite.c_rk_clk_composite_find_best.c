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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct rk_clk_composite_sc {int div_mask; int div_shift; scalar_t__ flags; } ;

/* Variables and functions */
 scalar_t__ RK_CLK_COMPOSITE_DIV_EXP ; 

__attribute__((used)) static uint32_t
rk_clk_composite_find_best(struct rk_clk_composite_sc *sc, uint64_t fparent,
    uint64_t freq, uint32_t *reg)
{
	uint64_t best, cur;
	uint32_t best_div, best_div_reg;
	uint32_t div, div_reg;

	best = 0;
	best_div = 0;
	best_div_reg = 0;

	for (div_reg = 0;  div_reg <= ((sc->div_mask >> sc->div_shift) + 1);
	    div_reg++) {
		if (sc->flags == RK_CLK_COMPOSITE_DIV_EXP)
			div = 1 << div_reg;
		else
			div = div_reg + 1;
		cur = fparent / div;
		if ((freq - cur) < (freq - best)) {
			best = cur;
			best_div = div;
			best_div_reg = div_reg;
			break;
		}
	}
	*reg = div_reg;
	return (best_div);
}