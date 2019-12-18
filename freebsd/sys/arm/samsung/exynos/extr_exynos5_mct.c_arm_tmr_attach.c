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
struct arm_tmr_softc {int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; int /*<<< orphan*/ * tmr_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MCT_CTRL ; 
 int MCT_CTRL_START ; 
 int /*<<< orphan*/  MCT_WRITE_STAT ; 
 int /*<<< orphan*/  arm_tmr_spec ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpufunc_nullop () ; 
 struct arm_tmr_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
arm_tmr_attach(device_t dev)
{
	struct arm_tmr_softc *sc;
	int reg, i;
	int mask;

	sc = device_get_softc(dev);

	if (bus_alloc_resources(dev, arm_tmr_spec, sc->tmr_res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	/* Timer interface */
	sc->bst = rman_get_bustag(sc->tmr_res[0]);
	sc->bsh = rman_get_bushandle(sc->tmr_res[0]);

	reg = bus_space_read_4(sc->bst, sc->bsh, MCT_CTRL);
	reg |= MCT_CTRL_START;
	bus_space_write_4(sc->bst, sc->bsh, MCT_CTRL, reg);

	mask = (1 << 16);

	/* Wait 10 times until written value is applied */
	for (i = 0; i < 10; i++) {
		reg = bus_space_read_4(sc->bst, sc->bsh, MCT_WRITE_STAT);
		if (reg & mask) {
			bus_space_write_4(sc->bst, sc->bsh,
			    MCT_WRITE_STAT, mask);
			return (0);
		}
		cpufunc_nullop();
	}

	/* NOTREACHED */

	panic("Can't enable timer\n");
}