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
 unsigned long __get_wchan (struct task_struct*) ; 
 int /*<<< orphan*/  put_task_stack (struct task_struct*) ; 
 int /*<<< orphan*/  try_get_task_stack (struct task_struct*) ; 

unsigned long get_wchan(struct task_struct *p)
{
	unsigned long ret;

	if (!try_get_task_stack(p))
		return 0;

	ret = __get_wchan(p);

	put_task_stack(p);

	return ret;
}