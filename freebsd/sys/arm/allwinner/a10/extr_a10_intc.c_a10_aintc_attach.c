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
struct a10_aintc_softc {int /*<<< orphan*/  aintc_res; int /*<<< orphan*/  mtx; int /*<<< orphan*/  aintc_bsh; int /*<<< orphan*/  aintc_bst; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SW_INT_ENABLE_REG (int) ; 
 int /*<<< orphan*/  SW_INT_MASK_REG (int) ; 
 int /*<<< orphan*/  SW_INT_NMI_CTRL_REG ; 
 int /*<<< orphan*/  SW_INT_PROTECTION_REG ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ a10_intr_pic_attach (struct a10_aintc_softc*) ; 
 int /*<<< orphan*/  aintc_write_4 (struct a10_aintc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct a10_aintc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
a10_aintc_attach(device_t dev)
{
	struct a10_aintc_softc *sc = device_get_softc(dev);
	int rid = 0;
	int i;
	sc->sc_dev = dev;

	sc->aintc_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &rid, RF_ACTIVE);
	if (!sc->aintc_res) {
		device_printf(dev, "could not allocate resource\n");
		goto error;
	}

	sc->aintc_bst = rman_get_bustag(sc->aintc_res);
	sc->aintc_bsh = rman_get_bushandle(sc->aintc_res);

	mtx_init(&sc->mtx, "A10 AINTC lock", "", MTX_SPIN);

	/* Disable & clear all interrupts */
	for (i = 0; i < 3; i++) {
		aintc_write_4(sc, SW_INT_ENABLE_REG(i), 0);
		aintc_write_4(sc, SW_INT_MASK_REG(i), 0xffffffff);
	}
	/* enable protection mode*/
	aintc_write_4(sc, SW_INT_PROTECTION_REG, 0x01);

	/* config the external interrupt source type*/
	aintc_write_4(sc, SW_INT_NMI_CTRL_REG, 0x00);

	if (a10_intr_pic_attach(sc) != 0) {
		device_printf(dev, "could not attach PIC\n");
		return (ENXIO);
	}

	return (0);

error:
	bus_release_resource(dev, SYS_RES_MEMORY, rid,
	    sc->aintc_res);
	return (ENXIO);
}