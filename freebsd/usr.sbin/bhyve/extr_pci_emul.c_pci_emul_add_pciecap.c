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
typedef  int /*<<< orphan*/  u_char ;
struct pciecap {int pcie_capabilities; int link_capabilities; int link_status; int /*<<< orphan*/  capid; } ;
struct pci_devinst {scalar_t__ pi_bus; } ;
typedef  int /*<<< orphan*/  pciecap ;

/* Variables and functions */
 int PCIECAP_VERSION ; 
 int PCIEM_TYPE_ENDPOINT ; 
 int PCIEM_TYPE_ROOT_INT_EP ; 
 int /*<<< orphan*/  PCIY_EXPRESS ; 
 int /*<<< orphan*/  bzero (struct pciecap*,int) ; 
 int pci_emul_add_capability (struct pci_devinst*,int /*<<< orphan*/ *,int) ; 

int
pci_emul_add_pciecap(struct pci_devinst *pi, int type)
{
	int err;
	struct pciecap pciecap;

	bzero(&pciecap, sizeof(pciecap));

	/*
	 * Use the integrated endpoint type for endpoints on a root complex bus.
	 *
	 * NB: bhyve currently only supports a single PCI bus that is the root
	 * complex bus, so all endpoints are integrated.
	 */
	if ((type == PCIEM_TYPE_ENDPOINT) && (pi->pi_bus == 0))
		type = PCIEM_TYPE_ROOT_INT_EP;

	pciecap.capid = PCIY_EXPRESS;
	pciecap.pcie_capabilities = PCIECAP_VERSION | type;
	if (type != PCIEM_TYPE_ROOT_INT_EP) {
		pciecap.link_capabilities = 0x411;	/* gen1, x1 */
		pciecap.link_status = 0x11;		/* gen1, x1 */
	}

	err = pci_emul_add_capability(pi, (u_char *)&pciecap, sizeof(pciecap));
	return (err);
}