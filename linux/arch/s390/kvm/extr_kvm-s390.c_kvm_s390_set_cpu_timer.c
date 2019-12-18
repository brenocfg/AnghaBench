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
struct TYPE_4__ {int /*<<< orphan*/  cputm_seqcount; TYPE_1__* sie_block; int /*<<< orphan*/  cputm_start; scalar_t__ cputm_enabled; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_3__ {int /*<<< orphan*/  cputm; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_tod_clock_fast () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  raw_write_seqcount_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_write_seqcount_end (int /*<<< orphan*/ *) ; 

void kvm_s390_set_cpu_timer(struct kvm_vcpu *vcpu, __u64 cputm)
{
	preempt_disable(); /* protect from TOD sync and vcpu_load/put */
	raw_write_seqcount_begin(&vcpu->arch.cputm_seqcount);
	if (vcpu->arch.cputm_enabled)
		vcpu->arch.cputm_start = get_tod_clock_fast();
	vcpu->arch.sie_block->cputm = cputm;
	raw_write_seqcount_end(&vcpu->arch.cputm_seqcount);
	preempt_enable();
}