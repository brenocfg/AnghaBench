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
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
struct TYPE_2__ {unsigned long hior; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_kvmppc_hv_enabled (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_book3s (struct kvm_vcpu*) ; 

__attribute__((used)) static inline unsigned long kvmppc_interrupt_offset(struct kvm_vcpu *vcpu)
{
	if (!is_kvmppc_hv_enabled(vcpu->kvm))
		return to_book3s(vcpu)->hior;
	return 0;
}