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
struct bxe_softc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int /*<<< orphan*/  PCIY_EXPRESS ; 
 scalar_t__ pci_find_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static uint32_t
bxe_pcie_capability_read(struct bxe_softc *sc,
                         int    reg,
                         int    width)
{
    int pcie_reg;

    /* ensure PCIe capability is enabled */
    if (pci_find_cap(sc->dev, PCIY_EXPRESS, &pcie_reg) == 0) {
        if (pcie_reg != 0) {
            BLOGD(sc, DBG_LOAD, "PCIe capability at 0x%04x\n", pcie_reg);
            return (pci_read_config(sc->dev, (pcie_reg + reg), width));
        }
    }

    BLOGE(sc, "PCIe capability NOT FOUND!!!\n");

    return (0);
}