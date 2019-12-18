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
typedef  int u16 ;
struct e1000_hw {int dummy; } ;
struct adapter {struct e1000_hw hw; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EM_NVM_MSIX_N_MASK ; 
 int EM_NVM_MSIX_N_SHIFT ; 
 int /*<<< orphan*/  EM_NVM_PCIE_CTRL ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  e1000_read_nvm (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  e1000_update_nvm_checksum (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_write_nvm (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
em_enable_vectors_82574(if_ctx_t ctx)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	struct e1000_hw *hw = &adapter->hw;
	device_t dev = iflib_get_dev(ctx);
	u16 edata;

	e1000_read_nvm(hw, EM_NVM_PCIE_CTRL, 1, &edata);
	if (bootverbose)
		device_printf(dev, "EM_NVM_PCIE_CTRL = %#06x\n", edata);
	if (((edata & EM_NVM_MSIX_N_MASK) >> EM_NVM_MSIX_N_SHIFT) != 4) {
		device_printf(dev, "Writing to eeprom: increasing "
		    "reported MSI-X vectors from 3 to 5...\n");
		edata &= ~(EM_NVM_MSIX_N_MASK);
		edata |= 4 << EM_NVM_MSIX_N_SHIFT;
		e1000_write_nvm(hw, EM_NVM_PCIE_CTRL, 1, &edata);
		e1000_update_nvm_checksum(hw);
		device_printf(dev, "Writing to eeprom: done\n");
	}
}