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
typedef  scalar_t__ uint32_t ;
struct pcib_softc {int /*<<< orphan*/  flags; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIB_ENABLE_ARI ; 
 scalar_t__ PCIEM_CTL2_ARI ; 
 scalar_t__ PCIER_DEVICE_CTL2 ; 
 scalar_t__ pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static void
pcib_enable_ari(struct pcib_softc *sc, uint32_t pcie_pos)
{
	uint32_t ctl2;

	ctl2 = pci_read_config(sc->dev, pcie_pos + PCIER_DEVICE_CTL2, 4);
	ctl2 |= PCIEM_CTL2_ARI;
	pci_write_config(sc->dev, pcie_pos + PCIER_DEVICE_CTL2, ctl2, 4);

	sc->flags |= PCIB_ENABLE_ARI;
}