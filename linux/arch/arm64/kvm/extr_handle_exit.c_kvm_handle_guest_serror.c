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
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ arm64_is_fatal_ras_serror (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm64_is_ras_serror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_inject_vabt (struct kvm_vcpu*) ; 

__attribute__((used)) static void kvm_handle_guest_serror(struct kvm_vcpu *vcpu, u32 esr)
{
	if (!arm64_is_ras_serror(esr) || arm64_is_fatal_ras_serror(NULL, esr))
		kvm_inject_vabt(vcpu);
}