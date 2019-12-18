#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct ixgbe_hw {int device_id; TYPE_1__ mac; int /*<<< orphan*/  subsystem_device_id; int /*<<< orphan*/  subsystem_vendor_id; int /*<<< orphan*/  revision_id; int /*<<< orphan*/  vendor_id; } ;
struct adapter {struct ixgbe_hw hw; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  IXGBE_DEV_ID_82599_VF 132 
#define  IXGBE_DEV_ID_X540_VF 131 
#define  IXGBE_DEV_ID_X550EM_A_VF 130 
#define  IXGBE_DEV_ID_X550EM_X_VF 129 
#define  IXGBE_DEV_ID_X550_VF 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_mac_82599_vf ; 
 int /*<<< orphan*/  ixgbe_mac_X540_vf ; 
 int /*<<< orphan*/  ixgbe_mac_X550EM_a_vf ; 
 int /*<<< orphan*/  ixgbe_mac_X550EM_x_vf ; 
 int /*<<< orphan*/  ixgbe_mac_X550_vf ; 
 int /*<<< orphan*/  ixgbe_mac_unknown ; 
 int pci_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_revid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_subdevice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_subvendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_vendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixv_identify_hardware(if_ctx_t ctx)
{
	struct adapter  *adapter = iflib_get_softc(ctx);
	device_t        dev = iflib_get_dev(ctx);
	struct ixgbe_hw *hw = &adapter->hw;

	/* Save off the information about this board */
	hw->vendor_id = pci_get_vendor(dev);
	hw->device_id = pci_get_device(dev);
	hw->revision_id = pci_get_revid(dev);
	hw->subsystem_vendor_id = pci_get_subvendor(dev);
	hw->subsystem_device_id = pci_get_subdevice(dev);

	/* A subset of set_mac_type */
	switch (hw->device_id) {
	case IXGBE_DEV_ID_82599_VF:
		hw->mac.type = ixgbe_mac_82599_vf;
		break;
	case IXGBE_DEV_ID_X540_VF:
		hw->mac.type = ixgbe_mac_X540_vf;
		break;
	case IXGBE_DEV_ID_X550_VF:
		hw->mac.type = ixgbe_mac_X550_vf;
		break;
	case IXGBE_DEV_ID_X550EM_X_VF:
		hw->mac.type = ixgbe_mac_X550EM_x_vf;
		break;
	case IXGBE_DEV_ID_X550EM_A_VF:
		hw->mac.type = ixgbe_mac_X550EM_a_vf;
		break;
	default:
		device_printf(dev, "unknown mac type\n");
		hw->mac.type = ixgbe_mac_unknown;
		break;
	}
}