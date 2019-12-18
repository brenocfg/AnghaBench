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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct al_hal_eth_adapter {TYPE_1__* ec_regs_base; } ;
struct TYPE_4__ {int /*<<< orphan*/  thash_table_data; int /*<<< orphan*/  thash_table_addr; } ;
struct TYPE_3__ {TYPE_2__ rfw; } ;

/* Variables and functions */
 scalar_t__ AL_ETH_RX_THASH_TABLE_SIZE ; 
 scalar_t__ AL_ETH_THASH_Q_MASK ; 
 scalar_t__ AL_ETH_THASH_Q_SHIFT ; 
 scalar_t__ AL_ETH_THASH_UDMA_MASK ; 
 scalar_t__ AL_ETH_THASH_UDMA_SHIFT ; 
 int /*<<< orphan*/  al_assert (int) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,scalar_t__) ; 

int al_eth_thash_table_set(struct al_hal_eth_adapter *adapter, uint32_t idx, uint8_t udma, uint32_t queue)
{
	uint32_t entry;
	al_assert(idx < AL_ETH_RX_THASH_TABLE_SIZE); /*valid THASH index*/

	entry = (udma << AL_ETH_THASH_UDMA_SHIFT) & AL_ETH_THASH_UDMA_MASK;
	entry |= (queue << AL_ETH_THASH_Q_SHIFT) & AL_ETH_THASH_Q_MASK;

	al_reg_write32(&adapter->ec_regs_base->rfw.thash_table_addr, idx);
	al_reg_write32(&adapter->ec_regs_base->rfw.thash_table_data, entry);
	return 0;
}