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
typedef  scalar_t__ uint32_t ;
struct pll_sc {int type; int /*<<< orphan*/  base_reg; int /*<<< orphan*/  misc_reg; } ;

/* Variables and functions */
 scalar_t__ PLLE_MISC_LOCK ; 
 scalar_t__ PLLRE_MISC_LOCK ; 
 scalar_t__ PLL_BASE_LOCK ; 
#define  PLL_E 129 
#define  PLL_REFE 128 
 int /*<<< orphan*/  RD4 (struct pll_sc*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static bool
is_locked(struct pll_sc *sc)
{
	uint32_t reg;

	switch (sc->type) {
	case PLL_REFE:
		RD4(sc, sc->misc_reg, &reg);
		reg &=  PLLRE_MISC_LOCK;
		break;

	case PLL_E:
		RD4(sc, sc->misc_reg, &reg);
		reg &= PLLE_MISC_LOCK;
		break;

	default:
		RD4(sc, sc->base_reg, &reg);
		reg &= PLL_BASE_LOCK;
		break;
	}
	return (reg != 0);
}