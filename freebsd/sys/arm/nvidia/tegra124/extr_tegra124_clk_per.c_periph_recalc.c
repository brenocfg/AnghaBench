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
typedef  int /*<<< orphan*/  uint32_t ;
struct periph_sc {int flags; int div_f_width; int divider; int /*<<< orphan*/  base_reg; } ;
struct clknode {int dummy; } ;

/* Variables and functions */
 int DCF_HAVE_DIV ; 
 int /*<<< orphan*/  DEVICE_LOCK (struct periph_sc*) ; 
 int /*<<< orphan*/  DEVICE_UNLOCK (struct periph_sc*) ; 
 int /*<<< orphan*/  RD4 (struct periph_sc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct periph_sc* clknode_get_softc (struct clknode*) ; 

__attribute__((used)) static int
periph_recalc(struct clknode *clk, uint64_t *freq)
{
	struct periph_sc *sc;
	uint32_t reg;

	sc = clknode_get_softc(clk);

	if (sc->flags & DCF_HAVE_DIV) {
		DEVICE_LOCK(sc);
		RD4(sc, sc->base_reg, &reg);
		DEVICE_UNLOCK(sc);
		*freq = (*freq << sc->div_f_width) / sc->divider;
	}
	return (0);
}