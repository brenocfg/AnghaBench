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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct vmctx {int dummy; } ;
struct pci_devinst {TYPE_1__* pi_bar; struct pci_devemu* pi_d; } ;
struct pci_devemu {int /*<<< orphan*/  (* pe_barwrite ) (struct vmctx*,int,struct pci_devinst*,int,int,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* pe_barread ) (struct vmctx*,int,struct pci_devinst*,int,int,int) ;} ;
struct TYPE_2__ {scalar_t__ type; int addr; int size; } ;

/* Variables and functions */
 scalar_t__ PCIBAR_IO ; 
 int PCI_BARMAX ; 
 int /*<<< orphan*/  stub1 (struct vmctx*,int,struct pci_devinst*,int,int,int) ; 
 int /*<<< orphan*/  stub2 (struct vmctx*,int,struct pci_devinst*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pci_emul_io_handler(struct vmctx *ctx, int vcpu, int in, int port, int bytes,
		    uint32_t *eax, void *arg)
{
	struct pci_devinst *pdi = arg;
	struct pci_devemu *pe = pdi->pi_d;
	uint64_t offset;
	int i;

	for (i = 0; i <= PCI_BARMAX; i++) {
		if (pdi->pi_bar[i].type == PCIBAR_IO &&
		    port >= pdi->pi_bar[i].addr &&
		    port + bytes <= pdi->pi_bar[i].addr + pdi->pi_bar[i].size) {
			offset = port - pdi->pi_bar[i].addr;
			if (in)
				*eax = (*pe->pe_barread)(ctx, vcpu, pdi, i,
							 offset, bytes);
			else
				(*pe->pe_barwrite)(ctx, vcpu, pdi, i, offset,
						   bytes, *eax);
			return (0);
		}
	}
	return (-1);
}