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
struct pcib_softc {void* pmemlimit; void* pmembase; void* memlimit; void* membase; int /*<<< orphan*/  dev; } ;
typedef  int pci_addr_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIM_BRPM_64 ; 
 int PCIM_BRPM_MASK ; 
 int /*<<< orphan*/  PCIR_MEMBASE_1 ; 
 int /*<<< orphan*/  PCIR_MEMLIMIT_1 ; 
 int /*<<< orphan*/  PCIR_PMBASEH_1 ; 
 int /*<<< orphan*/  PCIR_PMBASEL_1 ; 
 int /*<<< orphan*/  PCIR_PMLIMITH_1 ; 
 int /*<<< orphan*/  PCIR_PMLIMITL_1 ; 
 void* PCI_PPBMEMBASE (int,int) ; 
 void* PCI_PPBMEMLIMIT (int,int) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pcib_get_mem_decode(struct pcib_softc *sc)
{
	device_t	dev;
	pci_addr_t	pmemlow;

	dev = sc->dev;

	sc->membase = PCI_PPBMEMBASE(0,
	    pci_read_config(dev, PCIR_MEMBASE_1, 2));
	sc->memlimit = PCI_PPBMEMLIMIT(0,
	    pci_read_config(dev, PCIR_MEMLIMIT_1, 2));

	pmemlow = pci_read_config(dev, PCIR_PMBASEL_1, 2);
	if ((pmemlow & PCIM_BRPM_MASK) == PCIM_BRPM_64)
		sc->pmembase = PCI_PPBMEMBASE(
		    pci_read_config(dev, PCIR_PMBASEH_1, 4), pmemlow);
	else
		sc->pmembase = PCI_PPBMEMBASE(0, pmemlow);

	pmemlow = pci_read_config(dev, PCIR_PMLIMITL_1, 2);
	if ((pmemlow & PCIM_BRPM_MASK) == PCIM_BRPM_64)
		sc->pmemlimit = PCI_PPBMEMLIMIT(
		    pci_read_config(dev, PCIR_PMLIMITH_1, 4), pmemlow);
	else
		sc->pmemlimit = PCI_PPBMEMLIMIT(0, pmemlow);
}