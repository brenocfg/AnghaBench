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
typedef  int uint32_t ;
struct TYPE_2__ {scalar_t__ seid; } ;
struct ixl_vf {int /*<<< orphan*/  vf_num; int /*<<< orphan*/  qtag; TYPE_1__ vsi; } ;
struct i40e_hw {int dummy; } ;
struct ixl_pf {int /*<<< orphan*/  dev; struct i40e_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  I40E_VFGEN_RSTAT1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_VPGEN_VFRSTAT (int /*<<< orphan*/ ) ; 
 int I40E_VPGEN_VFRSTAT_VFRD_MASK ; 
 int /*<<< orphan*/  I40E_VPGEN_VFRTRIG (int /*<<< orphan*/ ) ; 
 int I40E_VPGEN_VFRTRIG_VFSWR_MASK ; 
 int IXL_VF_RESET_TIMEOUT ; 
 int VIRTCHNL_VFR_COMPLETED ; 
 int VIRTCHNL_VFR_VFACTIVE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_disable_rings (struct ixl_pf*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixl_flush (struct i40e_hw*) ; 
 int ixl_flush_pcie (struct ixl_pf*,struct ixl_vf*) ; 
 int /*<<< orphan*/  ixl_pf_qmgr_clear_queue_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixl_vf_map_queues (struct ixl_pf*,struct ixl_vf*) ; 
 int /*<<< orphan*/  ixl_vf_release_resources (struct ixl_pf*,struct ixl_vf*) ; 
 int /*<<< orphan*/  ixl_vf_setup_vsi (struct ixl_pf*,struct ixl_vf*) ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ixl_reinit_vf(struct ixl_pf *pf, struct ixl_vf *vf)
{
	struct i40e_hw *hw;
	uint32_t vfrstat, vfrtrig;
	int i, error;

	hw = &pf->hw;

	error = ixl_flush_pcie(pf, vf);
	if (error != 0)
		device_printf(pf->dev,
		    "Timed out waiting for PCIe activity to stop on VF-%d\n",
		    vf->vf_num);

	for (i = 0; i < IXL_VF_RESET_TIMEOUT; i++) {
		DELAY(10);

		vfrstat = rd32(hw, I40E_VPGEN_VFRSTAT(vf->vf_num));
		if (vfrstat & I40E_VPGEN_VFRSTAT_VFRD_MASK)
			break;
	}

	if (i == IXL_VF_RESET_TIMEOUT)
		device_printf(pf->dev, "VF %d failed to reset\n", vf->vf_num);

	wr32(hw, I40E_VFGEN_RSTAT1(vf->vf_num), VIRTCHNL_VFR_COMPLETED);

	vfrtrig = rd32(hw, I40E_VPGEN_VFRTRIG(vf->vf_num));
	vfrtrig &= ~I40E_VPGEN_VFRTRIG_VFSWR_MASK;
	wr32(hw, I40E_VPGEN_VFRTRIG(vf->vf_num), vfrtrig);

	if (vf->vsi.seid != 0)
		ixl_disable_rings(pf, &vf->vsi, &vf->qtag);
	ixl_pf_qmgr_clear_queue_flags(&vf->qtag);

	ixl_vf_release_resources(pf, vf);
	ixl_vf_setup_vsi(pf, vf);
	ixl_vf_map_queues(pf, vf);

	wr32(hw, I40E_VFGEN_RSTAT1(vf->vf_num), VIRTCHNL_VFR_VFACTIVE);
	ixl_flush(hw);
}