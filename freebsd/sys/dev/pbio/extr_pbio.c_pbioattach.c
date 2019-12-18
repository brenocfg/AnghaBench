#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pbio_softc {int iomode; TYPE_1__* pd; int /*<<< orphan*/ * res; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IO_PBIOSIZE ; 
 int PBIO_NPORTS ; 
 int /*<<< orphan*/  PBIO_PNAME (int) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/ * bus_alloc_resource_anywhere (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pbio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_dev (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pbio_cdevsw ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pbioattach (device_t dev)
{
	int unit;
	int i;
	int		rid;
	struct pbio_softc *sc;

	sc = device_get_softc(dev);
	unit = device_get_unit(dev);
	rid = 0;
	sc->res = bus_alloc_resource_anywhere(dev, SYS_RES_IOPORT, &rid,
	    IO_PBIOSIZE, RF_ACTIVE);
	if (sc->res == NULL)
		return (ENXIO);
	sc->bst = rman_get_bustag(sc->res);
	sc->bsh = rman_get_bushandle(sc->res);

	/*
	 * Store whatever seems wise.
	 */
	sc->iomode = 0x9b;		/* All ports to input */

	for (i = 0; i < PBIO_NPORTS; i++)
		sc->pd[i].port = make_dev(&pbio_cdevsw, (unit << 2) + i, 0, 0,
		    0600, "pbio%d%s", unit, PBIO_PNAME(i));
	return (0);
}