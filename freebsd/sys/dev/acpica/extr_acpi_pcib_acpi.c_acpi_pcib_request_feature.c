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
typedef  int /*<<< orphan*/  uint32_t ;
struct acpi_hpcib_softc {int dummy; } ;
typedef  enum pci_feature { ____Placeholder_pci_feature } pci_feature ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCIM_OSC_CTL_PCIE_AER ; 
 int /*<<< orphan*/  PCIM_OSC_CTL_PCIE_HP ; 
#define  PCI_FEATURE_AER 129 
#define  PCI_FEATURE_HP 128 
 int acpi_pcib_osc (struct acpi_hpcib_softc*,int /*<<< orphan*/ ) ; 
 struct acpi_hpcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_pcib_request_feature(device_t pcib, device_t dev, enum pci_feature feature)
{
	uint32_t osc_ctl;
	struct acpi_hpcib_softc *sc;

	sc = device_get_softc(pcib);

	switch (feature) {
	case PCI_FEATURE_HP:
		osc_ctl = PCIM_OSC_CTL_PCIE_HP;
		break;
	case PCI_FEATURE_AER:
		osc_ctl = PCIM_OSC_CTL_PCIE_AER;
		break;
	default:
		return (EINVAL);
	}

	return (acpi_pcib_osc(sc, osc_ctl));
}