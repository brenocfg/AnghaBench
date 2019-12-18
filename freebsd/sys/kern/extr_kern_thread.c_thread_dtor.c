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
struct thread {int td_state; int /*<<< orphan*/  td_tid; int /*<<< orphan*/ * td_su; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DIRECT_INVOKE (void (*) (void*,int,void*),struct thread*) ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
#define  TDS_CAN_RUN 132 
#define  TDS_INACTIVE 131 
#define  TDS_INHIBITED 130 
#define  TDS_RUNNING 129 
#define  TDS_RUNQ 128 
 int /*<<< orphan*/  audit_thread_free (struct thread*) ; 
 int /*<<< orphan*/  osd_thread_exit (struct thread*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  td_softdep_cleanup (struct thread*) ; 
 int /*<<< orphan*/  tid_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
thread_dtor(void *mem, int size, void *arg)
{
	struct thread *td;

	td = (struct thread *)mem;

#ifdef INVARIANTS
	/* Verify that this thread is in a safe state to free. */
	switch (td->td_state) {
	case TDS_INHIBITED:
	case TDS_RUNNING:
	case TDS_CAN_RUN:
	case TDS_RUNQ:
		/*
		 * We must never unlink a thread that is in one of
		 * these states, because it is currently active.
		 */
		panic("bad state for thread unlinking");
		/* NOTREACHED */
	case TDS_INACTIVE:
		break;
	default:
		panic("bad thread state");
		/* NOTREACHED */
	}
#endif
#ifdef AUDIT
	audit_thread_free(td);
#endif
	/* Free all OSD associated to this thread. */
	osd_thread_exit(td);
	td_softdep_cleanup(td);
	MPASS(td->td_su == NULL);

	EVENTHANDLER_DIRECT_INVOKE(thread_dtor, td);
	tid_free(td->td_tid);
}