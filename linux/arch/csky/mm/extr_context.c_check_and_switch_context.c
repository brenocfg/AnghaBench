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
struct TYPE_2__ {int /*<<< orphan*/  asid; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  asid_check_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,struct mm_struct*) ; 
 int /*<<< orphan*/  asid_info ; 

void check_and_switch_context(struct mm_struct *mm, unsigned int cpu)
{
	asid_check_context(&asid_info, &mm->context.asid, cpu, mm);
}