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
typedef  int /*<<< orphan*/  u32 ;
struct ecore_ptt {int dummy; } ;
struct TYPE_2__ {int target; } ;
struct dbg_tools_data {TYPE_1__ bus; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;

/* Variables and functions */
#define  DBG_BUS_TARGET_ID_INT_BUF 129 
#define  DBG_BUS_TARGET_ID_PCI 128 
 int /*<<< orphan*/  ecore_bus_dump_int_buf (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ecore_bus_dump_pci_buf (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static u32 ecore_bus_dump_data(struct ecore_hwfn *p_hwfn,
							   struct ecore_ptt *p_ptt,
							   u32 *dump_buf,
							   bool dump)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;

	switch (dev_data->bus.target) {
	case DBG_BUS_TARGET_ID_INT_BUF:
		return ecore_bus_dump_int_buf(p_hwfn, p_ptt, dump_buf, dump);
	case DBG_BUS_TARGET_ID_PCI:
		return ecore_bus_dump_pci_buf(p_hwfn, p_ptt, dump_buf, dump);
	default:
		break;
	}

	return 0;
}