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
struct mm_struct {int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  mm_context_t ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  flush_tlb_pid (unsigned long) ; 
 unsigned long get_pid_from_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void flush_tlb_mm(struct mm_struct *mm)
{
	if (current->mm == mm) {
		unsigned long mmu_pid = get_pid_from_context(&mm->context);
		flush_tlb_pid(mmu_pid);
	} else {
		memset(&mm->context, 0, sizeof(mm_context_t));
	}
}