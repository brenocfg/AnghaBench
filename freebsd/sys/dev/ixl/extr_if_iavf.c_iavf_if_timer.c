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
typedef  scalar_t__ uint16_t ;
typedef  int u32 ;
struct i40e_hw {int dummy; } ;
struct iavf_sc {struct i40e_hw hw; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_VFGEN_RSTAT ; 
 int I40E_VFGEN_RSTAT_VFR_STATE_MASK ; 
 int VIRTCHNL_VFR_COMPLETED ; 
 int VIRTCHNL_VFR_VFACTIVE ; 
 int /*<<< orphan*/  iavf_dbg_info (struct iavf_sc*,char*,int) ; 
 int /*<<< orphan*/  iavf_request_stats (struct iavf_sc*) ; 
 int /*<<< orphan*/  iflib_admin_intr_deferred (int /*<<< orphan*/ ) ; 
 struct iavf_sc* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int rd32 (struct i40e_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iavf_if_timer(if_ctx_t ctx, uint16_t qid)
{
	struct iavf_sc *sc = iflib_get_softc(ctx);
	struct i40e_hw *hw = &sc->hw;
	u32 val;

	if (qid != 0)
		return;

	/* Check for when PF triggers a VF reset */
	val = rd32(hw, I40E_VFGEN_RSTAT) &
	    I40E_VFGEN_RSTAT_VFR_STATE_MASK;
	if (val != VIRTCHNL_VFR_VFACTIVE
	    && val != VIRTCHNL_VFR_COMPLETED) {
		iavf_dbg_info(sc, "reset in progress! (%d)\n", val);
		return;
	}

	/* Fire off the adminq task */
	iflib_admin_intr_deferred(ctx);

	/* Update stats */
	iavf_request_stats(sc);
}