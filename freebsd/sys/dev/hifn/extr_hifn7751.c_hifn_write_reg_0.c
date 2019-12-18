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
typedef  int /*<<< orphan*/  u_int32_t ;
struct hifn_softc {int sc_flags; int sc_bar0_lastreg; int /*<<< orphan*/  sc_sh0; int /*<<< orphan*/  sc_st0; } ;
typedef  int bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  HIFN_0_PUCNFG ; 
 int HIFN_IS_7811 ; 
 int /*<<< orphan*/  bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hifn_write_reg_0(struct hifn_softc *sc, bus_size_t reg, u_int32_t val)
{
	if (sc->sc_flags & HIFN_IS_7811) {
		if (sc->sc_bar0_lastreg == reg - 4)
			bus_space_read_4(sc->sc_st0, sc->sc_sh0, HIFN_0_PUCNFG);
		sc->sc_bar0_lastreg = reg;
	}
	bus_space_write_4(sc->sc_st0, sc->sc_sh0, reg, val);
}