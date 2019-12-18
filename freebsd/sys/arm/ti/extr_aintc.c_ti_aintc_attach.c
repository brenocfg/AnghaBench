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
struct ti_aintc_softc {int /*<<< orphan*/ * aintc_res; int /*<<< orphan*/  aintc_bsh; int /*<<< orphan*/  aintc_bst; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  INTC_REVISION ; 
 int /*<<< orphan*/  INTC_SYSCONFIG ; 
 int /*<<< orphan*/  INTC_SYSSTATUS ; 
 int /*<<< orphan*/  INTC_THRESHOLD ; 
 int aintc_read_4 (struct ti_aintc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aintc_write_4 (struct ti_aintc_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ti_aintc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 
 scalar_t__ ti_aintc_pic_attach (struct ti_aintc_softc*) ; 
 int /*<<< orphan*/  ti_aintc_spec ; 

__attribute__((used)) static int
ti_aintc_attach(device_t dev)
{
	struct		ti_aintc_softc *sc = device_get_softc(dev);
	uint32_t x;

	sc->sc_dev = dev;

	if (bus_alloc_resources(dev, ti_aintc_spec, sc->aintc_res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	sc->aintc_bst = rman_get_bustag(sc->aintc_res[0]);
	sc->aintc_bsh = rman_get_bushandle(sc->aintc_res[0]);

	x = aintc_read_4(sc, INTC_REVISION);
	device_printf(dev, "Revision %u.%u\n",(x >> 4) & 0xF, x & 0xF);

	/* SoftReset */
	aintc_write_4(sc, INTC_SYSCONFIG, 2);

	/* Wait for reset to complete */
	while(!(aintc_read_4(sc, INTC_SYSSTATUS) & 1));

	/*Set Priority Threshold */
	aintc_write_4(sc, INTC_THRESHOLD, 0xFF);

	if (ti_aintc_pic_attach(sc) != 0) {
		device_printf(dev, "could not attach PIC\n");
		return (ENXIO);
	}
	return (0);
}