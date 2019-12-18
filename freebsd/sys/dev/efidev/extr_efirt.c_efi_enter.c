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
struct thread {TYPE_2__* td_proc; } ;
typedef  int /*<<< orphan*/ * pmap_t ;
struct TYPE_4__ {TYPE_1__* p_vmspace; } ;
struct TYPE_3__ {int /*<<< orphan*/  vm_pmap; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  FPU_KERN_NOCTX ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ *) ; 
 struct thread* curthread ; 
 int efi_arch_enter () ; 
 int /*<<< orphan*/  efi_lock ; 
 int /*<<< orphan*/ * efi_runtime ; 
 int /*<<< orphan*/  fpu_kern_enter (struct thread*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpu_kern_leave (struct thread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
efi_enter(void)
{
	struct thread *td;
	pmap_t curpmap;
	int error;

	if (efi_runtime == NULL)
		return (ENXIO);
	td = curthread;
	curpmap = &td->td_proc->p_vmspace->vm_pmap;
	PMAP_LOCK(curpmap);
	mtx_lock(&efi_lock);
	fpu_kern_enter(td, NULL, FPU_KERN_NOCTX);
	error = efi_arch_enter();
	if (error != 0) {
		fpu_kern_leave(td, NULL);
		mtx_unlock(&efi_lock);
		PMAP_UNLOCK(curpmap);
	}
	return (error);
}