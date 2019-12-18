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
struct vcpu_info {int /*<<< orphan*/  evtchn_upcall_mask; } ;

/* Variables and functions */
 unsigned long X86_EFLAGS_IF ; 
 struct vcpu_info* this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_vcpu ; 

unsigned long xen_save_fl(void)
{
	struct vcpu_info *vcpu;
	unsigned long flags;

	vcpu = this_cpu_read(xen_vcpu);

	/* flag has opposite sense of mask */
	flags = !vcpu->evtchn_upcall_mask;

	/* convert to IF type flag
	   -0 -> 0x00000000
	   -1 -> 0xffffffff
	*/
	return (-flags) & X86_EFLAGS_IF;
}