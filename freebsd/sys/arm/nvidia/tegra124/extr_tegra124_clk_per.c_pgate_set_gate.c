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
struct pgate_sc {int idx; int enabled; } ;
struct clknode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  DEVICE_LOCK (struct pgate_sc*) ; 
 int /*<<< orphan*/  DEVICE_UNLOCK (struct pgate_sc*) ; 
 int /*<<< orphan*/  MD4 (struct pgate_sc*,int,int,int) ; 
 int /*<<< orphan*/  RD4 (struct pgate_sc*,int,int*) ; 
 struct pgate_sc* clknode_get_softc (struct clknode*) ; 
 int get_enable_reg (int) ; 

__attribute__((used)) static int
pgate_set_gate(struct clknode *clk, bool enable)
{
	struct pgate_sc *sc;
	uint32_t reg, mask, base_reg;

	sc = clknode_get_softc(clk);
	mask = 1 << (sc->idx % 32);
	sc->enabled = enable;
	base_reg = get_enable_reg(sc->idx);

	DEVICE_LOCK(sc);
	MD4(sc, base_reg, mask, enable ? mask : 0);
	RD4(sc, base_reg, &reg);
	DEVICE_UNLOCK(sc);

	DELAY(2);
	return(0);
}