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
typedef  size_t uint8_t ;
typedef  int uint16_t ;
struct al_hal_eth_adapter {TYPE_3__* ec_regs_base; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {TYPE_2__* tpm_udma; TYPE_1__* tpm_sel; } ;
struct TYPE_5__ {int /*<<< orphan*/  vlan_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  etype; } ;

/* Variables and functions */
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  al_reg_write32 (int /*<<< orphan*/ *,int) ; 

int al_eth_vlan_mod_config(struct al_hal_eth_adapter *adapter, uint8_t udma_id, uint16_t udma_etype, uint16_t vlan1_data, uint16_t vlan2_data)
{
	al_dbg("[%s]: config vlan modification registers. udma id %d.\n", adapter->name, udma_id);

	al_reg_write32(&adapter->ec_regs_base->tpm_sel[udma_id].etype, udma_etype);
	al_reg_write32(&adapter->ec_regs_base->tpm_udma[udma_id].vlan_data, vlan1_data | (vlan2_data << 16));

	return 0;
}