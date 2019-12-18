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
struct periph_sc {int flags; int mux; int /*<<< orphan*/  base_reg; } ;
struct clknode {int dummy; } ;

/* Variables and functions */
 int DCF_HAVE_MUX ; 
 int DCF_IS_AUDIO ; 
 int DCF_IS_MASK ; 
 int /*<<< orphan*/  DEVICE_LOCK (struct periph_sc*) ; 
 int /*<<< orphan*/  DEVICE_UNLOCK (struct periph_sc*) ; 
 int ENXIO ; 
 int PERLCK_AMUX_DIS ; 
 int PERLCK_AMUX_SHIFT ; 
 int PERLCK_MUX_MASK ; 
 int PERLCK_MUX_SHIFT ; 
 int /*<<< orphan*/  RD4 (struct periph_sc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  WR4 (struct periph_sc*,int /*<<< orphan*/ ,int) ; 
 struct periph_sc* clknode_get_softc (struct clknode*) ; 

__attribute__((used)) static int
periph_set_mux(struct clknode *clk, int idx)
{
	struct periph_sc *sc;
	uint32_t reg;


	sc = clknode_get_softc(clk);
	if (!(sc->flags & DCF_HAVE_MUX))
		return (ENXIO);

	sc->mux = idx;
	DEVICE_LOCK(sc);
	RD4(sc, sc->base_reg, &reg);
	reg &= ~(PERLCK_MUX_MASK << PERLCK_MUX_SHIFT);
	if ((sc->flags & DCF_IS_MASK) == DCF_IS_AUDIO) {
		reg &= ~PERLCK_AMUX_DIS;
		reg &= ~(PERLCK_MUX_MASK << PERLCK_AMUX_SHIFT);

		if (idx <= 7) {
			reg |= idx << PERLCK_MUX_SHIFT;
		} else {
			reg |= 7 << PERLCK_MUX_SHIFT;
			reg |= (idx - 8) << PERLCK_AMUX_SHIFT;
		}
	} else {
		reg |= idx << PERLCK_MUX_SHIFT;
	}
	WR4(sc, sc->base_reg, reg);
	DEVICE_UNLOCK(sc);

	return(0);
}