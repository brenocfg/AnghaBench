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
struct TYPE_2__ {int flags; } ;
struct vmspace {TYPE_1__ vm_map; } ;
struct thread {int dummy; } ;
struct proc {int p_flag2; int p_flag; } ;

/* Variables and functions */
 int MAP_ASLR ; 
#define  P2_ASLR_DISABLE 129 
#define  P2_ASLR_ENABLE 128 
 int PROC_ASLR_ACTIVE ; 
 int PROC_ASLR_FORCE_DISABLE ; 
 int PROC_ASLR_FORCE_ENABLE ; 
 int PROC_ASLR_NOFORCE ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int P_WEXIT ; 
 int /*<<< orphan*/  _PHOLD (struct proc*) ; 
 int /*<<< orphan*/  _PRELE (struct proc*) ; 
 struct vmspace* vmspace_acquire_ref (struct proc*) ; 
 int /*<<< orphan*/  vmspace_free (struct vmspace*) ; 

__attribute__((used)) static int
aslr_status(struct thread *td, struct proc *p, int *data)
{
	struct vmspace *vm;
	int d;

	switch (p->p_flag2 & (P2_ASLR_ENABLE | P2_ASLR_DISABLE)) {
	case 0:
		d = PROC_ASLR_NOFORCE;
		break;
	case P2_ASLR_ENABLE:
		d = PROC_ASLR_FORCE_ENABLE;
		break;
	case P2_ASLR_DISABLE:
		d = PROC_ASLR_FORCE_DISABLE;
		break;
	}
	if ((p->p_flag & P_WEXIT) == 0) {
		_PHOLD(p);
		PROC_UNLOCK(p);
		vm = vmspace_acquire_ref(p);
		if (vm != NULL && (vm->vm_map.flags & MAP_ASLR) != 0) {
			d |= PROC_ASLR_ACTIVE;
			vmspace_free(vm);
		}
		PROC_LOCK(p);
		_PRELE(p);
	}
	*data = d;
	return (0);
}