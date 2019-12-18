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
struct pbio_softc {int /*<<< orphan*/ * res; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/ * res; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IO_PBIOSIZE ; 
 int /*<<< orphan*/  PBIO_CFG ; 
 int /*<<< orphan*/  PBIO_PORTA ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/ * bus_alloc_resource_anywhere (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct pbio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isa_get_logicalid (int /*<<< orphan*/ ) ; 
 int pbinb (struct pbio_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pboutb (struct pbio_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,unsigned char,...) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int rman_get_start (int /*<<< orphan*/ *) ; 
 TYPE_1__* sc ; 

__attribute__((used)) static int
pbioprobe(device_t dev)
{
	int		rid;
	struct pbio_softc *scp = device_get_softc(dev);
#ifdef GENERIC_PBIO_PROBE
	unsigned char val;
#endif

	if (isa_get_logicalid(dev))		/* skip PnP probes */
		return (ENXIO);
	rid = 0;
	scp->res = bus_alloc_resource_anywhere(dev, SYS_RES_IOPORT, &rid,
	    IO_PBIOSIZE, RF_ACTIVE);
	if (scp->res == NULL)
		return (ENXIO);

#ifdef GENERIC_PBIO_PROBE
	scp->bst = rman_get_bustag(scp->res);
	scp->bsh = rman_get_bushandle(scp->res);
	/*
	 * try see if the device is there.
	 * This probe works only if the device has no I/O attached to it
	 * XXX Better allow flags to abort testing
	 */
	/* Set all ports to output */
	pboutb(scp, PBIO_CFG, 0x80);
	printf("pbio val(CFG: 0x%03x)=0x%02x (should be 0x80)\n",
		rman_get_start(scp->res), pbinb(scp, PBIO_CFG));
	pboutb(scp, PBIO_PORTA, 0xa5);
	val = pbinb(scp, PBIO_PORTA);
	printf("pbio val=0x%02x (should be 0xa5)\n", val);
	if (val != 0xa5) {
		bus_release_resource(dev, SYS_RES_IOPORT, rid, sc->res);
		return (ENXIO);
	}
	pboutb(scp, PBIO_PORTA, 0x5a);
	val = pbinb(scp, PBIO_PORTA);
	printf("pbio val=0x%02x (should be 0x5a)\n", val);
	if (val != 0x5a) {
		bus_release_resource(dev, SYS_RES_IOPORT, rid, sc->res);
		return (ENXIO);
	}
#endif
	device_set_desc(dev, "Intel 8255 PPI (basic mode)");
	/* Set all ports to input */
	/* pboutb(scp, PBIO_CFG, 0x9b); */
	bus_release_resource(dev, SYS_RES_IOPORT, rid, scp->res);
	return (0);
}