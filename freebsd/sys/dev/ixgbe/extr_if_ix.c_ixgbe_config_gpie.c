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
typedef  int u32 ;
struct TYPE_2__ {int type; } ;
struct ixgbe_hw {TYPE_1__ mac; } ;
struct adapter {scalar_t__ intr_type; int feat_en; struct ixgbe_hw hw; } ;

/* Variables and functions */
 scalar_t__ IFLIB_INTR_MSIX ; 
 int IXGBE_FEATURE_FAN_FAIL ; 
 int IXGBE_FEATURE_TEMP_SENSOR ; 
 int /*<<< orphan*/  IXGBE_GPIE ; 
 int IXGBE_GPIE_EIAME ; 
 int IXGBE_GPIE_MSIX_MODE ; 
 int IXGBE_GPIE_OCD ; 
 int IXGBE_GPIE_PBA_SUPPORT ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int IXGBE_SDP0_GPIEN_X540 ; 
 int IXGBE_SDP1_GPIEN ; 
 int IXGBE_SDP2_GPIEN ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
#define  ixgbe_mac_82599EB 130 
#define  ixgbe_mac_X550EM_a 129 
#define  ixgbe_mac_X550EM_x 128 

__attribute__((used)) static void
ixgbe_config_gpie(struct adapter *adapter)
{
	struct ixgbe_hw *hw = &adapter->hw;
	u32             gpie;

	gpie = IXGBE_READ_REG(hw, IXGBE_GPIE);

	if (adapter->intr_type == IFLIB_INTR_MSIX) {
		/* Enable Enhanced MSI-X mode */
		gpie |= IXGBE_GPIE_MSIX_MODE
		     |  IXGBE_GPIE_EIAME
		     |  IXGBE_GPIE_PBA_SUPPORT
		     |  IXGBE_GPIE_OCD;
	}

	/* Fan Failure Interrupt */
	if (adapter->feat_en & IXGBE_FEATURE_FAN_FAIL)
		gpie |= IXGBE_SDP1_GPIEN;

	/* Thermal Sensor Interrupt */
	if (adapter->feat_en & IXGBE_FEATURE_TEMP_SENSOR)
		gpie |= IXGBE_SDP0_GPIEN_X540;

	/* Link detection */
	switch (hw->mac.type) {
	case ixgbe_mac_82599EB:
		gpie |= IXGBE_SDP1_GPIEN | IXGBE_SDP2_GPIEN;
		break;
	case ixgbe_mac_X550EM_x:
	case ixgbe_mac_X550EM_a:
		gpie |= IXGBE_SDP0_GPIEN_X540;
		break;
	default:
		break;
	}

	IXGBE_WRITE_REG(hw, IXGBE_GPIE, gpie);

}