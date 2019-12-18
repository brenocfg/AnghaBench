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
struct TYPE_2__ {unsigned long long dec; int /*<<< orphan*/  dec_jiffies; int /*<<< orphan*/  dec_timer; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 unsigned long do_div (unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_tb () ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_try_to_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_set (unsigned long long,unsigned long) ; 
 int /*<<< orphan*/  kvmppc_core_dequeue_dec (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long long) ; 
 unsigned long long tb_to_ns (unsigned long long) ; 

void kvmppc_emulate_dec(struct kvm_vcpu *vcpu)
{
	unsigned long dec_nsec;
	unsigned long long dec_time;

	pr_debug("mtDEC: %lx\n", vcpu->arch.dec);
	hrtimer_try_to_cancel(&vcpu->arch.dec_timer);

#ifdef CONFIG_PPC_BOOK3S
	/* mtdec lowers the interrupt line when positive. */
	kvmppc_core_dequeue_dec(vcpu);
#endif

#ifdef CONFIG_BOOKE
	/* On BOOKE, DEC = 0 is as good as decrementer not enabled */
	if (vcpu->arch.dec == 0)
		return;
#endif

	/*
	 * The decrementer ticks at the same rate as the timebase, so
	 * that's how we convert the guest DEC value to the number of
	 * host ticks.
	 */

	dec_time = vcpu->arch.dec;
	/*
	 * Guest timebase ticks at the same frequency as host timebase.
	 * So use the host timebase calculations for decrementer emulation.
	 */
	dec_time = tb_to_ns(dec_time);
	dec_nsec = do_div(dec_time, NSEC_PER_SEC);
	hrtimer_start(&vcpu->arch.dec_timer,
		ktime_set(dec_time, dec_nsec), HRTIMER_MODE_REL);
	vcpu->arch.dec_jiffies = get_tb();
}