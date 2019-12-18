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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  X86_CR4_VMXE ; 
 int /*<<< orphan*/  cr4_set_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_pt_handle_vmx (int) ; 

__attribute__((used)) static void kvm_cpu_vmxon(u64 addr)
{
	cr4_set_bits(X86_CR4_VMXE);
	intel_pt_handle_vmx(1);

	asm volatile ("vmxon %0" : : "m"(addr));
}