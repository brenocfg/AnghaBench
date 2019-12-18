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
 struct thread* curthread ; 
 scalar_t__ pmap_map_user_ptr (int /*<<< orphan*/ *,void volatile*,void**,int,int /*<<< orphan*/ *) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 

int
suword(volatile void *addr, long word)
{
	struct		thread *td;
	pmap_t		pm;
	jmp_buf		env;
	long		*p;

	td = curthread;
	pm = &td->td_proc->p_vmspace->vm_pmap;

	td->td_pcb->pcb_onfault = &env;
	if (setjmp(env)) {
		td->td_pcb->pcb_onfault = NULL;
		return (-1);
	}

	if (pmap_map_user_ptr(pm, addr, (void **)&p, sizeof(*p), NULL)) {
		td->td_pcb->pcb_onfault = NULL;
		return (-1);
	}

	*p = word;

	td->td_pcb->pcb_onfault = NULL;
	return (0);
}