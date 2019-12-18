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
typedef  int uint32_t ;
struct clknode {int dummy; } ;
struct aw_clk_mipi_sc {int gate_shift; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_LOCK (struct clknode*) ; 
 int /*<<< orphan*/  DEVICE_UNLOCK (struct clknode*) ; 
 int LDO1_EN_SHIFT ; 
 int LDO2_EN_SHIFT ; 
 int /*<<< orphan*/  READ4 (struct clknode*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  WRITE4 (struct clknode*,int /*<<< orphan*/ ,int) ; 
 struct aw_clk_mipi_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  dprintf (char*,char*) ; 

__attribute__((used)) static int
aw_clk_mipi_set_gate(struct clknode *clk, bool enable)
{
	struct aw_clk_mipi_sc *sc;
	uint32_t val;

	sc = clknode_get_softc(clk);

	dprintf("%sabling gate\n", enable ? "En" : "Dis");
	DEVICE_LOCK(clk);
	READ4(clk, sc->offset, &val);
	if (enable) {
		val |= (1 << sc->gate_shift);
		val |= (1 << LDO1_EN_SHIFT);
		val |= (1 << LDO2_EN_SHIFT);
	} else {
		val &= ~(1 << sc->gate_shift);
		val &= ~(1 << LDO1_EN_SHIFT);
		val &= ~(1 << LDO2_EN_SHIFT);
	}
	WRITE4(clk, sc->offset, val);
	DEVICE_UNLOCK(clk);

	return (0);
}