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
struct amdvi_softc {int /*<<< orphan*/  pci_rid; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_RID2BUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_RID2FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_RID2SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_cfgregread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline uint32_t
amdvi_pci_read(struct amdvi_softc *softc, int off)
{

	return (pci_cfgregread(PCI_RID2BUS(softc->pci_rid),
	    PCI_RID2SLOT(softc->pci_rid), PCI_RID2FUNC(softc->pci_rid),
	    off, 4));
}