#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rbs_bot; } ;
struct TYPE_6__ {TYPE_2__* mm; TYPE_1__ thread; } ;
struct TYPE_5__ {scalar_t__ start_stack; } ;

/* Variables and functions */
 unsigned long MAX_USER_STACK_SIZE ; 
 int /*<<< orphan*/  PAGE_ALIGN (scalar_t__) ; 
 int /*<<< orphan*/  RLIMIT_STACK ; 
 TYPE_3__* current ; 
 int rlimit_max (int /*<<< orphan*/ ) ; 

inline void
ia64_set_rbs_bot (void)
{
	unsigned long stack_size = rlimit_max(RLIMIT_STACK) & -16;

	if (stack_size > MAX_USER_STACK_SIZE)
		stack_size = MAX_USER_STACK_SIZE;
	current->thread.rbs_bot = PAGE_ALIGN(current->mm->start_stack - stack_size);
}