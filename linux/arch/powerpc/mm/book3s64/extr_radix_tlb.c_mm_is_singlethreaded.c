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
struct TYPE_3__ {int /*<<< orphan*/  copros; } ;
struct mm_struct {int /*<<< orphan*/  mm_users; TYPE_1__ context; } ;
struct TYPE_4__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_2__* current ; 

__attribute__((used)) static bool mm_is_singlethreaded(struct mm_struct *mm)
{
	if (atomic_read(&mm->context.copros) > 0)
		return false;
	if (atomic_read(&mm->mm_users) <= 1 && current->mm == mm)
		return true;
	return false;
}