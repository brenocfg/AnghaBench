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
struct pci_devinst {TYPE_1__* pi_bar; int /*<<< orphan*/  pi_name; } ;
struct mem_range {int arg2; struct pci_devinst* arg1; int /*<<< orphan*/  handler; int /*<<< orphan*/  flags; int /*<<< orphan*/  size; int /*<<< orphan*/  base; int /*<<< orphan*/  name; struct pci_devinst* arg; int /*<<< orphan*/  port; } ;
struct inout_port {int arg2; struct pci_devinst* arg1; int /*<<< orphan*/  handler; int /*<<< orphan*/  flags; int /*<<< orphan*/  size; int /*<<< orphan*/  base; int /*<<< orphan*/  name; struct pci_devinst* arg; int /*<<< orphan*/  port; } ;
struct TYPE_2__ {int type; int /*<<< orphan*/  size; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IOPORT_F_INOUT ; 
 int /*<<< orphan*/  MEM_F_RW ; 
#define  PCIBAR_IO 130 
#define  PCIBAR_MEM32 129 
#define  PCIBAR_MEM64 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bzero (struct mem_range*,int) ; 
 int /*<<< orphan*/  pci_emul_io_handler ; 
 int /*<<< orphan*/  pci_emul_mem_handler ; 
 int register_inout (struct mem_range*) ; 
 int register_mem (struct mem_range*) ; 
 int unregister_inout (struct mem_range*) ; 
 int unregister_mem (struct mem_range*) ; 

__attribute__((used)) static void
modify_bar_registration(struct pci_devinst *pi, int idx, int registration)
{
	int error;
	struct inout_port iop;
	struct mem_range mr;

	switch (pi->pi_bar[idx].type) {
	case PCIBAR_IO:
		bzero(&iop, sizeof(struct inout_port));
		iop.name = pi->pi_name;
		iop.port = pi->pi_bar[idx].addr;
		iop.size = pi->pi_bar[idx].size;
		if (registration) {
			iop.flags = IOPORT_F_INOUT;
			iop.handler = pci_emul_io_handler;
			iop.arg = pi;
			error = register_inout(&iop);
		} else
			error = unregister_inout(&iop);
		break;
	case PCIBAR_MEM32:
	case PCIBAR_MEM64:
		bzero(&mr, sizeof(struct mem_range));
		mr.name = pi->pi_name;
		mr.base = pi->pi_bar[idx].addr;
		mr.size = pi->pi_bar[idx].size;
		if (registration) {
			mr.flags = MEM_F_RW;
			mr.handler = pci_emul_mem_handler;
			mr.arg1 = pi;
			mr.arg2 = idx;
			error = register_mem(&mr);
		} else
			error = unregister_mem(&mr);
		break;
	default:
		error = EINVAL;
		break;
	}
	assert(error == 0);
}