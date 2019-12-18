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
typedef  int /*<<< orphan*/  device_t ;
typedef  int TW_UINT8 ;
typedef  int /*<<< orphan*/  TW_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  TW_OSLI_DEVICE_NAME ; 
 char* TW_OSL_DRIVER_VERSION_STRING ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_vendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ tw_cl_ctlr_supported (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_osli_dbg_printf (int,char*) ; 

__attribute__((used)) static TW_INT32
twa_probe(device_t dev)
{
	static TW_UINT8	first_ctlr = 1;

	tw_osli_dbg_printf(3, "entered");

	if (tw_cl_ctlr_supported(pci_get_vendor(dev), pci_get_device(dev))) {
		device_set_desc(dev, TW_OSLI_DEVICE_NAME);
		/* Print the driver version only once. */
		if (first_ctlr) {
			printf("3ware device driver for 9000 series storage "
				"controllers, version: %s\n",
				TW_OSL_DRIVER_VERSION_STRING);
			first_ctlr = 0;
		}
		return(0);
	}
	return(ENXIO);
}