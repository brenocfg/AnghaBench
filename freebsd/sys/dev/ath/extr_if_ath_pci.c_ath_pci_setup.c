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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int DEFAULT_CACHESIZE ; 
 int /*<<< orphan*/  PCIR_CACHELNSZ ; 
 int /*<<< orphan*/  PCIR_CFG_PMCSR ; 
 int /*<<< orphan*/  PCIR_LATTIMER ; 
 int /*<<< orphan*/  PCIR_RETRY_TIMEOUT ; 
 void* pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
ath_pci_setup(device_t dev)
{
	uint8_t cz;

	/* XXX TODO: need to override the _system_ saved copies of this */

	/*
	 * If the cache line size is 0, force it to a reasonable
	 * value.
	 */
	cz = pci_read_config(dev, PCIR_CACHELNSZ, 1);
	if (cz == 0) {
		pci_write_config(dev, PCIR_CACHELNSZ,
		    DEFAULT_CACHESIZE / 4, 1);
	}

	/* Override the system latency timer */
	pci_write_config(dev, PCIR_LATTIMER, 0xa8, 1);

	/* If a PCI NIC, force wakeup */
#ifdef	ATH_PCI_WAKEUP_WAR
	/* XXX TODO: don't do this for non-PCI (ie, PCIe, Cardbus!) */
	if (1) {
		uint16_t pmcsr;
		pmcsr = pci_read_config(dev, PCIR_CFG_PMCSR, 2);
		pmcsr |= 3;
		pci_write_config(dev, PCIR_CFG_PMCSR, pmcsr, 2);
		pmcsr &= ~3;
		pci_write_config(dev, PCIR_CFG_PMCSR, pmcsr, 2);
	}
#endif

	/*
	 * Disable retry timeout to keep PCI Tx retries from
	 * interfering with C3 CPU state.
	 */
	pci_write_config(dev, PCIR_RETRY_TIMEOUT, 0, 1);
}