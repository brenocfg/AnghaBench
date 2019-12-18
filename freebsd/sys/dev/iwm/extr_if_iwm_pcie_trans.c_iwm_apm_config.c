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
struct iwm_softc {int sc_ltr_enabled; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  lctl ;
typedef  int /*<<< orphan*/  cap ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_CLRBITS (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWM_CSR_GIO_REG ; 
 int /*<<< orphan*/  IWM_CSR_GIO_REG_VAL_L0S_ENABLED ; 
 int IWM_DEBUG_PWRSAVE ; 
 int IWM_DEBUG_RESET ; 
 int /*<<< orphan*/  IWM_DPRINTF (struct iwm_softc*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  IWM_SETBITS (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PCIEM_CTL2_LTR_ENABLE ; 
 int PCIEM_LINK_CTL_ASPMC_L1 ; 
 scalar_t__ PCIER_DEVICE_CTL2 ; 
 scalar_t__ PCIER_LINK_CTL ; 
 int /*<<< orphan*/  PCIY_EXPRESS ; 
 int pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 

void
iwm_apm_config(struct iwm_softc *sc)
{
	uint16_t lctl, cap;
	int pcie_ptr;

	/*
	 * HW bug W/A for instability in PCIe bus L0S->L1 transition.
	 * Check if BIOS (or OS) enabled L1-ASPM on this device.
	 * If so (likely), disable L0S, so device moves directly L0->L1;
	 *    costs negligible amount of power savings.
	 * If not (unlikely), enable L0S, so there is at least some
	 *    power savings, even without L1.
	 */
	int error;

	error = pci_find_cap(sc->sc_dev, PCIY_EXPRESS, &pcie_ptr);
	if (error != 0)
		return;
	lctl = pci_read_config(sc->sc_dev, pcie_ptr + PCIER_LINK_CTL,
	    sizeof(lctl));
	if (lctl & PCIEM_LINK_CTL_ASPMC_L1)  {
		IWM_SETBITS(sc, IWM_CSR_GIO_REG,
		    IWM_CSR_GIO_REG_VAL_L0S_ENABLED);
	} else {
		IWM_CLRBITS(sc, IWM_CSR_GIO_REG,
		    IWM_CSR_GIO_REG_VAL_L0S_ENABLED);
	}

	cap = pci_read_config(sc->sc_dev, pcie_ptr + PCIER_DEVICE_CTL2,
	    sizeof(cap));
	sc->sc_ltr_enabled = (cap & PCIEM_CTL2_LTR_ENABLE) ? 1 : 0;
	IWM_DPRINTF(sc, IWM_DEBUG_RESET | IWM_DEBUG_PWRSAVE,
	    "L1 %sabled - LTR %sabled\n",
	    (lctl & PCIEM_LINK_CTL_ASPMC_L1) ? "En" : "Dis",
	    sc->sc_ltr_enabled ? "En" : "Dis");
}