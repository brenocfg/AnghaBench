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
typedef  int u8 ;
struct ecore_ptt {int dummy; } ;
struct dbg_bus_data {int next_trigger_state; int hw_id_mask; TYPE_2__* blocks; TYPE_1__* trigger_states; scalar_t__ trigger_en; } ;
struct dbg_tools_data {scalar_t__ chip_id; struct dbg_bus_data bus; } ;
struct ecore_hwfn {struct dbg_tools_data dbg_info; } ;
struct TYPE_4__ {int data; } ;
struct TYPE_3__ {int data; } ;

/* Variables and functions */
 size_t BLOCK_PCIE ; 
 size_t BLOCK_PHY_PCIE ; 
 int BYTES_IN_DWORD ; 
 scalar_t__ CHIP_K2 ; 
 int /*<<< orphan*/  DBG_BUS_BLOCK_DATA_ENABLE_MASK ; 
 int /*<<< orphan*/  DBG_BUS_TRIGGER_STATE_DATA_CONSTRAINT_DWORD_MASK ; 
 scalar_t__ DBG_REG_HW_ID_NUM ; 
 scalar_t__ DBG_REG_TRIGGER_STATE_ID_0 ; 
 int GET_FIELD (int,int /*<<< orphan*/ ) ; 
 int HW_ID_BITS ; 
 scalar_t__ PCIE_REG_DBG_FW_TRIGGER_ENABLE_K2_E5 ; 
 scalar_t__ PCIE_REG_DBG_REPEAT_THRESHOLD_COUNT_K2_E5 ; 
 int VALUES_PER_CYCLE ; 
 int /*<<< orphan*/  ecore_assign_hw_ids (struct ecore_hwfn*,int*) ; 
 int /*<<< orphan*/  ecore_wr (struct ecore_hwfn*,struct ecore_ptt*,scalar_t__,int) ; 

__attribute__((used)) static void ecore_config_block_inputs(struct ecore_hwfn *p_hwfn,
							   struct ecore_ptt *p_ptt)
{
	struct dbg_tools_data *dev_data = &p_hwfn->dbg_info;
	struct dbg_bus_data *bus = &dev_data->bus;
	u8 hw_ids[VALUES_PER_CYCLE];
	u8 val_id, state_id;

	ecore_assign_hw_ids(p_hwfn, hw_ids);

	/* Assign a HW ID to each trigger state */
	if (dev_data->bus.trigger_en) {
		for (state_id = 0; state_id < bus->next_trigger_state; state_id++) {
			for (val_id = 0; val_id < VALUES_PER_CYCLE; val_id++) {
				u8 state_data = bus->trigger_states[state_id].data;

				if (GET_FIELD(state_data, DBG_BUS_TRIGGER_STATE_DATA_CONSTRAINT_DWORD_MASK) & (1 << val_id)) {
					ecore_wr(p_hwfn, p_ptt, DBG_REG_TRIGGER_STATE_ID_0 + state_id * BYTES_IN_DWORD, hw_ids[val_id]);
					break;
				}
			}
		}
	}

	/* Configure HW ID mask */
	dev_data->bus.hw_id_mask = 0;
	for (val_id = 0; val_id < VALUES_PER_CYCLE; val_id++)
		bus->hw_id_mask |= (hw_ids[val_id] << (val_id * HW_ID_BITS));
	ecore_wr(p_hwfn, p_ptt, DBG_REG_HW_ID_NUM, bus->hw_id_mask);

	/* Configure additional K2 PCIE registers */
	if (dev_data->chip_id == CHIP_K2 &&
		(GET_FIELD(bus->blocks[BLOCK_PCIE].data, DBG_BUS_BLOCK_DATA_ENABLE_MASK) ||
			GET_FIELD(bus->blocks[BLOCK_PHY_PCIE].data, DBG_BUS_BLOCK_DATA_ENABLE_MASK))) {
		ecore_wr(p_hwfn, p_ptt, PCIE_REG_DBG_REPEAT_THRESHOLD_COUNT_K2_E5, 1);
		ecore_wr(p_hwfn, p_ptt, PCIE_REG_DBG_FW_TRIGGER_ENABLE_K2_E5, 1);
	}
}