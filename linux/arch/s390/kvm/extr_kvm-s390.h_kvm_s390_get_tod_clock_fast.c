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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {scalar_t__ epoch; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ get_tod_clock_fast () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

__attribute__((used)) static inline u64 kvm_s390_get_tod_clock_fast(struct kvm *kvm)
{
	u64 rc;

	preempt_disable();
	rc = get_tod_clock_fast() + kvm->arch.epoch;
	preempt_enable();
	return rc;
}