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
typedef  int /*<<< orphan*/  uint32_t ;
struct al_hal_eth_adapter {TYPE_2__* ec_regs_base; } ;
struct al_eth_fwd_ctrl_table_entry {int dummy; } ;
typedef  scalar_t__ al_bool ;
struct TYPE_3__ {int /*<<< orphan*/  ctrl_table_def; } ;
struct TYPE_4__ {TYPE_1__ rfw; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_RFW_CTRL_TABLE_DEF_SEL ; 
 int /*<<< orphan*/  al_eth_fwd_ctrl_entry_to_val (struct al_eth_fwd_ctrl_table_entry*) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int al_eth_ctrl_table_def_set(struct al_hal_eth_adapter *adapter,
			      al_bool use_table,
			      struct al_eth_fwd_ctrl_table_entry *entry)
{
	uint32_t val = al_eth_fwd_ctrl_entry_to_val(entry);

	if (use_table)
		val |= EC_RFW_CTRL_TABLE_DEF_SEL;

	al_reg_write32(&adapter->ec_regs_base->rfw.ctrl_table_def, val);

	return 0;
}