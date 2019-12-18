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
typedef  int /*<<< orphan*/  u32 ;
struct xive_irq_data {int dummy; } ;
struct kvmppc_xive_src_block {struct kvmppc_xive_irq_state* irq_state; } ;
struct kvmppc_xive_irq_state {scalar_t__ act_priority; int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int KVMPPC_XICS_IRQ_PER_ICS ; 
 scalar_t__ MASKED ; 
 int /*<<< orphan*/  kvmppc_xive_select_irq (struct kvmppc_xive_irq_state*,int /*<<< orphan*/ *,struct xive_irq_data**) ; 
 int /*<<< orphan*/  xive_native_sync_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xive_native_sync_source (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvmppc_xive_native_sync_sources(struct kvmppc_xive_src_block *sb)
{
	int j;

	for (j = 0; j < KVMPPC_XICS_IRQ_PER_ICS; j++) {
		struct kvmppc_xive_irq_state *state = &sb->irq_state[j];
		struct xive_irq_data *xd;
		u32 hw_num;

		if (!state->valid)
			continue;

		/*
		 * The struct kvmppc_xive_irq_state reflects the state
		 * of the EAS configuration and not the state of the
		 * source. The source is masked setting the PQ bits to
		 * '-Q', which is what is being done before calling
		 * the KVM_DEV_XIVE_EQ_SYNC control.
		 *
		 * If a source EAS is configured, OPAL syncs the XIVE
		 * IC of the source and the XIVE IC of the previous
		 * target if any.
		 *
		 * So it should be fine ignoring MASKED sources as
		 * they have been synced already.
		 */
		if (state->act_priority == MASKED)
			continue;

		kvmppc_xive_select_irq(state, &hw_num, &xd);
		xive_native_sync_source(hw_num);
		xive_native_sync_queue(hw_num);
	}
}