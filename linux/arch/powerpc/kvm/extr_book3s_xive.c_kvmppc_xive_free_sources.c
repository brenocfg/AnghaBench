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
struct kvmppc_xive_irq_state {int valid; int /*<<< orphan*/ * pt_data; scalar_t__ pt_number; scalar_t__ ipi_number; int /*<<< orphan*/  ipi_data; } ;

/* Variables and functions */
 int KVMPPC_XICS_IRQ_PER_ICS ; 
 int /*<<< orphan*/  kvmppc_xive_cleanup_irq (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xive_cleanup_irq_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xive_native_free_irq (scalar_t__) ; 

void kvmppc_xive_free_sources(struct kvmppc_xive_src_block *sb)
{
	int i;

	for (i = 0; i < KVMPPC_XICS_IRQ_PER_ICS; i++) {
		struct kvmppc_xive_irq_state *state = &sb->irq_state[i];

		if (!state->valid)
			continue;

		kvmppc_xive_cleanup_irq(state->ipi_number, &state->ipi_data);
		xive_cleanup_irq_data(&state->ipi_data);
		xive_native_free_irq(state->ipi_number);

		/* Pass-through, cleanup too but keep IRQ hw data */
		if (state->pt_number)
			kvmppc_xive_cleanup_irq(state->pt_number, state->pt_data);

		state->valid = false;
	}
}