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
struct TYPE_2__ {unsigned long dec_expires; int timer_running; int /*<<< orphan*/  dec_timer; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 unsigned long get_tb () ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_core_prepare_to_enter (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_core_queue_dec (struct kvm_vcpu*) ; 
 unsigned long tb_to_ns (unsigned long) ; 

__attribute__((used)) static void kvmppc_set_timer(struct kvm_vcpu *vcpu)
{
	unsigned long dec_nsec, now;

	now = get_tb();
	if (now > vcpu->arch.dec_expires) {
		/* decrementer has already gone negative */
		kvmppc_core_queue_dec(vcpu);
		kvmppc_core_prepare_to_enter(vcpu);
		return;
	}
	dec_nsec = tb_to_ns(vcpu->arch.dec_expires - now);
	hrtimer_start(&vcpu->arch.dec_timer, dec_nsec, HRTIMER_MODE_REL);
	vcpu->arch.timer_running = 1;
}