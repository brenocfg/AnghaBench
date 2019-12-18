#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
struct kernel_vm86_regs {TYPE_3__ pt; } ;
struct TYPE_6__ {TYPE_1__* vm86; } ;
struct TYPE_8__ {TYPE_2__ thread; } ;
struct TYPE_5__ {int /*<<< orphan*/  veflags_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAFE_MASK ; 
 int /*<<< orphan*/  VEFLAGS ; 
 unsigned long X86_EFLAGS_IF ; 
 int /*<<< orphan*/  clear_IF (struct kernel_vm86_regs*) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  set_IF (struct kernel_vm86_regs*) ; 
 int /*<<< orphan*/  set_flags (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_vflags_long(unsigned long flags, struct kernel_vm86_regs *regs)
{
	set_flags(VEFLAGS, flags, current->thread.vm86->veflags_mask);
	set_flags(regs->pt.flags, flags, SAFE_MASK);
	if (flags & X86_EFLAGS_IF)
		set_IF(regs);
	else
		clear_IF(regs);
}