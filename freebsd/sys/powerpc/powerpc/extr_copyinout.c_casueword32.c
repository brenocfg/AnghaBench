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
typedef  int /*<<< orphan*/  uint32_t ;
struct thread {TYPE_3__* td_pcb; TYPE_2__* td_proc; } ;
typedef  int /*<<< orphan*/ * pmap_t ;
typedef  int /*<<< orphan*/  jmp_buf ;
struct TYPE_6__ {int /*<<< orphan*/ * pcb_onfault; } ;
struct TYPE_5__ {TYPE_1__* p_vmspace; } ;
struct TYPE_4__ {int /*<<< orphan*/  vm_pmap; } ;

/* Variables and functions */
 struct thread* curthread ; 
 scalar_t__ pmap_map_user_ptr (int /*<<< orphan*/ *,void*,void**,int,int /*<<< orphan*/ *) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 

int
casueword32(volatile uint32_t *addr, uint32_t old, uint32_t *oldvalp,
    uint32_t new)
{
	struct thread *td;
	pmap_t pm;
	jmp_buf		env;
	uint32_t *p, val;
	int res;

	td = curthread;
	pm = &td->td_proc->p_vmspace->vm_pmap;

	td->td_pcb->pcb_onfault = &env;
	if (setjmp(env)) {
		td->td_pcb->pcb_onfault = NULL;
		return (-1);
	}

	if (pmap_map_user_ptr(pm, (void *)(uintptr_t)addr, (void **)&p,
	    sizeof(*p), NULL)) {
		td->td_pcb->pcb_onfault = NULL;
		return (-1);
	}

	res = 0;
	__asm __volatile (
		"lwarx %0, 0, %3\n\t"		/* load old value */
		"cmplw %4, %0\n\t"		/* compare */
		"bne 1f\n\t"			/* exit if not equal */
		"stwcx. %5, 0, %3\n\t"      	/* attempt to store */
		"bne- 2f\n\t"			/* if failed */
		"b 3f\n\t"			/* we've succeeded */
		"1:\n\t"
		"stwcx. %0, 0, %3\n\t"       	/* clear reservation (74xx) */
		"2:li %2, 1\n\t"
		"3:\n\t"
		: "=&r" (val), "=m" (*p), "+&r" (res)
		: "r" (p), "r" (old), "r" (new), "m" (*p)
		: "cr0", "memory");

	td->td_pcb->pcb_onfault = NULL;

	*oldvalp = val;
	return (res);
}