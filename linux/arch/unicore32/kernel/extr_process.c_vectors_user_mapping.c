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
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int VM_DONTDUMP ; 
 int VM_DONTEXPAND ; 
 int VM_EXEC ; 
 int VM_MAYEXEC ; 
 int VM_MAYREAD ; 
 int VM_READ ; 
 TYPE_1__* current ; 
 int install_special_mapping (struct mm_struct*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int vectors_user_mapping(void)
{
	struct mm_struct *mm = current->mm;
	return install_special_mapping(mm, 0xffff0000, PAGE_SIZE,
				       VM_READ | VM_EXEC |
				       VM_MAYREAD | VM_MAYEXEC |
				       VM_DONTEXPAND | VM_DONTDUMP,
				       NULL);
}