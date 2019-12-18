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
typedef  size_t uint8_t ;
struct al_hal_eth_adapter {TYPE_1__* ec_regs_base; } ;
struct TYPE_4__ {int /*<<< orphan*/  bc_udma; int /*<<< orphan*/  mc_udma; int /*<<< orphan*/  uc_udma; } ;
struct TYPE_3__ {TYPE_2__* tfw_udma; } ;

/* Variables and functions */
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,size_t) ; 

int al_eth_switching_default_bitmap_set(struct al_hal_eth_adapter *adapter, uint8_t udma_id, uint8_t udma_uc_bitmask,
						uint8_t udma_mc_bitmask,uint8_t udma_bc_bitmask)
{
	al_reg_write32(&adapter->ec_regs_base->tfw_udma[udma_id].uc_udma, udma_uc_bitmask);
	al_reg_write32(&adapter->ec_regs_base->tfw_udma[udma_id].mc_udma, udma_mc_bitmask);
	al_reg_write32(&adapter->ec_regs_base->tfw_udma[udma_id].bc_udma, udma_bc_bitmask);

	return 0;
}