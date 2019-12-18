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
struct TYPE_3__ {int /*<<< orphan*/ * gfns; } ;
struct TYPE_4__ {TYPE_1__ apf; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_PF_PER_VCPU ; 
 int roundup_pow_of_two (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void kvm_async_pf_hash_reset(struct kvm_vcpu *vcpu)
{
	int i;
	for (i = 0; i < roundup_pow_of_two(ASYNC_PF_PER_VCPU); i++)
		vcpu->arch.apf.gfns[i] = ~0;
}