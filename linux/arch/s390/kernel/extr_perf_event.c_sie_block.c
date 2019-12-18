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
struct stack_frame {scalar_t__* empty1; } ;
struct pt_regs {scalar_t__* gprs; } ;
struct kvm_s390_sie_block {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct kvm_s390_sie_block *sie_block(struct pt_regs *regs)
{
	struct stack_frame *stack = (struct stack_frame *) regs->gprs[15];

	if (!stack)
		return NULL;

	return (struct kvm_s390_sie_block *) stack->empty1[0];
}