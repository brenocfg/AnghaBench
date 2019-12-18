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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_LOCK (struct pgate_sc*) ; 
 int /*<<< orphan*/  DEVICE_UNLOCK (struct pgate_sc*) ; 
 int /*<<< orphan*/  RD4 (struct pgate_sc*,int /*<<< orphan*/ ,int*) ; 
 struct pgate_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  clknode_init_parent_idx (struct clknode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_enable_reg (int) ; 
 int /*<<< orphan*/  get_reset_reg (int) ; 

__attribute__((used)) static int
pgate_init(struct clknode *clk, device_t dev)
{
	struct pgate_sc *sc;
	uint32_t ena_reg, rst_reg, mask;

	sc = clknode_get_softc(clk);
	mask = 1 << (sc->idx % 32);

	DEVICE_LOCK(sc);
	RD4(sc, get_enable_reg(sc->idx), &ena_reg);
	RD4(sc, get_reset_reg(sc->idx), &rst_reg);
	DEVICE_UNLOCK(sc);

	sc->enabled = ena_reg & mask ? 1 : 0;
	clknode_init_parent_idx(clk, 0);

	return(0);
}