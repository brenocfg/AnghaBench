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
 int /*<<< orphan*/  M_LINUX_CURRENT ; 
 int /*<<< orphan*/  free (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmput (int /*<<< orphan*/ ) ; 

void
linux_free_current(struct task_struct *ts)
{
	mmput(ts->mm);
	free(ts, M_LINUX_CURRENT);
}