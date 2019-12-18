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
struct ixl_vsi {int /*<<< orphan*/  seid; TYPE_2__* hw; int /*<<< orphan*/  ftl; scalar_t__ back; } ;
struct ixl_pf {scalar_t__ enable_tx_fc_filter; int /*<<< orphan*/  hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXL_VLAN_ANY ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  i40e_add_filter_to_drop_tx_flow_control_frames (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_aq_set_vsi_broadcast (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixl_add_filter (struct ixl_vsi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_del_default_hw_filters (struct ixl_vsi*) ; 

void
ixl_init_filters(struct ixl_vsi *vsi)
{
	struct ixl_pf *pf = (struct ixl_pf *)vsi->back;

	/* Initialize mac filter list for VSI */
	SLIST_INIT(&vsi->ftl);

	/* Receive broadcast Ethernet frames */
	i40e_aq_set_vsi_broadcast(&pf->hw, vsi->seid, TRUE, NULL);

	ixl_del_default_hw_filters(vsi);

	ixl_add_filter(vsi, vsi->hw->mac.addr, IXL_VLAN_ANY);
	/*
	 * Prevent Tx flow control frames from being sent out by
	 * non-firmware transmitters.
	 * This affects every VSI in the PF.
	 */
	if (pf->enable_tx_fc_filter)
		i40e_add_filter_to_drop_tx_flow_control_frames(vsi->hw, vsi->seid);
}