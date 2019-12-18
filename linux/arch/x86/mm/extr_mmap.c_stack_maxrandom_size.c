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
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int PF_RANDOMIZE ; 
 unsigned long __STACK_RND_MASK (int) ; 
 TYPE_1__* current ; 
 unsigned long task_size_32bit () ; 

__attribute__((used)) static unsigned long stack_maxrandom_size(unsigned long task_size)
{
	unsigned long max = 0;
	if (current->flags & PF_RANDOMIZE) {
		max = (-1UL) & __STACK_RND_MASK(task_size == task_size_32bit());
		max <<= PAGE_SHIFT;
	}

	return max;
}