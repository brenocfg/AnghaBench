#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ecore_ptt {int dummy; } ;
struct TYPE_3__ {int size; int /*<<< orphan*/  phys_addr; } ;
struct TYPE_4__ {TYPE_1__ pci_buf; } ;
struct dbg_tools_data {TYPE_2__ bus; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;
struct dbg_bus_mem_addr {void* hi; void* lo; } ;

/* Variables and functions */
 scalar_t__ BYTES_IN_DWORD ; 
 scalar_t__ DBG_REG_EXT_BUFFER_WR_PTR ; 
 scalar_t__ DBG_REG_WRAP_ON_EXT_BUFFER ; 
 int PCI_BUF_LINE_SIZE_IN_BYTES ; 
 int ecore_bus_dump_pci_buf_range (struct ecore_hwfn*,int*,int,int,int) ; 
 int ecore_phys_addr_diff (struct dbg_bus_mem_addr*,int /*<<< orphan*/ *) ; 
 void* ecore_rd (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__) ; 

__attribute__((used)) static u32 ecore_bus_dump_pci_buf(struct ecore_hwfn *p_hwfn,
								  struct ecore_ptt *p_ptt,
								  u32 *dump_buf,
								  bool dump)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	u32 next_wr_byte_offset, next_wr_line_offset;
	struct dbg_bus_mem_addr next_wr_phys_addr;
	u32 pci_buf_size_in_lines, offset = 0;

	pci_buf_size_in_lines = dev_data->bus.pci_buf.size / PCI_BUF_LINE_SIZE_IN_BYTES;

	/* Extract write pointer (physical address) */
	next_wr_phys_addr.lo = ecore_rd(p_hwfn, p_ptt, DBG_REG_EXT_BUFFER_WR_PTR);
	next_wr_phys_addr.hi = ecore_rd(p_hwfn, p_ptt, DBG_REG_EXT_BUFFER_WR_PTR + BYTES_IN_DWORD);

	/* Convert write pointer to offset */
	next_wr_byte_offset = ecore_phys_addr_diff(&next_wr_phys_addr, &dev_data->bus.pci_buf.phys_addr);
	if ((next_wr_byte_offset % PCI_BUF_LINE_SIZE_IN_BYTES) || next_wr_byte_offset > dev_data->bus.pci_buf.size)
		return 0;
	next_wr_line_offset = next_wr_byte_offset / PCI_BUF_LINE_SIZE_IN_BYTES;

	/* PCI buffer wrapped: first dump from write pointer to buffer end. */
	if (ecore_rd(p_hwfn, p_ptt, DBG_REG_WRAP_ON_EXT_BUFFER))
		offset += ecore_bus_dump_pci_buf_range(p_hwfn, dump_buf + offset, dump, next_wr_line_offset, pci_buf_size_in_lines - 1);

	/* Dump from buffer start until write pointer */
	if (next_wr_line_offset)
		offset += ecore_bus_dump_pci_buf_range(p_hwfn, dump_buf + offset, dump, 0, next_wr_line_offset - 1);

	return offset;
}