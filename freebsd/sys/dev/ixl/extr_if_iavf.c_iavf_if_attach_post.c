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
struct ixl_vsi {int /*<<< orphan*/  eth_stats; TYPE_1__* shared; int /*<<< orphan*/  num_tx_queues; int /*<<< orphan*/  num_rx_queues; int /*<<< orphan*/  ifp; } ;
struct i40e_hw {int dummy; } ;
struct iavf_sc {int /*<<< orphan*/  queues_enabled; int /*<<< orphan*/  init_state; struct ixl_vsi vsi; struct i40e_hw hw; } ;
struct i40e_eth_stats {int dummy; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  isc_ntxqsets; int /*<<< orphan*/  isc_nrxqsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  IAVF_INIT_READY ; 
 int /*<<< orphan*/  INIT_DBG_DEV (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  atomic_store_rel_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iavf_add_device_sysctls (struct iavf_sc*) ; 
 int /*<<< orphan*/  iavf_enable_adminq_irq (struct i40e_hw*) ; 
 int /*<<< orphan*/  iavf_setup_interface (int /*<<< orphan*/ ,struct iavf_sc*) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_get_ifp (int /*<<< orphan*/ ) ; 
 struct iavf_sc* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iavf_if_attach_post(if_ctx_t ctx)
{
	device_t dev;
	struct iavf_sc	*sc;
	struct i40e_hw	*hw;
	struct ixl_vsi *vsi;
	int error = 0;

	INIT_DBG_DEV(dev, "begin");

	dev = iflib_get_dev(ctx);
	sc = iflib_get_softc(ctx);
	vsi = &sc->vsi;
	vsi->ifp = iflib_get_ifp(ctx);
	hw = &sc->hw;

	/* Save off determined number of queues for interface */
	vsi->num_rx_queues = vsi->shared->isc_nrxqsets;
	vsi->num_tx_queues = vsi->shared->isc_ntxqsets;

	/* Setup the stack interface */
	iavf_setup_interface(dev, sc);

	INIT_DBG_DEV(dev, "Interface setup complete");

	/* Initialize statistics & add sysctls */
	bzero(&sc->vsi.eth_stats, sizeof(struct i40e_eth_stats));
	iavf_add_device_sysctls(sc);

	sc->init_state = IAVF_INIT_READY;
	atomic_store_rel_32(&sc->queues_enabled, 0);

	/* We want AQ enabled early for init */
	iavf_enable_adminq_irq(hw);

	INIT_DBG_DEV(dev, "end");

	return (error);
}