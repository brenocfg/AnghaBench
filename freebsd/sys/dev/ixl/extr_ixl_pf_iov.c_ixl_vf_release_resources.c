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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {scalar_t__ num_rx_queues; scalar_t__ num_tx_queues; } ;
struct ixl_vf {TYPE_2__ vsi; int /*<<< orphan*/  vf_num; } ;
struct TYPE_3__ {int num_msix_vectors_vf; } ;
struct i40e_hw {TYPE_1__ func_caps; } ;
struct ixl_pf {struct i40e_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_VFINT_DYN_CTL0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_VPINT_LNKLST0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXL_VFINT_DYN_CTLN_REG (struct i40e_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXL_VPINT_LNKLSTN_REG (struct i40e_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_vf_disable_queue_intr (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_vf_unregister_intr (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_vf_vsi_release (struct ixl_pf*,TYPE_2__*) ; 

__attribute__((used)) static void
ixl_vf_release_resources(struct ixl_pf *pf, struct ixl_vf *vf)
{
	struct i40e_hw *hw;
	uint32_t vfint_reg, vpint_reg;
	int i;

	hw = &pf->hw;

	ixl_vf_vsi_release(pf, &vf->vsi);

	/* Index 0 has a special register. */
	ixl_vf_disable_queue_intr(hw, I40E_VFINT_DYN_CTL0(vf->vf_num));

	for (i = 1; i < hw->func_caps.num_msix_vectors_vf; i++) {
		vfint_reg = IXL_VFINT_DYN_CTLN_REG(hw, i , vf->vf_num);
		ixl_vf_disable_queue_intr(hw, vfint_reg);
	}

	/* Index 0 has a special register. */
	ixl_vf_unregister_intr(hw, I40E_VPINT_LNKLST0(vf->vf_num));

	for (i = 1; i < hw->func_caps.num_msix_vectors_vf; i++) {
		vpint_reg = IXL_VPINT_LNKLSTN_REG(hw, i, vf->vf_num);
		ixl_vf_unregister_intr(hw, vpint_reg);
	}

	vf->vsi.num_tx_queues = 0;
	vf->vsi.num_rx_queues = 0;
}