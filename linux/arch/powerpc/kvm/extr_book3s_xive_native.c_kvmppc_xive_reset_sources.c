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
struct kvmppc_xive_src_block {struct kvmppc_xive_irq_state* irq_state; } ;
struct kvmppc_xive_irq_state {scalar_t__ act_priority; scalar_t__ pt_number; int /*<<< orphan*/ * pt_data; scalar_t__ ipi_number; int /*<<< orphan*/  ipi_data; scalar_t__ act_server; scalar_t__ eisn; int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int KVMPPC_XICS_IRQ_PER_ICS ; 
 scalar_t__ MASKED ; 
 int /*<<< orphan*/  XIVE_ESB_SET_PQ_01 ; 
 int /*<<< orphan*/  xive_native_configure_irq (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xive_vm_esb_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvmppc_xive_reset_sources(struct kvmppc_xive_src_block *sb)
{
	int i;

	for (i = 0; i < KVMPPC_XICS_IRQ_PER_ICS; i++) {
		struct kvmppc_xive_irq_state *state = &sb->irq_state[i];

		if (!state->valid)
			continue;

		if (state->act_priority == MASKED)
			continue;

		state->eisn = 0;
		state->act_server = 0;
		state->act_priority = MASKED;
		xive_vm_esb_load(&state->ipi_data, XIVE_ESB_SET_PQ_01);
		xive_native_configure_irq(state->ipi_number, 0, MASKED, 0);
		if (state->pt_number) {
			xive_vm_esb_load(state->pt_data, XIVE_ESB_SET_PQ_01);
			xive_native_configure_irq(state->pt_number,
						  0, MASKED, 0);
		}
	}
}