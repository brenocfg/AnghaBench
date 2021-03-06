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
struct task_struct {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 

void release_thread(struct task_struct *dead_task)
{
	WARN_ON(dead_task->mm);
}