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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __entry_task ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,struct task_struct*) ; 

__attribute__((used)) static void entry_task_switch(struct task_struct *next)
{
	__this_cpu_write(__entry_task, next);
}