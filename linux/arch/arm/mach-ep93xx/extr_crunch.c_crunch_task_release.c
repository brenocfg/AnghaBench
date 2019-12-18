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
struct thread_info {int /*<<< orphan*/  crunchstate; } ;

/* Variables and functions */
 int /*<<< orphan*/ * crunch_owner ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 

void crunch_task_release(struct thread_info *thread)
{
	local_irq_disable();
	if (crunch_owner == &thread->crunchstate)
		crunch_owner = NULL;
	local_irq_enable();
}