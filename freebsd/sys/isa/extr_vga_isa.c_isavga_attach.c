#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  adp; } ;
typedef  TYPE_1__ vga_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  VGA_MKMINOR (int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_flags (int /*<<< orphan*/ ) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int fb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isavga_cdevsw ; 
 int vga_attach_unit (int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vidd_diag (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
isavga_attach(device_t dev)
{
	vga_softc_t *sc;
	int unit;
	int rid;
	int error;

	unit = device_get_unit(dev);
	sc = device_get_softc(dev);

	rid = 0;
	bus_alloc_resource_any(dev, SYS_RES_IOPORT, &rid,
				  RF_ACTIVE | RF_SHAREABLE);
	rid = 0;
	bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
				 RF_ACTIVE | RF_SHAREABLE);

	error = vga_attach_unit(unit, sc, device_get_flags(dev));
	if (error)
		return (error);

#ifdef FB_INSTALL_CDEV
	/* attach a virtual frame buffer device */
	error = fb_attach(VGA_MKMINOR(unit), sc->adp, &isavga_cdevsw);
	if (error)
		return (error);
#endif /* FB_INSTALL_CDEV */

	if (0 && bootverbose)
		vidd_diag(sc->adp, bootverbose);

#if 0 /* experimental */
	device_add_child(dev, "fb", -1);
	bus_generic_attach(dev);
#endif

	return (0);
}