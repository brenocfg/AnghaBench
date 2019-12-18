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
struct kvm_s390_gisa_interrupt {int /*<<< orphan*/  origin; } ;
struct TYPE_2__ {struct kvm_s390_gisa_interrupt gisa_int; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_EVENT (struct kvm*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gisa_clear_ipm (int /*<<< orphan*/ ) ; 

void kvm_s390_gisa_clear(struct kvm *kvm)
{
	struct kvm_s390_gisa_interrupt *gi = &kvm->arch.gisa_int;

	if (!gi->origin)
		return;
	gisa_clear_ipm(gi->origin);
	VM_EVENT(kvm, 3, "gisa 0x%pK cleared", gi->origin);
}