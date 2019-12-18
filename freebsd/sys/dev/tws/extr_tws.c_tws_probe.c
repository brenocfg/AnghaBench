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
typedef  int u_int8_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 scalar_t__ TWS_DEVICE_ID ; 
 char* TWS_DRIVER_VERSION_STRING ; 
 scalar_t__ TWS_VENDOR_ID ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int
tws_probe(device_t dev)
{
    static u_int8_t first_ctlr = 1;

    if ((pci_get_vendor(dev) == TWS_VENDOR_ID) &&
        (pci_get_device(dev) == TWS_DEVICE_ID)) {
        device_set_desc(dev, "LSI 3ware SAS/SATA Storage Controller");
        if (first_ctlr) {
            printf("LSI 3ware device driver for SAS/SATA storage "
                    "controllers, version: %s\n", TWS_DRIVER_VERSION_STRING);
            first_ctlr = 0;
        }

        return(BUS_PROBE_DEFAULT);
    }
    return (ENXIO);
}