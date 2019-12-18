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
struct iicoc_softc {int /*<<< orphan*/ * iicbus; int /*<<< orphan*/ * mem_res; scalar_t__ mem_rid; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_anywhere (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct iicoc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iicoc_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iicoc_attach(device_t dev)
{
	int bus;
	struct iicoc_softc *sc;

	sc = device_get_softc(dev);
	bus = device_get_unit(dev);

	sc->dev = dev;
	mtx_init(&sc->sc_mtx, "iicoc", "iicoc", MTX_DEF);
	sc->mem_rid = 0;
	sc->mem_res = bus_alloc_resource_anywhere(dev,
	    SYS_RES_MEMORY, &sc->mem_rid, 0x100, RF_ACTIVE);

	if (sc->mem_res == NULL) {
		device_printf(dev, "Could not allocate bus resource.\n");
		return (-1);
	}
	iicoc_init(dev);
	sc->iicbus = device_add_child(dev, "iicbus", -1);
	if (sc->iicbus == NULL) {
		device_printf(dev, "Could not allocate iicbus instance.\n");
		return (-1);
	}
	bus_generic_attach(dev);

	return (0);
}