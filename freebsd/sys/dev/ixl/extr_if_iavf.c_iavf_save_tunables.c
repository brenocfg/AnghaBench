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
struct iavf_sc {scalar_t__ rx_itr; scalar_t__ tx_itr; TYPE_2__ vsi; TYPE_1__ hw; int /*<<< orphan*/  dbg_mask; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ IXL_ITR_4K ; 
 scalar_t__ IXL_ITR_8K ; 
 scalar_t__ IXL_MAX_ITR ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  iavf_core_debug_mask ; 
 int /*<<< orphan*/  iavf_enable_head_writeback ; 
 scalar_t__ iavf_rx_itr ; 
 int /*<<< orphan*/  iavf_shared_debug_mask ; 
 scalar_t__ iavf_tx_itr ; 

__attribute__((used)) static void
iavf_save_tunables(struct iavf_sc *sc)
{
	device_t dev = sc->dev;

	/* Save tunable information */
	sc->dbg_mask = iavf_core_debug_mask;
	sc->hw.debug_mask = iavf_shared_debug_mask;
	sc->vsi.enable_head_writeback = !!(iavf_enable_head_writeback);

	if (iavf_tx_itr < 0 || iavf_tx_itr > IXL_MAX_ITR) {
		device_printf(dev, "Invalid tx_itr value of %d set!\n",
		    iavf_tx_itr);
		device_printf(dev, "tx_itr must be between %d and %d, "
		    "inclusive\n",
		    0, IXL_MAX_ITR);
		device_printf(dev, "Using default value of %d instead\n",
		    IXL_ITR_4K);
		sc->tx_itr = IXL_ITR_4K;
	} else
		sc->tx_itr = iavf_tx_itr;

	if (iavf_rx_itr < 0 || iavf_rx_itr > IXL_MAX_ITR) {
		device_printf(dev, "Invalid rx_itr value of %d set!\n",
		    iavf_rx_itr);
		device_printf(dev, "rx_itr must be between %d and %d, "
		    "inclusive\n",
		    0, IXL_MAX_ITR);
		device_printf(dev, "Using default value of %d instead\n",
		    IXL_ITR_8K);
		sc->rx_itr = IXL_ITR_8K;
	} else
		sc->rx_itr = iavf_rx_itr;
}