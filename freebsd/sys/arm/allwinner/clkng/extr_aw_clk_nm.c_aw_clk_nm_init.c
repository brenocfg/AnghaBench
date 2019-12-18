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
struct aw_clk_nm_sc {int flags; int mux_mask; int mux_shift; int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AW_CLK_HAS_MUX ; 
 int /*<<< orphan*/  DEVICE_LOCK (struct clknode*) ; 
 int /*<<< orphan*/  DEVICE_UNLOCK (struct clknode*) ; 
 int /*<<< orphan*/  READ4 (struct clknode*,int /*<<< orphan*/ ,int*) ; 
 struct aw_clk_nm_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  clknode_init_parent_idx (struct clknode*,int) ; 

__attribute__((used)) static int
aw_clk_nm_init(struct clknode *clk, device_t dev)
{
	struct aw_clk_nm_sc *sc;
	uint32_t val, idx;

	sc = clknode_get_softc(clk);

	idx = 0;
	if ((sc->flags & AW_CLK_HAS_MUX) != 0) {
		DEVICE_LOCK(clk);
		READ4(clk, sc->offset, &val);
		DEVICE_UNLOCK(clk);

		idx = (val & sc->mux_mask) >> sc->mux_shift;
	}

	clknode_init_parent_idx(clk, idx);
	return (0);
}