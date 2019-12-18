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
typedef  int uint32_t ;
struct pcib_softc {void* iolimit; void* iobase; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIM_BRIO_32 ; 
 int PCIM_BRIO_MASK ; 
 int /*<<< orphan*/  PCIR_IOBASEH_1 ; 
 int /*<<< orphan*/  PCIR_IOBASEL_1 ; 
 int /*<<< orphan*/  PCIR_IOLIMITH_1 ; 
 int /*<<< orphan*/  PCIR_IOLIMITL_1 ; 
 void* PCI_PPBIOBASE (int,int) ; 
 void* PCI_PPBIOLIMIT (int,int) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pcib_get_io_decode(struct pcib_softc *sc)
{
	device_t	dev;
	uint32_t	iolow;

	dev = sc->dev;

	iolow = pci_read_config(dev, PCIR_IOBASEL_1, 1);
	if ((iolow & PCIM_BRIO_MASK) == PCIM_BRIO_32)
		sc->iobase = PCI_PPBIOBASE(
		    pci_read_config(dev, PCIR_IOBASEH_1, 2), iolow);
	else
		sc->iobase = PCI_PPBIOBASE(0, iolow);

	iolow = pci_read_config(dev, PCIR_IOLIMITL_1, 1);
	if ((iolow & PCIM_BRIO_MASK) == PCIM_BRIO_32)
		sc->iolimit = PCI_PPBIOLIMIT(
		    pci_read_config(dev, PCIR_IOLIMITH_1, 2), iolow);
	else
		sc->iolimit = PCI_PPBIOLIMIT(0, iolow);
}