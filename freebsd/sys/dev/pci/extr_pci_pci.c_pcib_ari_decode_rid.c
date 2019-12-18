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
typedef  int /*<<< orphan*/  uint16_t ;
struct pcib_softc {int flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIB_ENABLE_ARI ; 
 int PCIE_ARI_RID2FUNC (int /*<<< orphan*/ ) ; 
 int PCIE_ARI_RID2SLOT (int /*<<< orphan*/ ) ; 
 int PCI_RID2BUS (int /*<<< orphan*/ ) ; 
 int PCI_RID2FUNC (int /*<<< orphan*/ ) ; 
 int PCI_RID2SLOT (int /*<<< orphan*/ ) ; 
 struct pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pcib_ari_decode_rid(device_t pcib, uint16_t rid, int *bus, int *slot,
    int *func)
{
	struct pcib_softc *sc;

	sc = device_get_softc(pcib);

	*bus = PCI_RID2BUS(rid);
	if (sc->flags & PCIB_ENABLE_ARI) {
		*slot = PCIE_ARI_RID2SLOT(rid);
		*func = PCIE_ARI_RID2FUNC(rid);
	} else {
		*slot = PCI_RID2SLOT(rid);
		*func = PCI_RID2FUNC(rid);
	}
}