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
struct al_hal_eth_adapter {scalar_t__ rev_id; TYPE_2__* mac_regs_base; } ;
struct TYPE_3__ {int /*<<< orphan*/  v3_pcs_10g_ll_ncerr; int /*<<< orphan*/  v3_pcs_10g_ll_cerr; } ;
struct TYPE_4__ {TYPE_1__ stat; } ;

/* Variables and functions */
 scalar_t__ AL_ETH_REV_ID_2 ; 
 int /*<<< orphan*/  al_reg_read32 (int /*<<< orphan*/ *) ; 

int al_eth_fec_stats_get(struct al_hal_eth_adapter *adapter,
			uint32_t *corrected, uint32_t *uncorrectable)
{
	if (adapter->rev_id <= AL_ETH_REV_ID_2)
		return -1;

	*corrected = al_reg_read32(&adapter->mac_regs_base->stat.v3_pcs_10g_ll_cerr);
	*uncorrectable = al_reg_read32(&adapter->mac_regs_base->stat.v3_pcs_10g_ll_ncerr);

	return 0;
}