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
struct mm_struct {int dummy; } ;
struct TYPE_2__ {struct mm_struct* active_mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  __tlb_flush_local () ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  set_user_asce (struct mm_struct*) ; 

__attribute__((used)) static void __crst_table_upgrade(void *arg)
{
	struct mm_struct *mm = arg;

	if (current->active_mm == mm)
		set_user_asce(mm);
	__tlb_flush_local();
}