#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct thread {TYPE_3__* td_pcb; TYPE_2__* td_proc; } ;
typedef  int /*<<< orphan*/ * pmap_t ;
typedef  int /*<<< orphan*/  jmp_buf ;
struct TYPE_6__ {int /*<<< orphan*/ * pcb_onfault; } ;
struct TYPE_5__ {TYPE_1__* p_vmspace; } ;
struct TYPE_4__ {int /*<<< orphan*/  vm_pmap; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  bcopy (char*,char*,size_t) ; 
 struct thread* curthread ; 
 scalar_t__ pmap_map_user_ptr (int /*<<< orphan*/ *,char const*,void**,size_t,size_t*) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 

int
copyin(const void *udaddr, void *kaddr, size_t len)
{
	struct		thread *td;
	pmap_t		pm;
	jmp_buf		env;
	const char	*up;
	char		*kp, *p;
	size_t		l;

	td = curthread;
	pm = &td->td_proc->p_vmspace->vm_pmap;

	td->td_pcb->pcb_onfault = &env;
	if (setjmp(env)) {
		td->td_pcb->pcb_onfault = NULL;
		return (EFAULT);
	}

	kp = kaddr;
	up = udaddr;

	while (len > 0) {
		if (pmap_map_user_ptr(pm, up, (void **)&p, len, &l)) {
			td->td_pcb->pcb_onfault = NULL;
			return (EFAULT);
		}

		bcopy(p, kp, l);

		up += l;
		kp += l;
		len -= l;
	}

	td->td_pcb->pcb_onfault = NULL;
	return (0);
}