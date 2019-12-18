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
struct bge_softc {int /*<<< orphan*/  bge_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BGE_PCI_REG_BASEADDR ; 
 int /*<<< orphan*/  BGE_PCI_REG_DATA ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
bge_writereg_ind(struct bge_softc *sc, int off, int val)
{
	device_t dev;

	dev = sc->bge_dev;

	pci_write_config(dev, BGE_PCI_REG_BASEADDR, off, 4);
	pci_write_config(dev, BGE_PCI_REG_DATA, val, 4);
}