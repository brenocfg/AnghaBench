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
typedef  int /*<<< orphan*/  uint16_t ;
struct bhnd_pcihb_softc {int quirks; int /*<<< orphan*/  pci_dev; } ;
typedef  scalar_t__ bhnd_pci_war_state ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_PCIE_ASPMTIMER_EXTEND ; 
 int /*<<< orphan*/  BHND_PCIE_DLLP_PMTHRESHREG ; 
 int BHND_PCIE_QUIRK_ASPM_OVR ; 
 int BHND_PCIE_QUIRK_L1_TIMER_PERF ; 
 int /*<<< orphan*/  BHND_PCI_PROTO_READ_4 (struct bhnd_pcihb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_PCI_PROTO_WRITE_4 (struct bhnd_pcihb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BHND_PCI_WAR_SUSPEND ; 
 int /*<<< orphan*/  PCIEM_LINK_CTL_ASPMC_L1 ; 
 int /*<<< orphan*/  PCIEM_LINK_CTL_ECPM ; 
 int /*<<< orphan*/  PCIER_LINK_CTL ; 
 int /*<<< orphan*/  pcie_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcie_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bhnd_pci_wars_hwdown(struct bhnd_pcihb_softc *sc, bhnd_pci_war_state state)
{
	/* Reduce L1 timer for better power savings.
	 * TODO: We could enable/disable this on demand for better power
	 * savings if we tie this to HT clock request handling */
	if (sc->quirks & BHND_PCIE_QUIRK_L1_TIMER_PERF) {
		uint32_t pmt;
		pmt = BHND_PCI_PROTO_READ_4(sc, BHND_PCIE_DLLP_PMTHRESHREG);
		pmt &= ~BHND_PCIE_ASPMTIMER_EXTEND;
		BHND_PCI_PROTO_WRITE_4(sc, BHND_PCIE_DLLP_PMTHRESHREG, pmt);
	}

	/* Enable CLKREQ (ECPM). If suspending, also disable ASPM L1 entry */
	if (sc->quirks & BHND_PCIE_QUIRK_ASPM_OVR) {
		uint16_t	lcreg;

		lcreg = pcie_read_config(sc->pci_dev, PCIER_LINK_CTL, 2);

		lcreg |= PCIEM_LINK_CTL_ECPM;	/* CLKREQ# */
		if (state == BHND_PCI_WAR_SUSPEND)
			lcreg &= ~PCIEM_LINK_CTL_ASPMC_L1;

		pcie_write_config(sc->pci_dev, PCIER_LINK_CTL, lcreg, 2);
	}

	return (0);
}