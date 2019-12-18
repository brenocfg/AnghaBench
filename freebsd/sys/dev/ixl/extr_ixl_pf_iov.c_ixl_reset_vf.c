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
typedef  int /*<<< orphan*/  uint32_t ;
struct ixl_vf {int /*<<< orphan*/  vf_num; } ;
struct i40e_hw {int dummy; } ;
struct ixl_pf {struct i40e_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_VPGEN_VFRTRIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_VPGEN_VFRTRIG_VFSWR_MASK ; 
 int /*<<< orphan*/  ixl_dbg_iov (struct ixl_pf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_flush (struct i40e_hw*) ; 
 int /*<<< orphan*/  ixl_reinit_vf (struct ixl_pf*,struct ixl_vf*) ; 
 int /*<<< orphan*/  rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixl_reset_vf(struct ixl_pf *pf, struct ixl_vf *vf)
{
	struct i40e_hw *hw;
	uint32_t vfrtrig;

	hw = &pf->hw;

	ixl_dbg_iov(pf, "Resetting VF-%d\n", vf->vf_num);

	vfrtrig = rd32(hw, I40E_VPGEN_VFRTRIG(vf->vf_num));
	vfrtrig |= I40E_VPGEN_VFRTRIG_VFSWR_MASK;
	wr32(hw, I40E_VPGEN_VFRTRIG(vf->vf_num), vfrtrig);
	ixl_flush(hw);

	ixl_reinit_vf(pf, vf);

	ixl_dbg_iov(pf, "Resetting VF-%d done.\n", vf->vf_num);
}