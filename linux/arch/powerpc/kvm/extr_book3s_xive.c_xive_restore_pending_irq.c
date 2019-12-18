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
typedef  size_t u16 ;
struct kvmppc_xive_src_block {struct kvmppc_xive_irq_state* irq_state; } ;
struct kvmppc_xive_irq_state {int /*<<< orphan*/  ipi_data; int /*<<< orphan*/  valid; } ;
struct kvmppc_xive {int dummy; } ;

/* Variables and functions */
 struct kvmppc_xive_src_block* kvmppc_xive_find_source (struct kvmppc_xive*,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  xive_irq_trigger (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool xive_restore_pending_irq(struct kvmppc_xive *xive, u32 irq)
{
	struct kvmppc_xive_src_block *sb;
	struct kvmppc_xive_irq_state *state;
	u16 idx;

	sb = kvmppc_xive_find_source(xive, irq, &idx);
	if (!sb)
		return false;
	state = &sb->irq_state[idx];
	if (!state->valid)
		return false;

	/*
	 * Trigger the IPI. This assumes we never restore a pass-through
	 * interrupt which should be safe enough
	 */
	xive_irq_trigger(&state->ipi_data);

	return true;
}