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
typedef  scalar_t__* vulp ;
struct pci_controller {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ LCA_IOC_TBIA ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  wmb () ; 

void
lca_pci_tbi(struct pci_controller *hose, dma_addr_t start, dma_addr_t end)
{
	wmb();
	*(vulp)LCA_IOC_TBIA = 0;
	mb();
}