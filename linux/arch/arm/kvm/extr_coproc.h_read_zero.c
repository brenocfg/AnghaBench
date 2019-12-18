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
struct kvm_vcpu {int dummy; } ;
struct coproc_params {int /*<<< orphan*/  Rt1; } ;

/* Variables and functions */
 scalar_t__* vcpu_reg (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool read_zero(struct kvm_vcpu *vcpu,
			     const struct coproc_params *p)
{
	*vcpu_reg(vcpu, p->Rt1) = 0;
	return true;
}