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
struct al_eth_board_params {int dummy; } ;
struct al_eth_adapter {scalar_t__ board_type; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  ec_base; int /*<<< orphan*/  mac_base; int /*<<< orphan*/  internal_pcie_base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ALPINE_INTEGRATED ; 
 int /*<<< orphan*/  al_eth_board_params_get (int /*<<< orphan*/ ,struct al_eth_board_params*) ; 
 int /*<<< orphan*/  al_eth_board_params_set (int /*<<< orphan*/ ,struct al_eth_board_params*) ; 
 int al_eth_flr_rmn (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_eth_fpga_read_pci_config ; 
 int /*<<< orphan*/  al_eth_fpga_write_pci_config ; 
 int /*<<< orphan*/  al_eth_mac_addr_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_eth_mac_addr_store (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_eth_read_pci_config ; 
 int /*<<< orphan*/  al_eth_write_pci_config ; 

__attribute__((used)) static int
al_eth_function_reset(struct al_eth_adapter *adapter)
{
	struct al_eth_board_params params;
	int rc;

	/* save board params so we restore it after reset */
	al_eth_board_params_get(adapter->mac_base, &params);
	al_eth_mac_addr_read(adapter->ec_base, 0, adapter->mac_addr);
	if (adapter->board_type == ALPINE_INTEGRATED)
		rc = al_eth_flr_rmn(&al_eth_read_pci_config,
		    &al_eth_write_pci_config,
		    adapter->dev, adapter->mac_base);
	else
		rc = al_eth_flr_rmn(&al_eth_fpga_read_pci_config,
		    &al_eth_fpga_write_pci_config,
		    adapter->internal_pcie_base, adapter->mac_base);

	/* restore params */
	al_eth_board_params_set(adapter->mac_base, &params);
	al_eth_mac_addr_store(adapter->ec_base, 0, adapter->mac_addr);

	return (rc);
}