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
typedef  int u32 ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_3__ {unsigned long* msr_bitmap; } ;
struct TYPE_4__ {TYPE_1__ vmcs01; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_has_vmx_msr_bitmap () ; 
 int /*<<< orphan*/  test_bit (int,unsigned long*) ; 
 TYPE_2__* to_vmx (struct kvm_vcpu*) ; 

__attribute__((used)) static bool msr_write_intercepted_l01(struct kvm_vcpu *vcpu, u32 msr)
{
	unsigned long *msr_bitmap;
	int f = sizeof(unsigned long);

	if (!cpu_has_vmx_msr_bitmap())
		return true;

	msr_bitmap = to_vmx(vcpu)->vmcs01.msr_bitmap;

	if (msr <= 0x1fff) {
		return !!test_bit(msr, msr_bitmap + 0x800 / f);
	} else if ((msr >= 0xc0000000) && (msr <= 0xc0001fff)) {
		msr &= 0x1fff;
		return !!test_bit(msr, msr_bitmap + 0xc00 / f);
	}

	return true;
}