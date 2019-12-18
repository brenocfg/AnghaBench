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
typedef  int uint16_t ;
struct pci_devinst {TYPE_1__* pi_bar; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  PCIBAR_IO 132 
#define  PCIBAR_MEM32 131 
#define  PCIBAR_MEM64 130 
#define  PCIBAR_MEMHI64 129 
#define  PCIBAR_NONE 128 
 int PCIM_CMD_MEMEN ; 
 int PCIM_CMD_PORTEN ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int PCI_BARMAX ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int pci_get_cfgdata16 (struct pci_devinst*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_lintr_update (struct pci_devinst*) ; 
 int /*<<< orphan*/  register_bar (struct pci_devinst*,int) ; 
 int /*<<< orphan*/  unregister_bar (struct pci_devinst*,int) ; 

void
pci_emul_cmd_changed(struct pci_devinst *pi, uint16_t old)
{
	int i;
	uint16_t changed, new;

	new = pci_get_cfgdata16(pi, PCIR_COMMAND);
	changed = old ^ new;

	/*
	 * If the MMIO or I/O address space decoding has changed then
	 * register/unregister all BARs that decode that address space.
	 */
	for (i = 0; i <= PCI_BARMAX; i++) {
		switch (pi->pi_bar[i].type) {
			case PCIBAR_NONE:
			case PCIBAR_MEMHI64:
				break;
			case PCIBAR_IO:
				/* I/O address space decoding changed? */
				if (changed & PCIM_CMD_PORTEN) {
					if (new & PCIM_CMD_PORTEN)
						register_bar(pi, i);
					else
						unregister_bar(pi, i);
				}
				break;
			case PCIBAR_MEM32:
			case PCIBAR_MEM64:
				/* MMIO address space decoding changed? */
				if (changed & PCIM_CMD_MEMEN) {
					if (new & PCIM_CMD_MEMEN)
						register_bar(pi, i);
					else
						unregister_bar(pi, i);
				}
				break;
			default:
				assert(0);
		}
	}

	/*
	 * If INTx has been unmasked and is pending, assert the
	 * interrupt.
	 */
	pci_lintr_update(pi);
}