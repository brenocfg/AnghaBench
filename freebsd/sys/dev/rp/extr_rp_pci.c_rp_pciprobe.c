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

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 int ENXIO ; 
 scalar_t__ RP_VENDOR_ID ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rp_pciprobe(device_t dev)
{
	char *s;

	s = NULL;
	if (pci_get_vendor(dev) == RP_VENDOR_ID)
		s = "RocketPort PCI";

	if (s != NULL) {
		device_set_desc(dev, s);
		return (BUS_PROBE_DEFAULT);
	}

	return (ENXIO);
}