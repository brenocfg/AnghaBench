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
struct TYPE_2__ {scalar_t__ hw_filters_del; scalar_t__ hw_filters_add; int /*<<< orphan*/  seid; } ;
struct ixl_vf {TYPE_1__ vsi; } ;
struct i40e_hw {int dummy; } ;
struct ixl_pf {int /*<<< orphan*/  dev; struct i40e_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int i40e_aq_set_vsi_broadcast (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixl_reconfigure_filters (TYPE_1__*) ; 
 int ixl_vf_alloc_vsi (struct ixl_pf*,struct ixl_vf*) ; 

__attribute__((used)) static int
ixl_vf_setup_vsi(struct ixl_pf *pf, struct ixl_vf *vf)
{
	struct i40e_hw *hw;
	int error;

	hw = &pf->hw;

	error = ixl_vf_alloc_vsi(pf, vf);
	if (error != 0)
		return (error);

	/* Let VF receive broadcast Ethernet frames */
	error = i40e_aq_set_vsi_broadcast(hw, vf->vsi.seid, TRUE, NULL);
	if (error)
		device_printf(pf->dev, "Error configuring VF VSI for broadcast promiscuous\n");
	/* Re-add VF's MAC/VLAN filters to its VSI */
	ixl_reconfigure_filters(&vf->vsi);
	/* Reset stats? */
	vf->vsi.hw_filters_add = 0;
	vf->vsi.hw_filters_del = 0;

	return (0);
}