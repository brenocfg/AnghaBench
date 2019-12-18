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
typedef  scalar_t__ u16 ;
struct i40e_hw {int dummy; } ;
struct ixl_pf {int state; struct i40e_hw hw; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int IXL_PF_STATE_ADAPTER_RESETTING ; 
 int IXL_PF_STATE_MDD_PENDING ; 
 int /*<<< orphan*/  iflib_admin_intr_deferred (int /*<<< orphan*/ ) ; 
 struct ixl_pf* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_enable_intr0 (struct i40e_hw*) ; 
 int /*<<< orphan*/  ixl_handle_empr_reset (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_handle_mdd_event (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_process_adminq (struct ixl_pf*,scalar_t__*) ; 
 int /*<<< orphan*/  ixl_update_link_status (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_update_stats_counters (struct ixl_pf*) ; 

__attribute__((used)) static void
ixl_if_update_admin_status(if_ctx_t ctx)
{
	struct ixl_pf			*pf = iflib_get_softc(ctx);
	struct i40e_hw			*hw = &pf->hw;
	u16				pending;

	if (pf->state & IXL_PF_STATE_ADAPTER_RESETTING)
		ixl_handle_empr_reset(pf);

	if (pf->state & IXL_PF_STATE_MDD_PENDING)
		ixl_handle_mdd_event(pf);

	ixl_process_adminq(pf, &pending);
	ixl_update_link_status(pf);
	ixl_update_stats_counters(pf);
	
	/*
	 * If there are still messages to process, reschedule ourselves.
	 * Otherwise, re-enable our interrupt and go to sleep.
	 */
	if (pending > 0)
		iflib_admin_intr_deferred(ctx);
	else
		ixl_enable_intr0(hw);
}