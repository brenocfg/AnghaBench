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
struct TYPE_3__ {int /*<<< orphan*/  stimer_pending_bitmap; } ;
struct TYPE_4__ {TYPE_1__ hyperv; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  HV_SYNIC_STIMER_COUNT ; 
 int /*<<< orphan*/  bitmap_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool kvm_hv_has_stimer_pending(struct kvm_vcpu *vcpu)
{
	return !bitmap_empty(vcpu->arch.hyperv.stimer_pending_bitmap,
			     HV_SYNIC_STIMER_COUNT);
}