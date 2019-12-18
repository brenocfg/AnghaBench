#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  lo; } ;
struct TYPE_5__ {scalar_t__ size; int /*<<< orphan*/  phys_addr; TYPE_1__ virt_addr; } ;
struct TYPE_6__ {TYPE_2__ pci_buf; } ;
struct dbg_tools_data {TYPE_3__ bus; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; struct dbg_tools_data dbg_info; } ;
typedef  int /*<<< orphan*/  pci_buf_phys_addr ;
typedef  scalar_t__ osal_uintptr_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_DMA_FREE_COHERENT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  OSAL_MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ecore_bus_free_pci_buf(struct ecore_hwfn *p_hwfn)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	dma_addr_t pci_buf_phys_addr;
	void *virt_addr_lo;
	u32 *pci_buf;

	/* Extract PCI buffer pointer from virtual address */
	virt_addr_lo = &dev_data->bus.pci_buf.virt_addr.lo;
	pci_buf = (u32 *)(osal_uintptr_t)*((u64 *)virt_addr_lo);

	if (!dev_data->bus.pci_buf.size)
		return;

	OSAL_MEMCPY(&pci_buf_phys_addr, &dev_data->bus.pci_buf.phys_addr, sizeof(pci_buf_phys_addr));

	OSAL_DMA_FREE_COHERENT(p_hwfn->p_dev, pci_buf, pci_buf_phys_addr, dev_data->bus.pci_buf.size);

	dev_data->bus.pci_buf.size = 0;
}