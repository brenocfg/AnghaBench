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
struct TYPE_4__ {scalar_t__ mask; } ;
struct kvm_s390_gisa_interrupt {int /*<<< orphan*/ * origin; int /*<<< orphan*/  timer; TYPE_2__ alert; } ;
struct TYPE_3__ {struct kvm_s390_gisa_interrupt gisa_int; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_EVENT (int,char*,struct kvm*,scalar_t__) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ gisa_in_alert_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 

void kvm_s390_gisa_destroy(struct kvm *kvm)
{
	struct kvm_s390_gisa_interrupt *gi = &kvm->arch.gisa_int;

	if (!gi->origin)
		return;
	if (gi->alert.mask)
		KVM_EVENT(3, "vm 0x%pK has unexpected iam 0x%02x",
			  kvm, gi->alert.mask);
	while (gisa_in_alert_list(gi->origin))
		cpu_relax();
	hrtimer_cancel(&gi->timer);
	gi->origin = NULL;
}