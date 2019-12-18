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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  u_long ;
struct resource {int dummy; } ;
struct macio_softc {scalar_t__ sc_base; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int SYS_RES_IOPORT ; 
 int SYS_RES_IRQ ; 
 int SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bs_le_tag ; 
 int bus_activate_resource (int /*<<< orphan*/ ,int,int,struct resource*) ; 
 struct macio_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 void* pmap_mapdev (scalar_t__,int /*<<< orphan*/ ) ; 
 int rman_activate_resource (struct resource*) ; 
 scalar_t__ rman_get_size (struct resource*) ; 
 scalar_t__ rman_get_start (struct resource*) ; 
 int /*<<< orphan*/  rman_set_bushandle (struct resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_set_bustag (struct resource*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_set_virtual (struct resource*,void*) ; 

__attribute__((used)) static int
macio_activate_resource(device_t bus, device_t child, int type, int rid,
			   struct resource *res)
{
	struct macio_softc *sc;
	void    *p;

	sc = device_get_softc(bus);

	if (type == SYS_RES_IRQ)
                return (bus_activate_resource(bus, type, rid, res));

	if ((type == SYS_RES_MEMORY) || (type == SYS_RES_IOPORT)) {
		p = pmap_mapdev((vm_offset_t)rman_get_start(res) + sc->sc_base,
				(vm_size_t)rman_get_size(res));
		if (p == NULL)
			return (ENOMEM);
		rman_set_virtual(res, p);
		rman_set_bustag(res, &bs_le_tag);
		rman_set_bushandle(res, (u_long)p);
	}

	return (rman_activate_resource(res));
}