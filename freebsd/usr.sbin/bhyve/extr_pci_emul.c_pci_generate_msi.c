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
struct TYPE_2__ {scalar_t__ msg_data; int /*<<< orphan*/  addr; } ;
struct pci_devinst {TYPE_1__ pi_msi; int /*<<< orphan*/  pi_vmctx; } ;

/* Variables and functions */
 scalar_t__ pci_msi_enabled (struct pci_devinst*) ; 
 int pci_msi_maxmsgnum (struct pci_devinst*) ; 
 int /*<<< orphan*/  vm_lapic_msi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void
pci_generate_msi(struct pci_devinst *pi, int index)
{

	if (pci_msi_enabled(pi) && index < pci_msi_maxmsgnum(pi)) {
		vm_lapic_msi(pi->pi_vmctx, pi->pi_msi.addr,
			     pi->pi_msi.msg_data + index);
	}
}