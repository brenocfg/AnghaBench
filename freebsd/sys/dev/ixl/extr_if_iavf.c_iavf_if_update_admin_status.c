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
struct iavf_sc {struct i40e_hw hw; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  iavf_enable_adminq_irq (struct i40e_hw*) ; 
 int /*<<< orphan*/  iavf_process_adminq (struct iavf_sc*,scalar_t__*) ; 
 int /*<<< orphan*/  iavf_update_link_status (struct iavf_sc*) ; 
 int /*<<< orphan*/  iflib_admin_intr_deferred (int /*<<< orphan*/ ) ; 
 struct iavf_sc* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iavf_if_update_admin_status(if_ctx_t ctx)
{
	struct iavf_sc *sc = iflib_get_softc(ctx);
	struct i40e_hw *hw = &sc->hw;
	u16 pending;

	iavf_process_adminq(sc, &pending);
	iavf_update_link_status(sc);
	
	/*
	 * If there are still messages to process, reschedule.
	 * Otherwise, re-enable the Admin Queue interrupt.
	 */
	if (pending > 0)
		iflib_admin_intr_deferred(ctx);
	else
		iavf_enable_adminq_irq(hw);
}