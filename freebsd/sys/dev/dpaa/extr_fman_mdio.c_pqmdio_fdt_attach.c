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
struct pqmdio_softc {int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_offset; int /*<<< orphan*/  sc_handle; } ;
typedef  int /*<<< orphan*/  rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_get_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct pqmdio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fman_get_bushandle (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pqmdio_fdt_attach(device_t dev)
{
	struct pqmdio_softc *sc;
	rman_res_t start, count;

	sc = device_get_softc(dev);

	fman_get_bushandle(device_get_parent(dev), &sc->sc_handle);
	bus_get_resource(dev, SYS_RES_MEMORY, 0, &start, &count);
	sc->sc_offset = start;

	mtx_init(&sc->sc_lock, device_get_nameunit(dev), "QorIQ MDIO lock",
	    MTX_DEF);

	return (0);
}