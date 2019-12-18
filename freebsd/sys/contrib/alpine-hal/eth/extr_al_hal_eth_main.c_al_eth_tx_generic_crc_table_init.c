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
struct al_hal_eth_adapter {scalar_t__ rev_id; TYPE_1__* ec_regs_base; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  crc_csum_replace; int /*<<< orphan*/  tx_gcp_legacy; } ;
struct TYPE_3__ {TYPE_2__ tfw_v3; } ;

/* Variables and functions */
 scalar_t__ AL_ETH_REV_ID_2 ; 
 int AL_ETH_TX_GENERIC_CRC_ENTRIES_NUM ; 
 int /*<<< orphan*/  al_assert (int) ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * al_eth_generic_tx_crc_gcp ; 
 int /*<<< orphan*/  al_eth_tx_generic_crc_table_entry_set (struct al_hal_eth_adapter*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 

int al_eth_tx_generic_crc_table_init(struct al_hal_eth_adapter *adapter)
{
	int idx;
	al_assert((adapter->rev_id > AL_ETH_REV_ID_2));

	al_dbg("eth [%s]: enable tx_generic_crc\n", adapter->name);
	al_reg_write32(&adapter->ec_regs_base->tfw_v3.tx_gcp_legacy, 0x0);
	al_reg_write32(&adapter->ec_regs_base->tfw_v3.crc_csum_replace, 0x0);
	for (idx = 0; idx < AL_ETH_TX_GENERIC_CRC_ENTRIES_NUM; idx++)
		al_eth_tx_generic_crc_table_entry_set(adapter, idx,
				&al_eth_generic_tx_crc_gcp[idx]);

	return 0;
}