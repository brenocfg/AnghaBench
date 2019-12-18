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
struct TYPE_5__ {int /*<<< orphan*/  func; } ;
struct TYPE_4__ {int type; } ;
struct TYPE_6__ {int /*<<< orphan*/  device_id; TYPE_2__ bus; TYPE_1__ mac; } ;
struct adapter {int feat_cap; int feat_en; int /*<<< orphan*/  dev; TYPE_3__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_DEV_ID_82598AT ; 
 int /*<<< orphan*/  IXGBE_DEV_ID_82599_BYPASS ; 
 int /*<<< orphan*/  IXGBE_DEV_ID_82599_QSFP_SF_QP ; 
 int /*<<< orphan*/  IXGBE_DEV_ID_X540_BYPASS ; 
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_A_1G_T ; 
 int /*<<< orphan*/  IXGBE_DEV_ID_X550EM_A_1G_T_L ; 
 int IXGBE_FEATURE_BYPASS ; 
 int IXGBE_FEATURE_EEE ; 
 int IXGBE_FEATURE_FAN_FAIL ; 
 int IXGBE_FEATURE_FDIR ; 
 int IXGBE_FEATURE_LEGACY_IRQ ; 
 int IXGBE_FEATURE_MSI ; 
 int IXGBE_FEATURE_MSIX ; 
 int IXGBE_FEATURE_NETMAP ; 
 int IXGBE_FEATURE_RSS ; 
 int IXGBE_FEATURE_SRIOV ; 
 int IXGBE_FEATURE_TEMP_SENSOR ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ixgbe_enable_fdir ; 
 int /*<<< orphan*/  ixgbe_enable_msix ; 
 scalar_t__ ixgbe_enable_rss ; 
#define  ixgbe_mac_82598EB 133 
#define  ixgbe_mac_82599EB 132 
#define  ixgbe_mac_X540 131 
#define  ixgbe_mac_X550 130 
#define  ixgbe_mac_X550EM_a 129 
#define  ixgbe_mac_X550EM_x 128 

__attribute__((used)) static void
ixgbe_init_device_features(struct adapter *adapter)
{
	adapter->feat_cap = IXGBE_FEATURE_NETMAP
	                  | IXGBE_FEATURE_RSS
	                  | IXGBE_FEATURE_MSI
	                  | IXGBE_FEATURE_MSIX
	                  | IXGBE_FEATURE_LEGACY_IRQ;

	/* Set capabilities first... */
	switch (adapter->hw.mac.type) {
	case ixgbe_mac_82598EB:
		if (adapter->hw.device_id == IXGBE_DEV_ID_82598AT)
			adapter->feat_cap |= IXGBE_FEATURE_FAN_FAIL;
		break;
	case ixgbe_mac_X540:
		adapter->feat_cap |= IXGBE_FEATURE_SRIOV;
		adapter->feat_cap |= IXGBE_FEATURE_FDIR;
		if ((adapter->hw.device_id == IXGBE_DEV_ID_X540_BYPASS) &&
		    (adapter->hw.bus.func == 0))
			adapter->feat_cap |= IXGBE_FEATURE_BYPASS;
		break;
	case ixgbe_mac_X550:
		adapter->feat_cap |= IXGBE_FEATURE_TEMP_SENSOR;
		adapter->feat_cap |= IXGBE_FEATURE_SRIOV;
		adapter->feat_cap |= IXGBE_FEATURE_FDIR;
		break;
	case ixgbe_mac_X550EM_x:
		adapter->feat_cap |= IXGBE_FEATURE_SRIOV;
		adapter->feat_cap |= IXGBE_FEATURE_FDIR;
		break;
	case ixgbe_mac_X550EM_a:
		adapter->feat_cap |= IXGBE_FEATURE_SRIOV;
		adapter->feat_cap |= IXGBE_FEATURE_FDIR;
		adapter->feat_cap &= ~IXGBE_FEATURE_LEGACY_IRQ;
		if ((adapter->hw.device_id == IXGBE_DEV_ID_X550EM_A_1G_T) ||
		    (adapter->hw.device_id == IXGBE_DEV_ID_X550EM_A_1G_T_L)) {
			adapter->feat_cap |= IXGBE_FEATURE_TEMP_SENSOR;
			adapter->feat_cap |= IXGBE_FEATURE_EEE;
		}
		break;
	case ixgbe_mac_82599EB:
		adapter->feat_cap |= IXGBE_FEATURE_SRIOV;
		adapter->feat_cap |= IXGBE_FEATURE_FDIR;
		if ((adapter->hw.device_id == IXGBE_DEV_ID_82599_BYPASS) &&
		    (adapter->hw.bus.func == 0))
			adapter->feat_cap |= IXGBE_FEATURE_BYPASS;
		if (adapter->hw.device_id == IXGBE_DEV_ID_82599_QSFP_SF_QP)
			adapter->feat_cap &= ~IXGBE_FEATURE_LEGACY_IRQ;
		break;
	default:
		break;
	}

	/* Enabled by default... */
	/* Fan failure detection */
	if (adapter->feat_cap & IXGBE_FEATURE_FAN_FAIL)
		adapter->feat_en |= IXGBE_FEATURE_FAN_FAIL;
	/* Netmap */
	if (adapter->feat_cap & IXGBE_FEATURE_NETMAP)
		adapter->feat_en |= IXGBE_FEATURE_NETMAP;
	/* EEE */
	if (adapter->feat_cap & IXGBE_FEATURE_EEE)
		adapter->feat_en |= IXGBE_FEATURE_EEE;
	/* Thermal Sensor */
	if (adapter->feat_cap & IXGBE_FEATURE_TEMP_SENSOR)
		adapter->feat_en |= IXGBE_FEATURE_TEMP_SENSOR;

	/* Enabled via global sysctl... */
	/* Flow Director */
	if (ixgbe_enable_fdir) {
		if (adapter->feat_cap & IXGBE_FEATURE_FDIR)
			adapter->feat_en |= IXGBE_FEATURE_FDIR;
		else
			device_printf(adapter->dev, "Device does not support Flow Director. Leaving disabled.");
	}
	/*
	 * Message Signal Interrupts - Extended (MSI-X)
	 * Normal MSI is only enabled if MSI-X calls fail.
	 */
	if (!ixgbe_enable_msix)
		adapter->feat_cap &= ~IXGBE_FEATURE_MSIX;
	/* Receive-Side Scaling (RSS) */
	if ((adapter->feat_cap & IXGBE_FEATURE_RSS) && ixgbe_enable_rss)
		adapter->feat_en |= IXGBE_FEATURE_RSS;

	/* Disable features with unmet dependencies... */
	/* No MSI-X */
	if (!(adapter->feat_cap & IXGBE_FEATURE_MSIX)) {
		adapter->feat_cap &= ~IXGBE_FEATURE_RSS;
		adapter->feat_cap &= ~IXGBE_FEATURE_SRIOV;
		adapter->feat_en &= ~IXGBE_FEATURE_RSS;
		adapter->feat_en &= ~IXGBE_FEATURE_SRIOV;
	}
}