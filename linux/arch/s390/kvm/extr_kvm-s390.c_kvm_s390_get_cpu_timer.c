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
struct TYPE_3__ {scalar_t__ cputm_start; TYPE_2__* sie_block; int /*<<< orphan*/  cputm_seqcount; int /*<<< orphan*/  cputm_enabled; } ;
struct kvm_vcpu {scalar_t__ cpu; TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_4__ {int /*<<< orphan*/  cputm; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ get_tod_clock_fast () ; 
 scalar_t__ likely (scalar_t__) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 unsigned int raw_read_seqcount (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqcount_retry (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ smp_processor_id () ; 
 scalar_t__ unlikely (int) ; 

__u64 kvm_s390_get_cpu_timer(struct kvm_vcpu *vcpu)
{
	unsigned int seq;
	__u64 value;

	if (unlikely(!vcpu->arch.cputm_enabled))
		return vcpu->arch.sie_block->cputm;

	preempt_disable(); /* protect from TOD sync and vcpu_load/put */
	do {
		seq = raw_read_seqcount(&vcpu->arch.cputm_seqcount);
		/*
		 * If the writer would ever execute a read in the critical
		 * section, e.g. in irq context, we have a deadlock.
		 */
		WARN_ON_ONCE((seq & 1) && smp_processor_id() == vcpu->cpu);
		value = vcpu->arch.sie_block->cputm;
		/* if cputm_start is 0, accounting is being started/stopped */
		if (likely(vcpu->arch.cputm_start))
			value -= get_tod_clock_fast() - vcpu->arch.cputm_start;
	} while (read_seqcount_retry(&vcpu->arch.cputm_seqcount, seq & ~1));
	preempt_enable();
	return value;
}