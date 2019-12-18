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
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int ENXIO ; 
#define  SYS_RES_IOPORT 130 
#define  SYS_RES_IRQ 129 
#define  SYS_RES_MEMORY 128 
 int bus_generic_activate_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
 int bus_space_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rman_activate_resource (struct resource*) ; 
 int /*<<< orphan*/  rman_get_bushandle (struct resource*) ; 
 int /*<<< orphan*/  rman_get_bustag (struct resource*) ; 
 int /*<<< orphan*/  rman_get_size (struct resource*) ; 
 int /*<<< orphan*/  rman_set_bushandle (struct resource*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
octopci_activate_resource(device_t bus, device_t child, int type, int rid,
    struct resource *res)
{
	bus_space_handle_t bh;
	int error;

	switch (type) {
	case SYS_RES_IRQ:
		error = bus_generic_activate_resource(bus, child, type, rid,
						      res);
		if (error != 0)
			return (error);
		return (0);
	case SYS_RES_MEMORY:
	case SYS_RES_IOPORT:
		error = bus_space_map(rman_get_bustag(res),
		    rman_get_bushandle(res), rman_get_size(res), 0, &bh);
		if (error != 0)
			return (error);
		rman_set_bushandle(res, bh);
		break;
	default:
		return (ENXIO);
	}

	error = rman_activate_resource(res);
	if (error != 0)
		return (error);
	return (0);
}