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
struct stack_info {int dummy; } ;
struct pt_regs {int dummy; } ;
struct TYPE_2__ {unsigned long restart_stack; } ;

/* Variables and functions */
 TYPE_1__ S390_lowcore ; 
 int STACK_FRAME_OVERHEAD ; 
 int /*<<< orphan*/  STACK_TYPE_RESTART ; 
 scalar_t__ THREAD_SIZE ; 
 int in_stack (unsigned long,struct stack_info*,int /*<<< orphan*/ ,scalar_t__,unsigned long) ; 

__attribute__((used)) static bool in_restart_stack(unsigned long sp, struct stack_info *info)
{
	unsigned long frame_size, top;

	frame_size = STACK_FRAME_OVERHEAD + sizeof(struct pt_regs);
	top = S390_lowcore.restart_stack + frame_size;
	return in_stack(sp, info, STACK_TYPE_RESTART, top - THREAD_SIZE, top);
}