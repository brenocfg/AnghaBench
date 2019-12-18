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
struct TYPE_2__ {int /*<<< orphan*/ * mem; } ;
struct task {struct mm* mm; TYPE_1__ cpu; int /*<<< orphan*/ * mem; } ;
struct mm {int /*<<< orphan*/  mem; } ;

/* Variables and functions */

__attribute__((used)) static inline void task_set_mm(struct task *task, struct mm *mm) {
    task->mm = mm;
    task->mem = task->cpu.mem = &task->mm->mem;
}