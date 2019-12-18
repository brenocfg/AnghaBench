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
typedef  scalar_t__ u32 ;
struct vmcs12 {scalar_t__ msr_bitmap; } ;
struct kvm_vcpu {int dummy; } ;
typedef  scalar_t__ gpa_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_BASED_USE_MSR_BITMAPS ; 
 scalar_t__ EXIT_REASON_MSR_WRITE ; 
 scalar_t__ kvm_rcx_read (struct kvm_vcpu*) ; 
 scalar_t__ kvm_vcpu_read_guest (struct kvm_vcpu*,scalar_t__,unsigned char*,int) ; 
 int /*<<< orphan*/  nested_cpu_has (struct vmcs12*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nested_vmx_exit_handled_msr(struct kvm_vcpu *vcpu,
	struct vmcs12 *vmcs12, u32 exit_reason)
{
	u32 msr_index = kvm_rcx_read(vcpu);
	gpa_t bitmap;

	if (!nested_cpu_has(vmcs12, CPU_BASED_USE_MSR_BITMAPS))
		return true;

	/*
	 * The MSR_BITMAP page is divided into four 1024-byte bitmaps,
	 * for the four combinations of read/write and low/high MSR numbers.
	 * First we need to figure out which of the four to use:
	 */
	bitmap = vmcs12->msr_bitmap;
	if (exit_reason == EXIT_REASON_MSR_WRITE)
		bitmap += 2048;
	if (msr_index >= 0xc0000000) {
		msr_index -= 0xc0000000;
		bitmap += 1024;
	}

	/* Then read the msr_index'th bit from this bitmap: */
	if (msr_index < 1024*8) {
		unsigned char b;
		if (kvm_vcpu_read_guest(vcpu, bitmap + msr_index/8, &b, 1))
			return true;
		return 1 & (b >> (msr_index & 7));
	} else
		return true; /* let L1 handle the wrong parameter */
}