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
typedef  scalar_t__ u32 ;
struct ecore_ptt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct dbg_bus_data {int target; TYPE_1__ pci_buf; } ;
struct dbg_tools_data {struct dbg_bus_data bus; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;

/* Variables and functions */
 int /*<<< orphan*/  BYTES_TO_DWORDS (int /*<<< orphan*/ ) ; 
#define  DBG_BUS_TARGET_ID_INT_BUF 129 
#define  DBG_BUS_TARGET_ID_PCI 128 
 int DBG_STATUS_OK ; 
 int /*<<< orphan*/  INT_BUF_SIZE_IN_DWORDS ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 scalar_t__ ecore_bus_dump_hdr (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int) ; 
 int ecore_dbg_dev_init (struct ecore_hwfn*,struct ecore_ptt*) ; 
 scalar_t__ ecore_dump_last_section (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

enum dbg_status ecore_dbg_bus_get_dump_buf_size(struct ecore_hwfn *p_hwfn,
												struct ecore_ptt *p_ptt,
												u32 *buf_size)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	struct dbg_bus_data *bus = &dev_data->bus;
	enum dbg_status status;

	status = ecore_dbg_dev_init(p_hwfn, p_ptt);

	*buf_size = 0;

	if (status != DBG_STATUS_OK)
		return status;

	/* Add dump header */
	*buf_size = (u32)ecore_bus_dump_hdr(p_hwfn, p_ptt, OSAL_NULL, false);

	switch (bus->target) {
	case DBG_BUS_TARGET_ID_INT_BUF:
		*buf_size += INT_BUF_SIZE_IN_DWORDS; break;
	case DBG_BUS_TARGET_ID_PCI:
		*buf_size += BYTES_TO_DWORDS(bus->pci_buf.size); break;
	default:
		break;
	}

	/* Dump last section */
	*buf_size += ecore_dump_last_section(OSAL_NULL, 0, false);

	return DBG_STATUS_OK;
}