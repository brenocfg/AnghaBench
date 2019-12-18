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
struct kvmppc_xive_src_block {int /*<<< orphan*/  lock; } ;
struct kvmppc_xive_irq_state {int /*<<< orphan*/  in_eoi; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xive_lock_for_unmask(struct kvmppc_xive_src_block *sb,
				 struct kvmppc_xive_irq_state *state)
{
	/*
	 * Take the lock try again if racing with H_EOI
	 */
	for (;;) {
		arch_spin_lock(&sb->lock);
		if (!state->in_eoi)
			break;
		arch_spin_unlock(&sb->lock);
	}
}