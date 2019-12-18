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
struct kvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_MCLOCK_INPROGRESS ; 
 int /*<<< orphan*/  kvm_make_all_cpus_request (struct kvm*,int /*<<< orphan*/ ) ; 

void kvm_make_mclock_inprogress_request(struct kvm *kvm)
{
	kvm_make_all_cpus_request(kvm, KVM_REQ_MCLOCK_INPROGRESS);
}