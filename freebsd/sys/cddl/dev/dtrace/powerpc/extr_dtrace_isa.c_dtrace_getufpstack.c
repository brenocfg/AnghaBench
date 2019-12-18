#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  int uint16_t ;
struct TYPE_9__ {int /*<<< orphan*/ * gregs; } ;
struct TYPE_10__ {int /*<<< orphan*/  uc_link; TYPE_1__ uc_mcontext; } ;
typedef  TYPE_2__ ucontext_t ;
struct xframe {int dummy; } ;
struct trapframe {uintptr_t srr0; uintptr_t* fixreg; } ;
typedef  int /*<<< orphan*/  siginfo_t ;
struct TYPE_11__ {scalar_t__ p_pid; } ;
typedef  TYPE_3__ proc_t ;
typedef  int /*<<< orphan*/  greg_t ;
struct TYPE_14__ {int /*<<< orphan*/  cpuc_dtrace_flags; } ;
struct TYPE_13__ {struct trapframe* td_frame; } ;
struct TYPE_12__ {uintptr_t lwp_oldcontext; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_DTRACE_ENTRY ; 
 int volatile CPU_DTRACE_FAULT ; 
 scalar_t__ DTRACE_CPUFLAG_ISSET (int /*<<< orphan*/ ) ; 
 size_t REG_FP ; 
 size_t REG_PC ; 
 scalar_t__ RETURN_OFFSET ; 
 scalar_t__ RETURN_OFFSET64 ; 
 int /*<<< orphan*/  SV_ILP32 ; 
 scalar_t__ SV_PROC_FLAG (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* cpu_core ; 
 size_t curcpu ; 
 TYPE_3__* curproc ; 
 TYPE_5__* curthread ; 
 uintptr_t dtrace_fulword (int /*<<< orphan*/ *) ; 
 uintptr_t dtrace_fuword32 (void*) ; 
 uintptr_t dtrace_fuword64 (void*) ; 
 TYPE_4__* lwp ; 

void
dtrace_getufpstack(uint64_t *pcstack, uint64_t *fpstack, int pcstack_limit)
{
	proc_t *p = curproc;
	struct trapframe *tf;
	uintptr_t pc, sp;
	volatile uint16_t *flags =
	    (volatile uint16_t *)&cpu_core[curcpu].cpuc_dtrace_flags;
#ifdef notyet	/* XXX signal stack */
	uintptr_t oldcontext;
	size_t s1, s2;
#endif

	if (*flags & CPU_DTRACE_FAULT)
		return;

	if (pcstack_limit <= 0)
		return;

	/*
	 * If there's no user context we still need to zero the stack.
	 */
	if (p == NULL || (tf = curthread->td_frame) == NULL)
		goto zero;

	*pcstack++ = (uint64_t)p->p_pid;
	pcstack_limit--;

	if (pcstack_limit <= 0)
		return;

	pc = tf->srr0;
	sp = tf->fixreg[1];

#ifdef notyet /* XXX signal stack */
	oldcontext = lwp->lwp_oldcontext;
	s1 = sizeof (struct xframe) + 2 * sizeof (long);
	s2 = s1 + sizeof (siginfo_t);
#endif

	if (DTRACE_CPUFLAG_ISSET(CPU_DTRACE_ENTRY)) {
		*pcstack++ = (uint64_t)pc;
		*fpstack++ = 0;
		pcstack_limit--;
		if (pcstack_limit <= 0)
			return;

		if (SV_PROC_FLAG(p, SV_ILP32)) {
			pc = dtrace_fuword32((void *)sp);
		}
		else {
			pc = dtrace_fuword64((void *)sp);
		}
	}

	while (pc != 0) {
		*pcstack++ = (uint64_t)pc;
		*fpstack++ = sp;
		pcstack_limit--;
		if (pcstack_limit <= 0)
			break;

		if (sp == 0)
			break;

#ifdef notyet /* XXX signal stack */
		if (oldcontext == sp + s1 || oldcontext == sp + s2) {
			ucontext_t *ucp = (ucontext_t *)oldcontext;
			greg_t *gregs = ucp->uc_mcontext.gregs;

			sp = dtrace_fulword(&gregs[REG_FP]);
			pc = dtrace_fulword(&gregs[REG_PC]);

			oldcontext = dtrace_fulword(&ucp->uc_link);
		} else
#endif /* XXX */
		{
			if (SV_PROC_FLAG(p, SV_ILP32)) {
				pc = dtrace_fuword32((void *)(sp + RETURN_OFFSET));
				sp = dtrace_fuword32((void *)sp);
			}
			else {
				pc = dtrace_fuword64((void *)(sp + RETURN_OFFSET64));
				sp = dtrace_fuword64((void *)sp);
			}
		}

		/*
		 * This is totally bogus:  if we faulted, we're going to clear
		 * the fault and break.  This is to deal with the apparently
		 * broken Java stacks on x86.
		 */
		if (*flags & CPU_DTRACE_FAULT) {
			*flags &= ~CPU_DTRACE_FAULT;
			break;
		}
	}

zero:
	while (pcstack_limit-- > 0)
		*pcstack++ = 0;
}