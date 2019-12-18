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
typedef  short rman_res_t ;
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/ * devclass_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ISA_ORDER_SPECULATIVE ; 
 int /*<<< orphan*/  M_TEMP ; 
 int NCTAU ; 
 short NPORT ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 scalar_t__ bus_get_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,short*,short*) ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,short,short) ; 
 int /*<<< orphan*/  ct_is_free_res (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,short,short,short) ; 
 scalar_t__ ct_probe_board (short,int,int) ; 
 int /*<<< orphan*/ * devclass_find (char*) ; 
 int /*<<< orphan*/  devclass_get_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ***,int*) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_set_driver (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 short* porttab ; 

__attribute__((used)) static void ct_identify (driver_t *driver, device_t dev)
{
	rman_res_t iobase, rescount;
	int devcount;
	device_t *devices;
	device_t child;
	devclass_t my_devclass;
	int i, k;

	if ((my_devclass = devclass_find ("ct")) == NULL)
		return;

	devclass_get_devices (my_devclass, &devices, &devcount);

	if (devcount == 0) {
		/* We should find all devices by our self. We could alter other
		 * devices, but we don't have a choise
		 */
		for (i = 0; (iobase = porttab [i]) != 0; i++) {
			if (!ct_is_free_res (dev, 0, SYS_RES_IOPORT,
			    iobase, iobase + NPORT, NPORT))
				continue;
			if (ct_probe_board (iobase, -1, -1) == 0)
				continue;
			
			devcount++;
			child = BUS_ADD_CHILD (dev, ISA_ORDER_SPECULATIVE, "ct",
			    -1);

			if (child == NULL)
				return;

			device_set_desc_copy (child, "Cronyx Tau-ISA");
			device_set_driver (child, driver);
			bus_set_resource (child, SYS_RES_IOPORT, 0,
			    iobase, NPORT);

			if (devcount >= NCTAU)
				break;
		}
	} else {
		static	short porttab [] = {
			0x200, 0x220, 0x240, 0x260, 0x280, 0x2a0, 0x2c0, 0x2e0,
			0x300, 0x320, 0x340, 0x360, 0x380, 0x3a0, 0x3c0, 0x3e0, 0
		};
		/* Lets check user choise.
		 */
		for (k = 0; k < devcount; k++) {
			if (bus_get_resource (devices[k], SYS_RES_IOPORT, 0,
			    &iobase, &rescount) != 0)
				continue;

			for (i = 0; porttab [i] != 0; i++) {
				if (porttab [i] != iobase)
					continue;
					
				if (!ct_is_free_res (devices[k], 0, SYS_RES_IOPORT,
				    iobase, iobase + NPORT, NPORT))
					continue;

				if (ct_probe_board (iobase, -1, -1) == 0)
					continue;
				porttab [i] = -1;
				device_set_desc_copy (devices[k], "Cronyx Tau-ISA");
				break;
			}
			if (porttab [i] == 0) {
				device_delete_child (
				    device_get_parent (devices[k]),
				    devices [k]);
				devices[k] = 0;
				continue;
			}
		}
		for (k = 0; k < devcount; k++) {
			if (devices[k] == 0)
				continue;
			if (bus_get_resource (devices[k], SYS_RES_IOPORT, 0,
			    &iobase, &rescount) == 0)
				continue;
			for (i = 0; (iobase = porttab [i]) != 0; i++) {
				if (porttab [i] == -1)
					continue;
				if (!ct_is_free_res (devices[k], 0, SYS_RES_IOPORT,
				    iobase, iobase + NPORT, NPORT))
					continue;
				if (ct_probe_board (iobase, -1, -1) == 0)
					continue;
			
				bus_set_resource (devices[k], SYS_RES_IOPORT, 0,
				    iobase, NPORT);
				porttab [i] = -1;
				device_set_desc_copy (devices[k], "Cronyx Tau-ISA");
				break;
			}
			if (porttab [i] == 0) {
				device_delete_child (
				    device_get_parent (devices[k]),
				    devices [k]);
			}
		}		
		free (devices, M_TEMP);
	}
	
	return;
}