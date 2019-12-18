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

/* Variables and functions */
 int /*<<< orphan*/  set_intercept_indicators_ext (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  set_intercept_indicators_io (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  set_intercept_indicators_mchk (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  set_intercept_indicators_stop (struct kvm_vcpu*) ; 

__attribute__((used)) static void set_intercept_indicators(struct kvm_vcpu *vcpu)
{
	set_intercept_indicators_io(vcpu);
	set_intercept_indicators_ext(vcpu);
	set_intercept_indicators_mchk(vcpu);
	set_intercept_indicators_stop(vcpu);
}