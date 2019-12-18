#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct thread {int p_numthreads; int /*<<< orphan*/ * p_ksi; int /*<<< orphan*/ * td_su; int /*<<< orphan*/  p_ktr; } ;
struct proc {int p_numthreads; int /*<<< orphan*/ * p_ksi; int /*<<< orphan*/ * td_su; int /*<<< orphan*/  p_ktr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DIRECT_INVOKE (int /*<<< orphan*/ ,struct thread*) ; 
 struct thread* FIRST_THREAD_IN_PROC (struct thread*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KSI_ONQ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 int STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osd_thread_exit (struct thread*) ; 
 int /*<<< orphan*/  process_dtor ; 
 int /*<<< orphan*/  td_softdep_cleanup (struct thread*) ; 
 int /*<<< orphan*/  thread_dtor ; 

__attribute__((used)) static void
proc_dtor(void *mem, int size, void *arg)
{
	struct proc *p;
	struct thread *td;

	/* INVARIANTS checks go here */
	p = (struct proc *)mem;
	td = FIRST_THREAD_IN_PROC(p);
	if (td != NULL) {
#ifdef INVARIANTS
		KASSERT((p->p_numthreads == 1),
		    ("bad number of threads in exiting process"));
		KASSERT(STAILQ_EMPTY(&p->p_ktr), ("proc_dtor: non-empty p_ktr"));
#endif
		/* Free all OSD associated to this thread. */
		osd_thread_exit(td);
		td_softdep_cleanup(td);
		MPASS(td->td_su == NULL);

		/* Make sure all thread destructors are executed */
		EVENTHANDLER_DIRECT_INVOKE(thread_dtor, td);
	}
	EVENTHANDLER_DIRECT_INVOKE(process_dtor, p);
	if (p->p_ksi != NULL)
		KASSERT(! KSI_ONQ(p->p_ksi), ("SIGCHLD queue"));
}