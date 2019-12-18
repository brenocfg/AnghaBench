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
struct vm {int maxcpus; int /*<<< orphan*/  cookie; } ;
struct seg_desc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int VMSETDESC (int /*<<< orphan*/ ,int,int,struct seg_desc*) ; 
 int /*<<< orphan*/  is_descriptor_table (int) ; 
 int /*<<< orphan*/  is_segment_register (int) ; 

int
vm_set_seg_desc(struct vm *vm, int vcpu, int reg,
		struct seg_desc *desc)
{
	if (vcpu < 0 || vcpu >= vm->maxcpus)
		return (EINVAL);

	if (!is_segment_register(reg) && !is_descriptor_table(reg))
		return (EINVAL);

	return (VMSETDESC(vm->cookie, vcpu, reg, desc));
}