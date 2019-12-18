#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct al_hal_eth_adapter {int dummy; } ;
struct al_eth_epe_p_reg_entry {int dummy; } ;
struct al_eth_epe_control_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  al_eth_epe_entry_set (struct al_hal_eth_adapter*,int /*<<< orphan*/ ,struct al_eth_epe_p_reg_entry*,struct al_eth_epe_control_entry*) ; 

int al_eth_rx_parser_entry_update(struct al_hal_eth_adapter *adapter, uint32_t idx,
		struct al_eth_epe_p_reg_entry *reg_entry,
		struct al_eth_epe_control_entry *control_entry)
{
	al_eth_epe_entry_set(adapter, idx, reg_entry, control_entry);
	return 0;
}