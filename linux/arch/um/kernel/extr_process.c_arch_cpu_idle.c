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
struct TYPE_4__ {int /*<<< orphan*/  pid; } ;
struct TYPE_3__ {size_t cpu; } ;

/* Variables and functions */
 TYPE_2__* cpu_tasks ; 
 TYPE_1__* current_thread_info () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  os_getpid () ; 
 int /*<<< orphan*/  um_idle_sleep () ; 

void arch_cpu_idle(void)
{
	cpu_tasks[current_thread_info()->cpu].pid = os_getpid();
	um_idle_sleep();
	local_irq_enable();
}