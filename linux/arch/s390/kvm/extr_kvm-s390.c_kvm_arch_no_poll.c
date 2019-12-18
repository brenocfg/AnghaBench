#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  halt_no_poll_steal; } ;
struct kvm_vcpu {TYPE_1__ stat; } ;
struct TYPE_4__ {int avg_steal_timer; } ;

/* Variables and functions */
 TYPE_2__ S390_lowcore ; 
 int TICK_USEC ; 
 int halt_poll_max_steal ; 

bool kvm_arch_no_poll(struct kvm_vcpu *vcpu)
{
	/* do not poll with more than halt_poll_max_steal percent of steal time */
	if (S390_lowcore.avg_steal_timer * 100 / (TICK_USEC << 12) >=
	    halt_poll_max_steal) {
		vcpu->stat.halt_no_poll_steal++;
		return true;
	}
	return false;
}