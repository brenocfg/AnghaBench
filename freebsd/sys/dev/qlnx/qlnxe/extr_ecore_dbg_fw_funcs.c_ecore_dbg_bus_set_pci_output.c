#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  void* u32 ;
typedef  int u16 ;
struct ecore_ptt {int dummy; } ;
struct TYPE_8__ {int lo; int hi; } ;
struct TYPE_5__ {void* hi; void* lo; } ;
struct TYPE_6__ {int size; TYPE_4__ phys_addr; TYPE_1__ virt_addr; } ;
struct TYPE_7__ {scalar_t__ target; scalar_t__ state; TYPE_2__ pci_buf; } ;
struct dbg_tools_data {TYPE_3__ bus; } ;
struct ecore_hwfn {int /*<<< orphan*/  rel_pf_id; int /*<<< orphan*/  p_dev; struct dbg_tools_data dbg_info; } ;
typedef  int /*<<< orphan*/  pci_buf_phys_addr ;
typedef  scalar_t__ osal_uintptr_t ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ DBG_BUS_STATE_READY ; 
 scalar_t__ DBG_BUS_TARGET_ID_INT_BUF ; 
 int DBG_BUS_TARGET_ID_PCI ; 
 int /*<<< orphan*/  DBG_REG_DEBUG_TARGET ; 
 int /*<<< orphan*/  DBG_REG_OUTPUT_ENABLE ; 
 int /*<<< orphan*/  DBG_REG_PCI_EXT_BUFFER_SIZE ; 
 int /*<<< orphan*/  DBG_REG_PCI_EXT_BUFFER_STRT_ADDR_LSB ; 
 int /*<<< orphan*/  DBG_REG_PCI_EXT_BUFFER_STRT_ADDR_MSB ; 
 int /*<<< orphan*/  DBG_REG_PCI_FUNC_NUM ; 
 int /*<<< orphan*/  DBG_REG_PCI_LOGIC_ADDR ; 
 int /*<<< orphan*/  DBG_REG_PCI_REQ_CREDIT ; 
 int /*<<< orphan*/  DBG_REG_TARGET_PACKET_SIZE ; 
 int DBG_STATUS_DBG_BLOCK_NOT_RESET ; 
 int DBG_STATUS_INVALID_ARGS ; 
 int DBG_STATUS_OK ; 
 int DBG_STATUS_OUTPUT_ALREADY_SET ; 
 int DBG_STATUS_PCI_BUF_ALLOC_FAILED ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ECORE_MSG_DEBUG ; 
 int OPAQUE_FID (int /*<<< orphan*/ ) ; 
 void* OSAL_DMA_ALLOC_COHERENT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OSAL_MEMCPY (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 int PCI_PHYS_ADDR_TYPE ; 
 int PCI_PKT_SIZE_IN_BYTES ; 
 int PCI_PKT_SIZE_IN_CHUNKS ; 
 int PCI_REQ_CREDIT ; 
 int TARGET_EN_MASK_PCI ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 

enum dbg_status ecore_dbg_bus_set_pci_output(struct ecore_hwfn *p_hwfn,
											 struct ecore_ptt *p_ptt,
											 u16 buf_size_kb)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	dma_addr_t pci_buf_phys_addr;
	void *pci_buf;

	DP_VERBOSE(p_hwfn, ECORE_MSG_DEBUG, "dbg_bus_set_pci_output: buf_size_kb = %d\n", buf_size_kb);

	if (dev_data->bus.target != DBG_BUS_TARGET_ID_INT_BUF)
		return DBG_STATUS_OUTPUT_ALREADY_SET;
	if (dev_data->bus.state != DBG_BUS_STATE_READY || dev_data->bus.pci_buf.size > 0)
		return DBG_STATUS_DBG_BLOCK_NOT_RESET;

	dev_data->bus.target = DBG_BUS_TARGET_ID_PCI;
	dev_data->bus.pci_buf.size = buf_size_kb * 1024;
	if (dev_data->bus.pci_buf.size % PCI_PKT_SIZE_IN_BYTES)
		return DBG_STATUS_INVALID_ARGS;

	pci_buf = OSAL_DMA_ALLOC_COHERENT(p_hwfn->p_dev, &pci_buf_phys_addr, dev_data->bus.pci_buf.size);
	if (!pci_buf)
		return DBG_STATUS_PCI_BUF_ALLOC_FAILED;

	OSAL_MEMCPY(&dev_data->bus.pci_buf.phys_addr, &pci_buf_phys_addr, sizeof(pci_buf_phys_addr));

	dev_data->bus.pci_buf.virt_addr.lo = (u32)((u64)(osal_uintptr_t)pci_buf);
	dev_data->bus.pci_buf.virt_addr.hi = (u32)((u64)(osal_uintptr_t)pci_buf >> 32);

	ecore_wr(p_hwfn, p_ptt, DBG_REG_PCI_EXT_BUFFER_STRT_ADDR_LSB, dev_data->bus.pci_buf.phys_addr.lo);
	ecore_wr(p_hwfn, p_ptt, DBG_REG_PCI_EXT_BUFFER_STRT_ADDR_MSB, dev_data->bus.pci_buf.phys_addr.hi);
	ecore_wr(p_hwfn, p_ptt, DBG_REG_TARGET_PACKET_SIZE, PCI_PKT_SIZE_IN_CHUNKS);
	ecore_wr(p_hwfn, p_ptt, DBG_REG_PCI_EXT_BUFFER_SIZE, dev_data->bus.pci_buf.size / PCI_PKT_SIZE_IN_BYTES);
	ecore_wr(p_hwfn, p_ptt, DBG_REG_PCI_FUNC_NUM, OPAQUE_FID(p_hwfn->rel_pf_id));
	ecore_wr(p_hwfn, p_ptt, DBG_REG_PCI_LOGIC_ADDR, PCI_PHYS_ADDR_TYPE);
	ecore_wr(p_hwfn, p_ptt, DBG_REG_PCI_REQ_CREDIT, PCI_REQ_CREDIT);
	ecore_wr(p_hwfn, p_ptt, DBG_REG_DEBUG_TARGET, DBG_BUS_TARGET_ID_PCI);
	ecore_wr(p_hwfn, p_ptt, DBG_REG_OUTPUT_ENABLE, TARGET_EN_MASK_PCI);

	return DBG_STATUS_OK;
}