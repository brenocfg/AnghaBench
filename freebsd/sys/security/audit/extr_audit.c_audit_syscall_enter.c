#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct thread {int td_pflags; TYPE_6__* td_ar; TYPE_5__* td_ucred; TYPE_3__* td_proc; } ;
struct au_mask {int dummy; } ;
typedef  scalar_t__ au_id_t ;
typedef  scalar_t__ au_event_t ;
typedef  int /*<<< orphan*/  au_class_t ;
struct TYPE_12__ {void* k_dtaudit_state; } ;
struct TYPE_10__ {scalar_t__ ai_auid; struct au_mask ai_mask; } ;
struct TYPE_11__ {TYPE_4__ cr_audit; } ;
struct TYPE_9__ {TYPE_2__* p_sysent; } ;
struct TYPE_8__ {unsigned short sv_size; TYPE_1__* sv_table; } ;
struct TYPE_7__ {scalar_t__ sy_auevent; } ;

/* Variables and functions */
 scalar_t__ AUE_NULL ; 
 scalar_t__ AU_DEFAUDITID ; 
 int /*<<< orphan*/  AU_PRS_BOTH ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PRIV_AUDIT_FAILSTOP ; 
 int TDP_AUDITREC ; 
 int /*<<< orphan*/  au_event_class (scalar_t__) ; 
 scalar_t__ au_preselect (scalar_t__,int /*<<< orphan*/ ,struct au_mask*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_fail_cv ; 
 scalar_t__ audit_in_failure ; 
 int /*<<< orphan*/  audit_mtx ; 
 struct au_mask audit_nae_mask ; 
 TYPE_6__* audit_new (scalar_t__,struct thread*) ; 
 scalar_t__ audit_pipe_preselect (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* dtaudit_hook_preselect (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ priv_check (struct thread*,int /*<<< orphan*/ ) ; 

void
audit_syscall_enter(unsigned short code, struct thread *td)
{
	struct au_mask *aumask;
#ifdef KDTRACE_HOOKS
	void *dtaudit_state;
#endif
	au_class_t class;
	au_event_t event;
	au_id_t auid;
	int record_needed;

	KASSERT(td->td_ar == NULL, ("audit_syscall_enter: td->td_ar != NULL"));
	KASSERT((td->td_pflags & TDP_AUDITREC) == 0,
	    ("audit_syscall_enter: TDP_AUDITREC set"));

	/*
	 * In FreeBSD, each ABI has its own system call table, and hence
	 * mapping of system call codes to audit events.  Convert the code to
	 * an audit event identifier using the process system call table
	 * reference.  In Darwin, there's only one, so we use the global
	 * symbol for the system call table.  No audit record is generated
	 * for bad system calls, as no operation has been performed.
	 */
	if (code >= td->td_proc->p_sysent->sv_size)
		return;

	event = td->td_proc->p_sysent->sv_table[code].sy_auevent;
	if (event == AUE_NULL)
		return;

	/*
	 * Check which audit mask to use; either the kernel non-attributable
	 * event mask or the process audit mask.
	 */
	auid = td->td_ucred->cr_audit.ai_auid;
	if (auid == AU_DEFAUDITID)
		aumask = &audit_nae_mask;
	else
		aumask = &td->td_ucred->cr_audit.ai_mask;

	/*
	 * Determine whether trail or pipe preselection would like an audit
	 * record allocated for this system call.
	 */
	class = au_event_class(event);
	if (au_preselect(event, class, aumask, AU_PRS_BOTH)) {
		/*
		 * If we're out of space and need to suspend unprivileged
		 * processes, do that here rather than trying to allocate
		 * another audit record.
		 *
		 * Note: we might wish to be able to continue here in the
		 * future, if the system recovers.  That should be possible
		 * by means of checking the condition in a loop around
		 * cv_wait().  It might be desirable to reevaluate whether an
		 * audit record is still required for this event by
		 * re-calling au_preselect().
		 */
		if (audit_in_failure &&
		    priv_check(td, PRIV_AUDIT_FAILSTOP) != 0) {
			cv_wait(&audit_fail_cv, &audit_mtx);
			panic("audit_failing_stop: thread continued");
		}
		record_needed = 1;
	} else if (audit_pipe_preselect(auid, event, class, AU_PRS_BOTH, 0)) {
		record_needed = 1;
	} else {
		record_needed = 0;
	}

	/*
	 * After audit trails and pipes have made their policy choices, DTrace
	 * may request that records be generated as well.  This is a slightly
	 * complex affair, as the DTrace audit provider needs the audit
	 * framework to maintain some state on the audit record, which has not
	 * been allocated at the point where the decision has to be made.
	 * This hook must run even if we are not changing the decision, as
	 * DTrace may want to stick event state onto a record we were going to
	 * produce due to the trail or pipes.  The event state returned by the
	 * DTrace provider must be safe without locks held between here and
	 * below -- i.e., dtaudit_state must must refer to stable memory.
	 */
#ifdef KDTRACE_HOOKS
	dtaudit_state = NULL;
        if (dtaudit_hook_preselect != NULL) {
		dtaudit_state = dtaudit_hook_preselect(auid, event, class);
		if (dtaudit_state != NULL)
			record_needed = 1;
	}
#endif

	/*
	 * If a record is required, allocate it and attach it to the thread
	 * for use throughout the system call.  Also attach DTrace state if
	 * required.
	 *
	 * XXXRW: If we decide to reference count the evname_elem underlying
	 * dtaudit_state, we will need to free here if no record is allocated
	 * or allocatable.
	 */
	if (record_needed) {
		td->td_ar = audit_new(event, td);
		if (td->td_ar != NULL) {
			td->td_pflags |= TDP_AUDITREC;
#ifdef KDTRACE_HOOKS
			td->td_ar->k_dtaudit_state = dtaudit_state;
#endif
		}
	} else
		td->td_ar = NULL;
}