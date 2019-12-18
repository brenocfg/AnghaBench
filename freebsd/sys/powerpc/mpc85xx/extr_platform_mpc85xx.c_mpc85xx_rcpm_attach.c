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
struct mpc85xx_rcpm_softc {int /*<<< orphan*/  sc_mem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 struct mpc85xx_rcpm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeze_timebase ; 
 int /*<<< orphan*/  mpc85xx_rcpm_freeze_timebase ; 
 int /*<<< orphan*/  rcpm_dev ; 

__attribute__((used)) static int
mpc85xx_rcpm_attach(device_t dev)
{
	struct mpc85xx_rcpm_softc *sc;
	int rid;

	sc = device_get_softc(dev);
	freeze_timebase = mpc85xx_rcpm_freeze_timebase;
	rcpm_dev = dev;

	rid = 0;
	sc->sc_mem = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
	    RF_ACTIVE | RF_SHAREABLE);

	return (0);
}