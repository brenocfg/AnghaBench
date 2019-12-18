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
typedef  scalar_t__ uint32_t ;
struct al_hal_eth_adapter {TYPE_2__* ec_regs_base; } ;
struct al_eth_fwd_vid_table_entry {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  vid_table_data; int /*<<< orphan*/  vid_table_addr; } ;
struct TYPE_4__ {TYPE_1__ rfw; } ;

/* Variables and functions */
 scalar_t__ AL_ETH_FWD_VID_TABLE_NUM ; 
 int /*<<< orphan*/  al_assert (int) ; 
 scalar_t__ al_eth_fwd_vid_entry_to_val (struct al_eth_fwd_vid_table_entry*) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,scalar_t__) ; 

int al_eth_fwd_vid_table_set(struct al_hal_eth_adapter *adapter, uint32_t idx,
			     struct al_eth_fwd_vid_table_entry *entry)
{
	uint32_t val;
	al_assert(idx < AL_ETH_FWD_VID_TABLE_NUM); /* valid VID index */

	val = al_eth_fwd_vid_entry_to_val(entry);
	al_reg_write32(&adapter->ec_regs_base->rfw.vid_table_addr, idx);
	al_reg_write32(&adapter->ec_regs_base->rfw.vid_table_data, val);
	return 0;
}