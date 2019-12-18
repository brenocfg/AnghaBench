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
#define  NVIDIA_DEVICEID_NFORCE 129 
#define  NVIDIA_DEVICEID_NFORCE2 128 
 scalar_t__ NVIDIA_VENDORID ; 
 scalar_t__ PCIC_BRIDGE ; 
 scalar_t__ PCIS_BRIDGE_HOST ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 int pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
agp_nvidia_match (device_t dev)
{
	if (pci_get_class(dev) != PCIC_BRIDGE ||
	    pci_get_subclass(dev) != PCIS_BRIDGE_HOST ||
	    pci_get_vendor(dev) != NVIDIA_VENDORID)
		return (NULL);

	switch (pci_get_device(dev)) {
	case NVIDIA_DEVICEID_NFORCE:
		return ("NVIDIA nForce AGP Controller");
	case NVIDIA_DEVICEID_NFORCE2:
		return ("NVIDIA nForce2 AGP Controller");
	}
	return (NULL);
}