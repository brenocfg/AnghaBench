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
struct TYPE_3__ {int /*<<< orphan*/  seid; } ;
struct ixl_vf {TYPE_1__ vsi; } ;
struct ixl_pf {int /*<<< orphan*/  hw; } ;
struct TYPE_4__ {int port_vlan_flags; int /*<<< orphan*/  valid_sections; } ;
struct i40e_vsi_context {TYPE_2__ info; int /*<<< orphan*/  seid; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_AQ_VSI_PROP_VLAN_VALID ; 
 int I40E_AQ_VSI_PVLAN_EMOD_STR_BOTH ; 
 int I40E_AQ_VSI_PVLAN_MODE_ALL ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int i40e_aq_update_vsi_params (int /*<<< orphan*/ *,struct i40e_vsi_context*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum i40e_status_code
ixl_vf_enable_vlan_strip(struct ixl_pf *pf, struct ixl_vf *vf)
{
	struct i40e_vsi_context vsi_ctx;

	vsi_ctx.seid = vf->vsi.seid;

	bzero(&vsi_ctx.info, sizeof(vsi_ctx.info));
	vsi_ctx.info.valid_sections = htole16(I40E_AQ_VSI_PROP_VLAN_VALID);
	vsi_ctx.info.port_vlan_flags = I40E_AQ_VSI_PVLAN_MODE_ALL |
	    I40E_AQ_VSI_PVLAN_EMOD_STR_BOTH;
	return (i40e_aq_update_vsi_params(&pf->hw, &vsi_ctx, NULL));
}