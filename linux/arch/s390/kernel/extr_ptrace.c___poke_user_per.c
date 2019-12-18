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
struct TYPE_3__ {scalar_t__ end; scalar_t__ start; scalar_t__ control; } ;
struct TYPE_4__ {TYPE_1__ per_user; } ;
struct task_struct {TYPE_2__ thread; } ;
struct per_struct_kernel {int /*<<< orphan*/  ending_addr; int /*<<< orphan*/  starting_addr; int /*<<< orphan*/  cr9; } ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */
 scalar_t__ PER_CONTROL_MASK ; 
 scalar_t__ PER_EVENT_MASK ; 

__attribute__((used)) static inline void __poke_user_per(struct task_struct *child,
				   addr_t addr, addr_t data)
{
	struct per_struct_kernel *dummy = NULL;

	/*
	 * There are only three fields in the per_info struct that the
	 * debugger user can write to.
	 * 1) cr9: the debugger wants to set a new PER event mask
	 * 2) starting_addr: the debugger wants to set a new starting
	 *    address to use with the PER event mask.
	 * 3) ending_addr: the debugger wants to set a new ending
	 *    address to use with the PER event mask.
	 * The user specified PER event mask and the start and end
	 * addresses are used only if single stepping is not in effect.
	 * Writes to any other field in per_info are ignored.
	 */
	if (addr == (addr_t) &dummy->cr9)
		/* PER event mask of the user specified per set. */
		child->thread.per_user.control =
			data & (PER_EVENT_MASK | PER_CONTROL_MASK);
	else if (addr == (addr_t) &dummy->starting_addr)
		/* Starting address of the user specified per set. */
		child->thread.per_user.start = data;
	else if (addr == (addr_t) &dummy->ending_addr)
		/* Ending address of the user specified per set. */
		child->thread.per_user.end = data;
}