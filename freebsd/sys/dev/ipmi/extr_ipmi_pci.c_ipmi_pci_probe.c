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
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ ipmi_attached ; 
 char* ipmi_pci_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ipmi_pci_probe(device_t dev)
{
	const char *desc;

	if (ipmi_attached)
		return (ENXIO);

	desc = ipmi_pci_match(pci_get_vendor(dev), pci_get_device(dev));
	if (desc != NULL) {
		device_set_desc(dev, desc);
		return (BUS_PROBE_DEFAULT);
	}

	return (ENXIO);
}