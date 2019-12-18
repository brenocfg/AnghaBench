#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {unsigned long nip; } ;
struct TYPE_6__ {scalar_t__ addr; } ;
struct optimized_kprobe {TYPE_1__ kp; } ;
struct TYPE_7__ {int /*<<< orphan*/  kprobe_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  KPROBE_HIT_ACTIVE ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  current_kprobe ; 
 TYPE_4__* get_kprobe_ctlblk () ; 
 scalar_t__ kprobe_disabled (TYPE_1__*) ; 
 scalar_t__ kprobe_running () ; 
 int /*<<< orphan*/  kprobes_inc_nmissed_count (TYPE_1__*) ; 
 int /*<<< orphan*/  opt_pre_handler (TYPE_1__*,struct pt_regs*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable_no_resched () ; 

__attribute__((used)) static void optimized_callback(struct optimized_kprobe *op,
			       struct pt_regs *regs)
{
	/* This is possible if op is under delayed unoptimizing */
	if (kprobe_disabled(&op->kp))
		return;

	preempt_disable();

	if (kprobe_running()) {
		kprobes_inc_nmissed_count(&op->kp);
	} else {
		__this_cpu_write(current_kprobe, &op->kp);
		regs->nip = (unsigned long)op->kp.addr;
		get_kprobe_ctlblk()->kprobe_status = KPROBE_HIT_ACTIVE;
		opt_pre_handler(&op->kp, regs);
		__this_cpu_write(current_kprobe, NULL);
	}

	preempt_enable_no_resched();
}