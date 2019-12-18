#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct clk {scalar_t__ sel_reg; int sel_mask; int sel_shift; int sel_val; scalar_t__ reg; int enable_reg; int div_mask; int div_shift; int div_val; } ;
struct ccm_softc {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct clk* clk; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int READ4 (struct ccm_softc*,scalar_t__) ; 
 int /*<<< orphan*/  WRITE4 (struct ccm_softc*,scalar_t__,int) ; 
 TYPE_1__* clock_map ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
set_clock(struct ccm_softc *sc, char *name)
{
	struct clk *clk;
	int reg;
	int i;

	for (i = 0; clock_map[i].name != NULL; i++) {
		if (strcmp(clock_map[i].name, name) == 0) {
#if 0
			device_printf(sc->dev, "Configuring %s clk\n", name);
#endif
			clk = clock_map[i].clk;
			if (clk->sel_reg != 0) {
				reg = READ4(sc, clk->sel_reg);
				reg &= ~(clk->sel_mask << clk->sel_shift);
				reg |= (clk->sel_val << clk->sel_shift);
				WRITE4(sc, clk->sel_reg, reg);
			}

			reg = READ4(sc, clk->reg);
			reg |= clk->enable_reg;
			reg &= ~(clk->div_mask << clk->div_shift);
			reg |= (clk->div_val << clk->div_shift);
			WRITE4(sc, clk->reg, reg);
		}
	}

	return (0);
}