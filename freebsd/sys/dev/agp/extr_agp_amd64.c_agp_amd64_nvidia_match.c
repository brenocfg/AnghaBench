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
typedef  int uint16_t ;

/* Variables and functions */
 int ENXIO ; 
 int PCIC_BRIDGE ; 
 int /*<<< orphan*/  PCIR_CLASS ; 
 int /*<<< orphan*/  PCIR_DEVICE ; 
 int /*<<< orphan*/  PCIR_SUBCLASS ; 
 int /*<<< orphan*/  PCIR_VENDOR ; 
 int PCIS_BRIDGE_PCI ; 
 int pci_cfgregread (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
agp_amd64_nvidia_match(uint16_t devid)
{
	/* XXX nForce3 requires secondary AGP bridge at 0:11:0. */
	if (pci_cfgregread(0, 11, 0, PCIR_CLASS, 1) != PCIC_BRIDGE ||
	    pci_cfgregread(0, 11, 0, PCIR_SUBCLASS, 1) != PCIS_BRIDGE_PCI ||
	    pci_cfgregread(0, 11, 0, PCIR_VENDOR, 2) != 0x10de ||
	    pci_cfgregread(0, 11, 0, PCIR_DEVICE, 2) != devid)
		return (ENXIO);

	return (0);
}