#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 scalar_t__ avic ; 
 scalar_t__ irqchip_split (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool svm_get_enable_apicv(struct kvm_vcpu *vcpu)
{
	return avic && irqchip_split(vcpu->kvm);
}