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
typedef  int rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int NPORT ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 scalar_t__ bus_get_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  cx_is_free_res (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  cx_probe_board (int,int,int) ; 
 int /*<<< orphan*/  device_get_desc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int* porttab ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int cx_probe (device_t dev)
{
	int unit = device_get_unit (dev);
	int i;
	rman_res_t iobase, rescount;

	if (!device_get_desc (dev) ||
	    strcmp (device_get_desc (dev), "Cronyx Sigma"))
		return ENXIO;
	
	if (bus_get_resource (dev, SYS_RES_IOPORT, 0, &iobase, &rescount) != 0) {
		printf ("cx%d: Couldn't get IOPORT\n", unit);
		return ENXIO;
	}

	if (!cx_is_free_res (dev, 0, SYS_RES_IOPORT,
	    iobase, iobase + NPORT, NPORT)) {
		printf ("cx%d: Resource IOPORT isn't free %lx\n", unit, iobase);
		return ENXIO;
	}
		
	for (i = 0; porttab [i] != 0; i++) {
		if (porttab [i] == iobase) {
			porttab [i] = -1;
			break;
		}
	}
	
	if (porttab [i] == 0) {
		return ENXIO;
	}
	
	if (!cx_probe_board (iobase, -1, -1)) {
		printf ("cx%d: probing for Sigma at %lx faild\n", unit, iobase);
		return ENXIO;
	}
	
	return 0;
}