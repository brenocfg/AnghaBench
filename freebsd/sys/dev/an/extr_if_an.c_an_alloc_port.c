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
struct resource {int dummy; } ;
struct an_softc {int port_rid; struct resource* port_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 struct resource* bus_alloc_resource_anywhere (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 struct an_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
an_alloc_port(device_t dev, int rid, int size)
{
	struct an_softc *sc = device_get_softc(dev);
	struct resource *res;

	res = bus_alloc_resource_anywhere(dev, SYS_RES_IOPORT, &rid,
					  size, RF_ACTIVE);
	if (res) {
		sc->port_rid = rid;
		sc->port_res = res;
		return (0);
	} else {
		return (ENOENT);
	}
}