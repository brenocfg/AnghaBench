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
struct thread_info {struct thread_info* real_thread; } ;
struct TYPE_2__ {struct thread_info* stack; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 struct thread_info* current_thread_info () ; 
 int pending_mask ; 
 unsigned long xchg (int*,int /*<<< orphan*/ ) ; 

unsigned long from_irq_stack(int nested)
{
	struct thread_info *ti, *to;
	unsigned long mask;

	ti = current_thread_info();

	pending_mask = 1;

	to = ti->real_thread;
	current->stack = to;
	ti->real_thread = NULL;
	*to = *ti;

	mask = xchg(&pending_mask, 0);
	return mask & ~1;
}