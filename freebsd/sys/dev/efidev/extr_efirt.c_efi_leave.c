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
struct thread {int dummy; } ;
typedef  int /*<<< orphan*/ * pmap_t ;
struct TYPE_4__ {TYPE_1__* p_vmspace; } ;
struct TYPE_3__ {int /*<<< orphan*/  vm_pmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ *) ; 
 TYPE_2__* curproc ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  efi_arch_leave () ; 
 int /*<<< orphan*/  efi_lock ; 
 int /*<<< orphan*/  fpu_kern_leave (struct thread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
efi_leave(void)
{
	struct thread *td;
	pmap_t curpmap;

	efi_arch_leave();

	curpmap = &curproc->p_vmspace->vm_pmap;
	td = curthread;
	fpu_kern_leave(td, NULL);
	mtx_unlock(&efi_lock);
	PMAP_UNLOCK(curpmap);
}