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
struct au_mask {int dummy; } ;
struct TYPE_3__ {int ar_errno; int ar_retval; scalar_t__ ar_subj_auid; int ar_event; int /*<<< orphan*/  ar_arg_svipc_which; int /*<<< orphan*/  ar_arg_cmd; int /*<<< orphan*/  ar_valid_arg; int /*<<< orphan*/  ar_arg_ctlname; int /*<<< orphan*/  ar_arg_fflags; struct au_mask ar_subj_amask; int /*<<< orphan*/  ar_endtime; } ;
struct kaudit_record {int k_ar_commit; TYPE_1__ k_ar; } ;
typedef  scalar_t__ au_id_t ;
typedef  int au_event_t ;
typedef  int /*<<< orphan*/  au_class_t ;
struct TYPE_4__ {scalar_t__ aq_hiwater; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_IS_VALID (struct kaudit_record*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARG_SVIPC_WHICH ; 
 int AR_COMMIT_KERNEL ; 
 int AR_PRESELECT_DTRACE ; 
 int AR_PRESELECT_PIPE ; 
 int AR_PRESELECT_TRAIL ; 
 int AR_PRESELECT_USER_PIPE ; 
 int AR_PRESELECT_USER_TRAIL ; 
#define  AUE_AUDITON 134 
#define  AUE_MSGSYS 133 
#define  AUE_OPENAT_RWTC 132 
#define  AUE_OPEN_RWTC 131 
#define  AUE_SEMSYS 130 
#define  AUE_SHMSYS 129 
#define  AUE_SYSCTL 128 
 scalar_t__ AU_DEFAUDITID ; 
 int AU_PRS_FAILURE ; 
 int AU_PRS_SUCCESS ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct kaudit_record*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_event_class (int) ; 
 scalar_t__ au_preselect (int,int /*<<< orphan*/ ,struct au_mask*,int) ; 
 int audit_ctlname_to_sysctlevent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int audit_flags_and_error_to_openatevent (int /*<<< orphan*/ ,int) ; 
 int audit_flags_and_error_to_openevent (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  audit_free (struct kaudit_record*) ; 
 int audit_msgsys_to_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_mtx ; 
 struct au_mask audit_nae_mask ; 
 scalar_t__ audit_pipe_preselect (scalar_t__,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  audit_pre_q_len ; 
 int /*<<< orphan*/  audit_q ; 
 scalar_t__ audit_q_len ; 
 TYPE_2__ audit_qctrl ; 
 int audit_semsys_to_event (int /*<<< orphan*/ ) ; 
 int audit_shmsys_to_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_trail_enabled ; 
 scalar_t__ audit_trail_suspended ; 
 int /*<<< orphan*/  audit_watermark_cv ; 
 int /*<<< orphan*/  audit_worker_cv ; 
 int auditon_command_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dtaudit_hook_commit (struct kaudit_record*,scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  k_q ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nanotime (int /*<<< orphan*/ *) ; 

void
audit_commit(struct kaudit_record *ar, int error, int retval)
{
	au_event_t event;
	au_class_t class;
	au_id_t auid;
	int sorf;
	struct au_mask *aumask;

	if (ar == NULL)
		return;

	ar->k_ar.ar_errno = error;
	ar->k_ar.ar_retval = retval;
	nanotime(&ar->k_ar.ar_endtime);

	/*
	 * Decide whether to commit the audit record by checking the error
	 * value from the system call and using the appropriate audit mask.
	 */
	if (ar->k_ar.ar_subj_auid == AU_DEFAUDITID)
		aumask = &audit_nae_mask;
	else
		aumask = &ar->k_ar.ar_subj_amask;

	if (error)
		sorf = AU_PRS_FAILURE;
	else
		sorf = AU_PRS_SUCCESS;

	/*
	 * syscalls.master sometimes contains a prototype event number, which
	 * we will transform into a more specific event number now that we
	 * have more complete information gathered during the system call.
	 */
	switch(ar->k_ar.ar_event) {
	case AUE_OPEN_RWTC:
		ar->k_ar.ar_event = audit_flags_and_error_to_openevent(
		    ar->k_ar.ar_arg_fflags, error);
		break;

	case AUE_OPENAT_RWTC:
		ar->k_ar.ar_event = audit_flags_and_error_to_openatevent(
		    ar->k_ar.ar_arg_fflags, error);
		break;

	case AUE_SYSCTL:
		ar->k_ar.ar_event = audit_ctlname_to_sysctlevent(
		    ar->k_ar.ar_arg_ctlname, ar->k_ar.ar_valid_arg);
		break;

	case AUE_AUDITON:
		/* Convert the auditon() command to an event. */
		ar->k_ar.ar_event = auditon_command_event(ar->k_ar.ar_arg_cmd);
		break;

	case AUE_MSGSYS:
		if (ARG_IS_VALID(ar, ARG_SVIPC_WHICH))
			ar->k_ar.ar_event =
			    audit_msgsys_to_event(ar->k_ar.ar_arg_svipc_which);
		break;

	case AUE_SEMSYS:
		if (ARG_IS_VALID(ar, ARG_SVIPC_WHICH))
			ar->k_ar.ar_event =
			    audit_semsys_to_event(ar->k_ar.ar_arg_svipc_which);
		break;

	case AUE_SHMSYS:
		if (ARG_IS_VALID(ar, ARG_SVIPC_WHICH))
			ar->k_ar.ar_event =
			    audit_shmsys_to_event(ar->k_ar.ar_arg_svipc_which);
		break;
	}

	auid = ar->k_ar.ar_subj_auid;
	event = ar->k_ar.ar_event;
	class = au_event_class(event);

	ar->k_ar_commit |= AR_COMMIT_KERNEL;
	if (au_preselect(event, class, aumask, sorf) != 0)
		ar->k_ar_commit |= AR_PRESELECT_TRAIL;
	if (audit_pipe_preselect(auid, event, class, sorf,
	    ar->k_ar_commit & AR_PRESELECT_TRAIL) != 0)
		ar->k_ar_commit |= AR_PRESELECT_PIPE;
#ifdef KDTRACE_HOOKS
	/*
	 * Expose the audit record to DTrace, both to allow the "commit" probe
	 * to fire if it's desirable, and also to allow a decision to be made
	 * about later firing with BSM in the audit worker.
	 */
	if (dtaudit_hook_commit != NULL) {
		if (dtaudit_hook_commit(ar, auid, event, class, sorf) != 0)
			ar->k_ar_commit |= AR_PRESELECT_DTRACE;
	}
#endif

	if ((ar->k_ar_commit & (AR_PRESELECT_TRAIL | AR_PRESELECT_PIPE |
	    AR_PRESELECT_USER_TRAIL | AR_PRESELECT_USER_PIPE |
	    AR_PRESELECT_DTRACE)) == 0) {
		mtx_lock(&audit_mtx);
		audit_pre_q_len--;
		mtx_unlock(&audit_mtx);
		audit_free(ar);
		return;
	}

	/*
	 * Note: it could be that some records initiated while audit was
	 * enabled should still be committed?
	 *
	 * NB: The check here is not for audit_syscalls because any
	 * DTrace-related obligations have been fulfilled above -- we're just
	 * down to the trail and pipes now.
	 */
	mtx_lock(&audit_mtx);
	if (audit_trail_suspended || !audit_trail_enabled) {
		audit_pre_q_len--;
		mtx_unlock(&audit_mtx);
		audit_free(ar);
		return;
	}

	/*
	 * Constrain the number of committed audit records based on the
	 * configurable parameter.
	 */
	while (audit_q_len >= audit_qctrl.aq_hiwater)
		cv_wait(&audit_watermark_cv, &audit_mtx);

	TAILQ_INSERT_TAIL(&audit_q, ar, k_q);
	audit_q_len++;
	audit_pre_q_len--;
	cv_signal(&audit_worker_cv);
	mtx_unlock(&audit_mtx);
}