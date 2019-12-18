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
struct TYPE_4__ {int enable_head_writeback; } ;
struct TYPE_3__ {int /*<<< orphan*/  debug_mask; } ;
struct ixl_pf {int enable_vf_loopback; int i2c_access_method; scalar_t__ rx_itr; scalar_t__ tx_itr; int /*<<< orphan*/  dynamic_tx_itr; int /*<<< orphan*/  dynamic_rx_itr; TYPE_2__ vsi; TYPE_1__ hw; int /*<<< orphan*/  dbg_mask; int /*<<< orphan*/  enable_tx_fc_filter; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ IXL_ITR_4K ; 
 scalar_t__ IXL_ITR_8K ; 
 scalar_t__ IXL_MAX_ITR ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  ixl_core_debug_mask ; 
 int /*<<< orphan*/  ixl_dynamic_rx_itr ; 
 int /*<<< orphan*/  ixl_dynamic_tx_itr ; 
 int /*<<< orphan*/  ixl_enable_head_writeback ; 
 int /*<<< orphan*/  ixl_enable_tx_fc_filter ; 
 int /*<<< orphan*/  ixl_enable_vf_loopback ; 
 int ixl_i2c_access_method ; 
 scalar_t__ ixl_rx_itr ; 
 int /*<<< orphan*/  ixl_shared_debug_mask ; 
 scalar_t__ ixl_tx_itr ; 

__attribute__((used)) static void
ixl_save_pf_tunables(struct ixl_pf *pf)
{
	device_t dev = pf->dev;

	/* Save tunable information */
	pf->enable_tx_fc_filter = ixl_enable_tx_fc_filter;
	pf->dbg_mask = ixl_core_debug_mask;
	pf->hw.debug_mask = ixl_shared_debug_mask;
	pf->vsi.enable_head_writeback = !!(ixl_enable_head_writeback);
	pf->enable_vf_loopback = !!(ixl_enable_vf_loopback);
#if 0
	pf->dynamic_rx_itr = ixl_dynamic_rx_itr;
	pf->dynamic_tx_itr = ixl_dynamic_tx_itr;
#endif

	if (ixl_i2c_access_method > 3 || ixl_i2c_access_method < 0)
		pf->i2c_access_method = 0;
	else
		pf->i2c_access_method = ixl_i2c_access_method;

	if (ixl_tx_itr < 0 || ixl_tx_itr > IXL_MAX_ITR) {
		device_printf(dev, "Invalid tx_itr value of %d set!\n",
		    ixl_tx_itr);
		device_printf(dev, "tx_itr must be between %d and %d, "
		    "inclusive\n",
		    0, IXL_MAX_ITR);
		device_printf(dev, "Using default value of %d instead\n",
		    IXL_ITR_4K);
		pf->tx_itr = IXL_ITR_4K;
	} else
		pf->tx_itr = ixl_tx_itr;

	if (ixl_rx_itr < 0 || ixl_rx_itr > IXL_MAX_ITR) {
		device_printf(dev, "Invalid rx_itr value of %d set!\n",
		    ixl_rx_itr);
		device_printf(dev, "rx_itr must be between %d and %d, "
		    "inclusive\n",
		    0, IXL_MAX_ITR);
		device_printf(dev, "Using default value of %d instead\n",
		    IXL_ITR_8K);
		pf->rx_itr = IXL_ITR_8K;
	} else
		pf->rx_itr = ixl_rx_itr;
}