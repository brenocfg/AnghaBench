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
struct task_struct {struct mm_struct* mm; } ;
struct mm_struct {int /*<<< orphan*/  mm_users; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

struct mm_struct *
linux_get_task_mm(struct task_struct *task)
{
	struct mm_struct *mm;

	mm = task->mm;
	if (mm != NULL) {
		atomic_inc(&mm->mm_users);
		return (mm);
	}
	return (NULL);
}