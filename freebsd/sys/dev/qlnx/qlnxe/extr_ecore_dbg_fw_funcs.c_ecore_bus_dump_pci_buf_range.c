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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  lo; } ;
struct TYPE_5__ {TYPE_1__ virt_addr; } ;
struct TYPE_6__ {TYPE_2__ pci_buf; } ;
struct dbg_tools_data {TYPE_3__ bus; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;
typedef  scalar_t__ osal_uintptr_t ;

/* Variables and functions */
 int PCI_BUF_LINE_SIZE_IN_DWORDS ; 
 int* s_pci_buf_line_ind ; 

__attribute__((used)) static u32 ecore_bus_dump_pci_buf_range(struct ecore_hwfn *p_hwfn,
										u32 *dump_buf,
										bool dump,
										u32 start_line,
										u32 end_line)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u32 offset = 0;

	/* Extract PCI buffer pointer from virtual address */
	void *virt_addr_lo = &dev_data->bus.pci_buf.virt_addr.lo;
	u32 *pci_buf_start = (u32 *)(osal_uintptr_t)*((u64 *)virt_addr_lo);
	u32 *pci_buf, line, i;

	if (!dump)
		return (end_line - start_line + 1) * PCI_BUF_LINE_SIZE_IN_DWORDS;

	for (line = start_line, pci_buf = pci_buf_start + start_line * PCI_BUF_LINE_SIZE_IN_DWORDS;
	line <= end_line;
		line++, offset += PCI_BUF_LINE_SIZE_IN_DWORDS)
		for (i = 0; i < PCI_BUF_LINE_SIZE_IN_DWORDS; i++, pci_buf++)
			dump_buf[offset + s_pci_buf_line_ind[i]] = *pci_buf;

	return offset;
}