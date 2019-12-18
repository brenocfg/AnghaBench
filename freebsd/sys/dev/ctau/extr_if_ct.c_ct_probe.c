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
typedef  scalar_t__ rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ NPORT ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 scalar_t__ bus_get_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  ct_is_free_res (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ct_probe_board (scalar_t__,int,int) ; 
 int /*<<< orphan*/  device_get_desc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ct_probe (device_t dev)
{
	int unit = device_get_unit (dev);
	rman_res_t iobase, rescount;

	if (!device_get_desc (dev) ||
	    strcmp (device_get_desc (dev), "Cronyx Tau-ISA"))
		return ENXIO;

/*	KASSERT ((bd != NULL), ("ct%d: NULL device softc\n", unit));*/
	if (bus_get_resource (dev, SYS_RES_IOPORT, 0, &iobase, &rescount) != 0) {
		printf ("ct%d: Couldn't get IOPORT\n", unit);
		return ENXIO;
	}

	if (!ct_is_free_res (dev, 0, SYS_RES_IOPORT,
	    iobase, iobase + NPORT, NPORT)) {
		printf ("ct%d: Resource IOPORT isn't free\n", unit);
		return ENXIO;
	}
		
	if (!ct_probe_board (iobase, -1, -1)) {
		printf ("ct%d: probing for Tau-ISA at %jx faild\n", unit, iobase);
		return ENXIO;
	}
	
	return 0;
}