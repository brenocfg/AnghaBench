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
typedef  int /*<<< orphan*/  cy_addr ;

/* Variables and functions */
 int /*<<< orphan*/  CY16_RESET ; 
 int /*<<< orphan*/  CY_CLEAR_INTR ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  cy_inb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cy_outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cy_units (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isa_get_logicalid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_virtual (struct resource*) ; 

__attribute__((used)) static int
cy_isa_probe(device_t dev)
{
	struct resource *mem_res;
	cy_addr iobase;
	int error, mem_rid;

	if (isa_get_logicalid(dev) != 0)	/* skip PnP probes */
		return (ENXIO);

	mem_rid = 0;
	mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &mem_rid,
	    RF_ACTIVE);
	if (mem_res == NULL) {
		device_printf(dev, "ioport resource allocation failed\n");
		return (ENXIO);
	}
	iobase = rman_get_virtual(mem_res);

	/* Cyclom-16Y hardware reset (Cyclom-8Ys don't care) */
	cy_inb(iobase, CY16_RESET, 0);	/* XXX? */
	DELAY(500);		/* wait for the board to get its act together */

	/* this is needed to get the board out of reset */
	cy_outb(iobase, CY_CLEAR_INTR, 0, 0);
	DELAY(500);

	error = (cy_units(iobase, 0) == 0 ? ENXIO : 0);
	bus_release_resource(dev, SYS_RES_MEMORY, mem_rid, mem_res);
	return (error);
}