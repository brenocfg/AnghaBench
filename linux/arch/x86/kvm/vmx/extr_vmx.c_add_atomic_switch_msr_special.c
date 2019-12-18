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
struct vcpu_vmx {int dummy; } ;

/* Variables and functions */
 unsigned long HOST_IA32_EFER ; 
 int /*<<< orphan*/  vm_entry_controls_setbit (struct vcpu_vmx*,unsigned long) ; 
 int /*<<< orphan*/  vm_exit_controls_setbit (struct vcpu_vmx*,unsigned long) ; 
 int /*<<< orphan*/  vmcs_write64 (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_atomic_switch_msr_special(struct vcpu_vmx *vmx,
		unsigned long entry, unsigned long exit,
		unsigned long guest_val_vmcs, unsigned long host_val_vmcs,
		u64 guest_val, u64 host_val)
{
	vmcs_write64(guest_val_vmcs, guest_val);
	if (host_val_vmcs != HOST_IA32_EFER)
		vmcs_write64(host_val_vmcs, host_val);
	vm_entry_controls_setbit(vmx, entry);
	vm_exit_controls_setbit(vmx, exit);
}