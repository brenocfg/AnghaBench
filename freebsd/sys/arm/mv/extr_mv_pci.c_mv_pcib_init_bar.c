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
struct mv_pcib_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int PCIR_BAR (int) ; 
 scalar_t__ bootverbose ; 
 int mv_pcib_read_config (int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  mv_pcib_write_config (int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int pcib_alloc (struct mv_pcib_softc*,int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int) ; 

__attribute__((used)) static int
mv_pcib_init_bar(struct mv_pcib_softc *sc, int bus, int slot, int func,
    int barno)
{
	uint32_t addr, bar;
	int reg, width;

	reg = PCIR_BAR(barno);

	/*
	 * Need to init the BAR register with 0xffffffff before correct
	 * value can be read.
	 */
	mv_pcib_write_config(sc->sc_dev, bus, slot, func, reg, ~0, 4);
	bar = mv_pcib_read_config(sc->sc_dev, bus, slot, func, reg, 4);
	if (bar == 0)
		return (1);

	/* Calculate BAR size: 64 or 32 bit (in 32-bit units) */
	width = ((bar & 7) == 4) ? 2 : 1;

	addr = pcib_alloc(sc, bar);
	if (!addr)
		return (-1);

	if (bootverbose)
		printf("PCI %u:%u:%u: reg %x: smask=%08x: addr=%08x\n",
		    bus, slot, func, reg, bar, addr);

	mv_pcib_write_config(sc->sc_dev, bus, slot, func, reg, addr, 4);
	if (width == 2)
		mv_pcib_write_config(sc->sc_dev, bus, slot, func, reg + 4,
		    0, 4);

	return (width);
}