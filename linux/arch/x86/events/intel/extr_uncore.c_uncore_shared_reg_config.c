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
typedef  int /*<<< orphan*/  u64 ;
struct intel_uncore_extra_reg {int /*<<< orphan*/  lock; int /*<<< orphan*/  config; } ;
struct intel_uncore_box {struct intel_uncore_extra_reg* shared_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

u64 uncore_shared_reg_config(struct intel_uncore_box *box, int idx)
{
	struct intel_uncore_extra_reg *er;
	unsigned long flags;
	u64 config;

	er = &box->shared_regs[idx];

	raw_spin_lock_irqsave(&er->lock, flags);
	config = er->config;
	raw_spin_unlock_irqrestore(&er->lock, flags);

	return config;
}