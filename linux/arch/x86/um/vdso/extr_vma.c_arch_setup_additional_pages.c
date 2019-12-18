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
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct linux_binprm {int dummy; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int VM_EXEC ; 
 int VM_MAYEXEC ; 
 int VM_MAYREAD ; 
 int VM_MAYWRITE ; 
 int VM_READ ; 
 TYPE_1__* current ; 
 scalar_t__ down_write_killable (int /*<<< orphan*/ *) ; 
 int install_special_mapping (struct mm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  um_vdso_addr ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdso_enabled ; 
 int /*<<< orphan*/  vdsop ; 

int arch_setup_additional_pages(struct linux_binprm *bprm, int uses_interp)
{
	int err;
	struct mm_struct *mm = current->mm;

	if (!vdso_enabled)
		return 0;

	if (down_write_killable(&mm->mmap_sem))
		return -EINTR;

	err = install_special_mapping(mm, um_vdso_addr, PAGE_SIZE,
		VM_READ|VM_EXEC|
		VM_MAYREAD|VM_MAYWRITE|VM_MAYEXEC,
		vdsop);

	up_write(&mm->mmap_sem);

	return err;
}