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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct kvmppc_xive_irq_state {scalar_t__ act_priority; int /*<<< orphan*/  number; int /*<<< orphan*/  act_server; } ;
struct kvmppc_xive {int dummy; } ;
struct TYPE_2__ {struct kvmppc_xive* xive; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ MASKED ; 
 int /*<<< orphan*/  kvmppc_xive_select_irq (struct kvmppc_xive_irq_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int kvmppc_xive_select_target (struct kvm*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kvmppc_xive_vp (struct kvmppc_xive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xive_inc_q_pending (struct kvm*,int /*<<< orphan*/ ,scalar_t__) ; 
 int xive_native_configure_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xive_target_interrupt(struct kvm *kvm,
				 struct kvmppc_xive_irq_state *state,
				 u32 server, u8 prio)
{
	struct kvmppc_xive *xive = kvm->arch.xive;
	u32 hw_num;
	int rc;

	/*
	 * This will return a tentative server and actual
	 * priority. The count for that new target will have
	 * already been incremented.
	 */
	rc = kvmppc_xive_select_target(kvm, &server, prio);

	/*
	 * We failed to find a target ? Not much we can do
	 * at least until we support the GIQ.
	 */
	if (rc)
		return rc;

	/*
	 * Increment the old queue pending count if there
	 * was one so that the old queue count gets adjusted later
	 * when observed to be empty.
	 */
	if (state->act_priority != MASKED)
		xive_inc_q_pending(kvm,
				   state->act_server,
				   state->act_priority);
	/*
	 * Update state and HW
	 */
	state->act_priority = prio;
	state->act_server = server;

	/* Get the right irq */
	kvmppc_xive_select_irq(state, &hw_num, NULL);

	return xive_native_configure_irq(hw_num,
					 kvmppc_xive_vp(xive, server),
					 prio, state->number);
}