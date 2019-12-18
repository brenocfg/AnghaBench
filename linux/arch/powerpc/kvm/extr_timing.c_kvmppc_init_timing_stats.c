#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ tv64; } ;
struct TYPE_4__ {scalar_t__ tv64; } ;
struct TYPE_6__ {int last_exit_type; int* timing_min_duration; int /*<<< orphan*/  exit_timing_lock; TYPE_2__ timing_last_enter; TYPE_1__ timing_exit; scalar_t__ timing_last_exit; scalar_t__* timing_sum_quad_duration; scalar_t__* timing_sum_duration; scalar_t__* timing_max_duration; scalar_t__* timing_count_type; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;

/* Variables and functions */
 int __NUMBER_OF_KVM_EXIT_TYPES ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void kvmppc_init_timing_stats(struct kvm_vcpu *vcpu)
{
	int i;

	/* Take a lock to avoid concurrent updates */
	mutex_lock(&vcpu->arch.exit_timing_lock);

	vcpu->arch.last_exit_type = 0xDEAD;
	for (i = 0; i < __NUMBER_OF_KVM_EXIT_TYPES; i++) {
		vcpu->arch.timing_count_type[i] = 0;
		vcpu->arch.timing_max_duration[i] = 0;
		vcpu->arch.timing_min_duration[i] = 0xFFFFFFFF;
		vcpu->arch.timing_sum_duration[i] = 0;
		vcpu->arch.timing_sum_quad_duration[i] = 0;
	}
	vcpu->arch.timing_last_exit = 0;
	vcpu->arch.timing_exit.tv64 = 0;
	vcpu->arch.timing_last_enter.tv64 = 0;

	mutex_unlock(&vcpu->arch.exit_timing_lock);
}