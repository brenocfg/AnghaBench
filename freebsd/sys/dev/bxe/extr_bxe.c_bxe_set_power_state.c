#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_2__ {int pcie_cap_flags; scalar_t__ pcie_pm_cap_reg; } ;
struct bxe_softc {TYPE_1__ devinfo; int /*<<< orphan*/  dev; int /*<<< orphan*/  wol; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,int,int) ; 
 int /*<<< orphan*/  BLOGW (struct bxe_softc*,char*) ; 
 int BXE_PM_CAPABLE_FLAG ; 
 int /*<<< orphan*/  CHIP_REV_IS_SLOW (struct bxe_softc*) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int PCIM_PSTAT_D3 ; 
 int PCIM_PSTAT_DMASK ; 
 int PCIM_PSTAT_PME ; 
 int PCIM_PSTAT_PMEENABLE ; 
 scalar_t__ PCIR_POWER_STATUS ; 
#define  PCI_PM_D0 129 
#define  PCI_PM_D3hot 128 
 int pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static int
bxe_set_power_state(struct bxe_softc *sc,
                    uint8_t          state)
{
    uint16_t pmcsr;

    /* If there is no power capability, silently succeed */
    if (!(sc->devinfo.pcie_cap_flags & BXE_PM_CAPABLE_FLAG)) {
        BLOGW(sc, "No power capability\n");
        return (0);
    }

    pmcsr = pci_read_config(sc->dev,
                            (sc->devinfo.pcie_pm_cap_reg + PCIR_POWER_STATUS),
                            2);

    switch (state) {
    case PCI_PM_D0:
        pci_write_config(sc->dev,
                         (sc->devinfo.pcie_pm_cap_reg + PCIR_POWER_STATUS),
                         ((pmcsr & ~PCIM_PSTAT_DMASK) | PCIM_PSTAT_PME), 2);

        if (pmcsr & PCIM_PSTAT_DMASK) {
            /* delay required during transition out of D3hot */
            DELAY(20000);
        }

        break;

    case PCI_PM_D3hot:
        /* XXX if there are other clients above don't shut down the power */

        /* don't shut down the power for emulation and FPGA */
        if (CHIP_REV_IS_SLOW(sc)) {
            return (0);
        }

        pmcsr &= ~PCIM_PSTAT_DMASK;
        pmcsr |= PCIM_PSTAT_D3;

        if (sc->wol) {
            pmcsr |= PCIM_PSTAT_PMEENABLE;
        }

        pci_write_config(sc->dev,
                         (sc->devinfo.pcie_pm_cap_reg + PCIR_POWER_STATUS),
                         pmcsr, 4);

        /*
         * No more memory access after this point until device is brought back
         * to D0 state.
         */
        break;

    default:
        BLOGE(sc, "Can't support PCI power state = 0x%x pmcsr 0x%x\n",
            state, pmcsr);
        return (-1);
    }

    return (0);
}