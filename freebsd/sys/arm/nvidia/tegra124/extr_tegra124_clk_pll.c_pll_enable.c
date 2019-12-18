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
typedef  int /*<<< orphan*/  uint32_t ;
struct pll_sc {scalar_t__ type; int /*<<< orphan*/  base_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_BASE_BYPASS ; 
 int /*<<< orphan*/  PLL_BASE_ENABLE ; 
 scalar_t__ PLL_E ; 
 int /*<<< orphan*/  RD4 (struct pll_sc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WR4 (struct pll_sc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pll_enable(struct pll_sc *sc)
{
	uint32_t reg;


	RD4(sc, sc->base_reg, &reg);
	if (sc->type != PLL_E)
		reg &= ~PLL_BASE_BYPASS;
	reg |= PLL_BASE_ENABLE;
	WR4(sc, sc->base_reg, reg);
	return (0);
}