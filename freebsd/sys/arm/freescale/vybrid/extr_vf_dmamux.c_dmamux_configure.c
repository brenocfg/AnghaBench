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
struct dmamux_softc {int dummy; } ;

/* Variables and functions */
 int CHCFG_ENBL ; 
 int CHCFG_SOURCE_MASK ; 
 int CHCFG_SOURCE_SHIFT ; 
 int /*<<< orphan*/  DMAMUX_CHCFG (int) ; 
 int /*<<< orphan*/  MUX_WRITE1 (struct dmamux_softc*,int,int /*<<< orphan*/ ,int) ; 
 struct dmamux_softc* dmamux_sc ; 

int
dmamux_configure(int mux, int source, int channel, int enable)
{
	struct dmamux_softc *sc;
	int reg;

	sc = dmamux_sc;

	MUX_WRITE1(sc, mux, DMAMUX_CHCFG(channel), 0x0);

	reg = 0;
	if (enable)
		reg |= (CHCFG_ENBL);

	reg &= ~(CHCFG_SOURCE_MASK << CHCFG_SOURCE_SHIFT);
	reg |= (source << CHCFG_SOURCE_SHIFT);

	MUX_WRITE1(sc, mux, DMAMUX_CHCFG(channel), reg);

	return (0);
}