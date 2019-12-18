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
struct ixgbe_hw {int dummy; } ;
struct adapter {scalar_t__ intr_type; int feat_cap; int /*<<< orphan*/  advertise; scalar_t__ dmac; int /*<<< orphan*/ * mta; struct ixgbe_hw hw; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 scalar_t__ IFLIB_INTR_LEGACY ; 
 int IXGBE_FEATURE_LEGACY_IRQ ; 
 int IXGBE_FEATURE_SRIOV ; 
 int MAX_NUM_MULTICAST_ADDRESSES ; 
 int /*<<< orphan*/  M_IXGBE ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_add_device_sysctls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_add_hw_stats (struct adapter*) ; 
 int /*<<< orphan*/  ixgbe_advertise_speed ; 
 int /*<<< orphan*/  ixgbe_bypass_init (struct adapter*) ; 
 int /*<<< orphan*/  ixgbe_define_iov_schemas (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ixgbe_enable_tx_laser (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  ixgbe_get_advertise (struct adapter*) ; 
 int /*<<< orphan*/  ixgbe_get_slot_info (struct adapter*) ; 
 int /*<<< orphan*/  ixgbe_if_update_admin_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_initialize_iov (struct adapter*) ; 
 int /*<<< orphan*/  ixgbe_set_advertise (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_set_phy_power (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int ixgbe_setup_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_update_stats_counters (struct adapter*) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ixgbe_if_attach_post(if_ctx_t ctx)
{
	device_t dev;
	struct adapter  *adapter;
	struct ixgbe_hw *hw;
	int             error = 0;

	dev = iflib_get_dev(ctx);
	adapter = iflib_get_softc(ctx);
	hw = &adapter->hw;


	if (adapter->intr_type == IFLIB_INTR_LEGACY &&
		(adapter->feat_cap & IXGBE_FEATURE_LEGACY_IRQ) == 0) {
		device_printf(dev, "Device does not support legacy interrupts");
		error = ENXIO;
		goto err;
	}

	/* Allocate multicast array memory. */
	adapter->mta = malloc(sizeof(*adapter->mta) *
	                      MAX_NUM_MULTICAST_ADDRESSES, M_IXGBE, M_NOWAIT);
	if (adapter->mta == NULL) {
		device_printf(dev, "Can not allocate multicast setup array\n");
		error = ENOMEM;
		goto err;
	}

	/* hw.ix defaults init */
	ixgbe_set_advertise(adapter, ixgbe_advertise_speed);

	/* Enable the optics for 82599 SFP+ fiber */
	ixgbe_enable_tx_laser(hw);

	/* Enable power to the phy. */
	ixgbe_set_phy_power(hw, TRUE);

	ixgbe_initialize_iov(adapter);

	error = ixgbe_setup_interface(ctx);
	if (error) {
		device_printf(dev, "Interface setup failed: %d\n", error);
		goto err;
	}

	ixgbe_if_update_admin_status(ctx);

	/* Initialize statistics */
	ixgbe_update_stats_counters(adapter);
	ixgbe_add_hw_stats(adapter);

	/* Check PCIE slot type/speed/width */
	ixgbe_get_slot_info(adapter);

	/*
	 * Do time init and sysctl init here, but
	 * only on the first port of a bypass adapter.
	 */
	ixgbe_bypass_init(adapter);

	/* Set an initial dmac value */
	adapter->dmac = 0;
	/* Set initial advertised speeds (if applicable) */
	adapter->advertise = ixgbe_get_advertise(adapter);

	if (adapter->feat_cap & IXGBE_FEATURE_SRIOV)
		ixgbe_define_iov_schemas(dev, &error);

	/* Add sysctls */
	ixgbe_add_device_sysctls(ctx);

	return (0);
err:
	return (error);
}