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
struct vcpu_vmx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vm_entry_controls_clearbit (struct vcpu_vmx*,unsigned long) ; 
 int /*<<< orphan*/  vm_exit_controls_clearbit (struct vcpu_vmx*,unsigned long) ; 

__attribute__((used)) static void clear_atomic_switch_msr_special(struct vcpu_vmx *vmx,
		unsigned long entry, unsigned long exit)
{
	vm_entry_controls_clearbit(vmx, entry);
	vm_exit_controls_clearbit(vmx, exit);
}