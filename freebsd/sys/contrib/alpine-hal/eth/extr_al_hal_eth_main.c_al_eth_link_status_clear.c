#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct al_hal_eth_adapter {TYPE_3__* mac_regs_base; int /*<<< orphan*/  mac_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
struct TYPE_5__ {int /*<<< orphan*/  pcs_data; int /*<<< orphan*/  pcs_addr; } ;
struct TYPE_6__ {TYPE_1__ mac_10g; TYPE_2__ kr; } ;

/* Variables and functions */
 scalar_t__ AL_ETH_IS_10G_MAC (int /*<<< orphan*/ ) ; 
 scalar_t__ AL_ETH_IS_25G_MAC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_MAC_KR_PCS_BASE_R_STATUS2 ; 
 int /*<<< orphan*/  al_reg_read32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int al_eth_link_status_clear(struct al_hal_eth_adapter *adapter)
{
	int status = 0;

	if (AL_ETH_IS_10G_MAC(adapter->mac_mode) || AL_ETH_IS_25G_MAC(adapter->mac_mode)) {
		al_reg_write32(&adapter->mac_regs_base->kr.pcs_addr, ETH_MAC_KR_PCS_BASE_R_STATUS2);
		al_reg_read32(&adapter->mac_regs_base->kr.pcs_data);

		al_reg_read32(&adapter->mac_regs_base->mac_10g.status);
	} else {
		status = -1;
	}

	return status;
}