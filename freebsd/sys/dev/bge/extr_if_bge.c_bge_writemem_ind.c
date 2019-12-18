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
struct bge_softc {scalar_t__ bge_asicrev; int /*<<< orphan*/  bge_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ BGE_ASICREV_BCM5906 ; 
 int /*<<< orphan*/  BGE_PCI_MEMWIN_BASEADDR ; 
 int /*<<< orphan*/  BGE_PCI_MEMWIN_DATA ; 
 int BGE_SEND_RING_1_TO_4 ; 
 int BGE_STATS_BLOCK ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
bge_writemem_ind(struct bge_softc *sc, int off, int val)
{
	device_t dev;

	if (sc->bge_asicrev == BGE_ASICREV_BCM5906 &&
	    off >= BGE_STATS_BLOCK && off < BGE_SEND_RING_1_TO_4)
		return;

	dev = sc->bge_dev;

	pci_write_config(dev, BGE_PCI_MEMWIN_BASEADDR, off, 4);
	pci_write_config(dev, BGE_PCI_MEMWIN_DATA, val, 4);
	pci_write_config(dev, BGE_PCI_MEMWIN_BASEADDR, 0, 4);
}