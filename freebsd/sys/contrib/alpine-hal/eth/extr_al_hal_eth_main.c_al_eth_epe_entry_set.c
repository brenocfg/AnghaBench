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
typedef  size_t uint32_t ;
struct al_hal_eth_adapter {TYPE_4__* ec_regs_base; } ;
struct al_eth_epe_p_reg_entry {size_t data; size_t mask; size_t ctrl; } ;
struct al_eth_epe_control_entry {size_t* data; } ;
struct TYPE_8__ {TYPE_3__* epe; TYPE_2__* msp_c; TYPE_1__* epe_p; } ;
struct TYPE_7__ {int /*<<< orphan*/  act_table_data_1; int /*<<< orphan*/  act_table_data_5; int /*<<< orphan*/  act_table_data_4; int /*<<< orphan*/  act_table_data_3; int /*<<< orphan*/  act_table_data_2; int /*<<< orphan*/  act_table_data_6; int /*<<< orphan*/  act_table_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  p_comp_ctrl; int /*<<< orphan*/  p_comp_mask; int /*<<< orphan*/  p_comp_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  comp_ctrl; int /*<<< orphan*/  comp_mask; int /*<<< orphan*/  comp_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void al_eth_epe_entry_set(struct al_hal_eth_adapter *adapter, uint32_t idx,
		struct al_eth_epe_p_reg_entry *reg_entry,
		struct al_eth_epe_control_entry *control_entry)
{
	al_reg_write32(&adapter->ec_regs_base->epe_p[idx].comp_data, reg_entry->data);
	al_reg_write32(&adapter->ec_regs_base->epe_p[idx].comp_mask, reg_entry->mask);
	al_reg_write32(&adapter->ec_regs_base->epe_p[idx].comp_ctrl, reg_entry->ctrl);

	al_reg_write32(&adapter->ec_regs_base->msp_c[idx].p_comp_data, reg_entry->data);
	al_reg_write32(&adapter->ec_regs_base->msp_c[idx].p_comp_mask, reg_entry->mask);
	al_reg_write32(&adapter->ec_regs_base->msp_c[idx].p_comp_ctrl, reg_entry->ctrl);

	/*control table  0*/
	al_reg_write32(&adapter->ec_regs_base->epe[0].act_table_addr, idx);
	al_reg_write32(&adapter->ec_regs_base->epe[0].act_table_data_6,
			control_entry->data[5]);
	al_reg_write32(&adapter->ec_regs_base->epe[0].act_table_data_2,
			control_entry->data[1]);
	al_reg_write32(&adapter->ec_regs_base->epe[0].act_table_data_3,
			control_entry->data[2]);
	al_reg_write32(&adapter->ec_regs_base->epe[0].act_table_data_4,
			control_entry->data[3]);
	al_reg_write32(&adapter->ec_regs_base->epe[0].act_table_data_5,
			control_entry->data[4]);
	al_reg_write32(&adapter->ec_regs_base->epe[0].act_table_data_1,
			control_entry->data[0]);

	/*control table 1*/
	al_reg_write32(&adapter->ec_regs_base->epe[1].act_table_addr, idx);
	al_reg_write32(&adapter->ec_regs_base->epe[1].act_table_data_6,
			control_entry->data[5]);
	al_reg_write32(&adapter->ec_regs_base->epe[1].act_table_data_2,
			control_entry->data[1]);
	al_reg_write32(&adapter->ec_regs_base->epe[1].act_table_data_3,
			control_entry->data[2]);
	al_reg_write32(&adapter->ec_regs_base->epe[1].act_table_data_4,
			control_entry->data[3]);
	al_reg_write32(&adapter->ec_regs_base->epe[1].act_table_data_5,
			control_entry->data[4]);
	al_reg_write32(&adapter->ec_regs_base->epe[1].act_table_data_1,
			control_entry->data[0]);
}