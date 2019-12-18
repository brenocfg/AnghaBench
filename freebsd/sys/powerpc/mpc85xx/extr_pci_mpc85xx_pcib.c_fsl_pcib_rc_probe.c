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
 scalar_t__ PCIC_PROCESSOR ; 
 scalar_t__ PCIS_PROCESSOR_POWERPC ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_progif (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subclass (int /*<<< orphan*/ ) ; 
 int pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fsl_pcib_rc_probe(device_t dev)
{

	if (pci_get_vendor(dev) != 0x1957)
		return (ENXIO);
	if (pci_get_progif(dev) != 0)
		return (ENXIO);
	if (pci_get_class(dev) != PCIC_PROCESSOR)
		return (ENXIO);
	if (pci_get_subclass(dev) != PCIS_PROCESSOR_POWERPC)
		return (ENXIO);

	device_set_desc(dev, "MPC85xx Root Complex bridge");

	return (BUS_PROBE_DEFAULT);
}