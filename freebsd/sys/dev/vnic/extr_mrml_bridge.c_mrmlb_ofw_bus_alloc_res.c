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
typedef  int /*<<< orphan*/  u_int ;
struct simplebus_softc {int nranges; TYPE_1__* ranges; } ;
struct resource_list_entry {scalar_t__ start; scalar_t__ end; scalar_t__ count; } ;
struct resource {int dummy; } ;
struct mrmlb_ofw_devinfo {int /*<<< orphan*/  di_rl; } ;
typedef  scalar_t__ rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ bus; scalar_t__ size; scalar_t__ host; } ;

/* Variables and functions */
 scalar_t__ RMAN_IS_DEFAULT_RANGE (scalar_t__,scalar_t__) ; 
 int SYS_RES_IOPORT ; 
 int SYS_RES_MEMORY ; 
 struct resource* bus_generic_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct mrmlb_ofw_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct simplebus_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 struct resource_list_entry* resource_list_find (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static struct resource *
mrmlb_ofw_bus_alloc_res(device_t bus, device_t child, int type, int *rid,
    rman_res_t start, rman_res_t end, rman_res_t count, u_int flags)
{
	struct simplebus_softc *sc;
	struct mrmlb_ofw_devinfo *di;
	struct resource_list_entry *rle;
	int i;

	if (RMAN_IS_DEFAULT_RANGE(start, end)) {
		if ((di = device_get_ivars(child)) == NULL)
			return (NULL);
		if (type == SYS_RES_IOPORT)
		    type = SYS_RES_MEMORY;

		/* Find defaults for this rid */
		rle = resource_list_find(&di->di_rl, type, *rid);
		if (rle == NULL)
			return (NULL);

		start = rle->start;
		end = rle->end;
		count = rle->count;
	}

	sc = device_get_softc(bus);

	if (type == SYS_RES_MEMORY) {
		/* Remap through ranges property */
		for (i = 0; i < sc->nranges; i++) {
			if (start >= sc->ranges[i].bus && end <
			    sc->ranges[i].bus + sc->ranges[i].size) {
				start -= sc->ranges[i].bus;
				start += sc->ranges[i].host;
				end -= sc->ranges[i].bus;
				end += sc->ranges[i].host;
				break;
			}
		}

		if (i == sc->nranges && sc->nranges != 0) {
			device_printf(bus, "Could not map resource "
			    "%#lx-%#lx\n", start, end);
			return (NULL);
		}
	}

	return (bus_generic_alloc_resource(bus, child, type, rid, start, end,
	    count, flags));
}