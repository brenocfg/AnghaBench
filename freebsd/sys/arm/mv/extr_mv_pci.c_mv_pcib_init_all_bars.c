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
struct mv_pcib_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PCIM_HDRTYPE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int mv_pcib_init_bar (struct mv_pcib_softc*,int,int,int,int) ; 

__attribute__((used)) static int
mv_pcib_init_all_bars(struct mv_pcib_softc *sc, int bus, int slot,
    int func, int hdrtype)
{
	int maxbar, bar, i;

	maxbar = (hdrtype & PCIM_HDRTYPE) ? 0 : 6;
	bar = 0;

	/* Program the base address registers */
	while (bar < maxbar) {
		i = mv_pcib_init_bar(sc, bus, slot, func, bar);
		bar += i;
		if (i < 0) {
			device_printf(sc->sc_dev,
			    "PCI IO/Memory space exhausted\n");
			return (ENOMEM);
		}
	}

	return (0);
}