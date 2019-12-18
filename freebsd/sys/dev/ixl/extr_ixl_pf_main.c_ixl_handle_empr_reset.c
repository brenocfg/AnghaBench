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
typedef  int u32 ;
struct ixl_vsi {TYPE_1__* ifp; } ;
struct i40e_hw {int dummy; } ;
struct ixl_pf {int /*<<< orphan*/  state; struct i40e_hw hw; struct ixl_vsi vsi; } ;
struct TYPE_2__ {int if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_GLGEN_RSTAT ; 
 int I40E_GLGEN_RSTAT_DEVSTATE_MASK ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IXL_DBG_INFO ; 
 int /*<<< orphan*/  IXL_PF_STATE_ADAPTER_RESETTING ; 
 int /*<<< orphan*/  atomic_clear_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_msec_delay (int) ; 
 int /*<<< orphan*/  ixl_dbg (struct ixl_pf*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ixl_prepare_for_reset (struct ixl_pf*,int) ; 
 int /*<<< orphan*/  ixl_rebuild_hw_structs_after_reset (struct ixl_pf*) ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 

void
ixl_handle_empr_reset(struct ixl_pf *pf)
{
	struct ixl_vsi	*vsi = &pf->vsi;
	struct i40e_hw	*hw = &pf->hw;
	bool is_up = !!(vsi->ifp->if_drv_flags & IFF_DRV_RUNNING);
	int count = 0;
	u32 reg;

	ixl_prepare_for_reset(pf, is_up);

	/* Typically finishes within 3-4 seconds */
	while (count++ < 100) {
		reg = rd32(hw, I40E_GLGEN_RSTAT)
			& I40E_GLGEN_RSTAT_DEVSTATE_MASK;
		if (reg)
			i40e_msec_delay(100);
		else
			break;
	}
	ixl_dbg(pf, IXL_DBG_INFO,
			"Reset wait count: %d\n", count);

	ixl_rebuild_hw_structs_after_reset(pf);

	atomic_clear_int(&pf->state, IXL_PF_STATE_ADAPTER_RESETTING);
}