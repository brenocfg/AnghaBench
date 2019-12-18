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
struct TYPE_3__ {int type; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct adapter {int feat_cap; int feat_en; TYPE_2__ hw; } ;

/* Variables and functions */
 int IXGBE_FEATURE_LEGACY_TX ; 
 int IXGBE_FEATURE_NEEDS_CTXD ; 
 int IXGBE_FEATURE_NETMAP ; 
 int IXGBE_FEATURE_RSS ; 
 int IXGBE_FEATURE_VF ; 
#define  ixgbe_mac_82599_vf 132 
#define  ixgbe_mac_X540_vf 131 
#define  ixgbe_mac_X550EM_a_vf 130 
#define  ixgbe_mac_X550EM_x_vf 129 
#define  ixgbe_mac_X550_vf 128 

__attribute__((used)) static void
ixv_init_device_features(struct adapter *adapter)
{
	adapter->feat_cap = IXGBE_FEATURE_NETMAP
	                  | IXGBE_FEATURE_VF
	                  | IXGBE_FEATURE_LEGACY_TX;

	/* A tad short on feature flags for VFs, atm. */
	switch (adapter->hw.mac.type) {
	case ixgbe_mac_82599_vf:
		break;
	case ixgbe_mac_X540_vf:
		break;
	case ixgbe_mac_X550_vf:
	case ixgbe_mac_X550EM_x_vf:
	case ixgbe_mac_X550EM_a_vf:
		adapter->feat_cap |= IXGBE_FEATURE_NEEDS_CTXD;
		adapter->feat_cap |= IXGBE_FEATURE_RSS;
		break;
	default:
		break;
	}

	/* Enabled by default... */
	/* Is a virtual function (VF) */
	if (adapter->feat_cap & IXGBE_FEATURE_VF)
		adapter->feat_en |= IXGBE_FEATURE_VF;
	/* Netmap */
	if (adapter->feat_cap & IXGBE_FEATURE_NETMAP)
		adapter->feat_en |= IXGBE_FEATURE_NETMAP;
	/* Receive-Side Scaling (RSS) */
	if (adapter->feat_cap & IXGBE_FEATURE_RSS)
		adapter->feat_en |= IXGBE_FEATURE_RSS;
	/* Needs advanced context descriptor regardless of offloads req'd */
	if (adapter->feat_cap & IXGBE_FEATURE_NEEDS_CTXD)
		adapter->feat_en |= IXGBE_FEATURE_NEEDS_CTXD;
}