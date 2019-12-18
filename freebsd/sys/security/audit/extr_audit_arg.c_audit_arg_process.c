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
struct TYPE_3__ {int /*<<< orphan*/  ai_termid; int /*<<< orphan*/  ai_asid; int /*<<< orphan*/  ai_auid; } ;
struct ucred {TYPE_1__ cr_audit; int /*<<< orphan*/  cr_rgid; int /*<<< orphan*/  cr_ruid; int /*<<< orphan*/ * cr_groups; int /*<<< orphan*/  cr_uid; } ;
struct proc {int /*<<< orphan*/  p_pid; struct ucred* p_ucred; } ;
struct TYPE_4__ {int /*<<< orphan*/  ar_arg_pid; int /*<<< orphan*/  ar_arg_termid_addr; int /*<<< orphan*/  ar_arg_asid; int /*<<< orphan*/  ar_arg_rgid; int /*<<< orphan*/  ar_arg_ruid; int /*<<< orphan*/  ar_arg_egid; int /*<<< orphan*/  ar_arg_euid; int /*<<< orphan*/  ar_arg_auid; } ;
struct kaudit_record {TYPE_2__ k_ar; } ;

/* Variables and functions */
 int ARG_ASID ; 
 int ARG_AUID ; 
 int ARG_EGID ; 
 int ARG_EUID ; 
 int ARG_PID ; 
 int ARG_PROCESS ; 
 int ARG_RGID ; 
 int ARG_RUID ; 
 int /*<<< orphan*/  ARG_SET_VALID (struct kaudit_record*,int) ; 
 int ARG_TERMID_ADDR ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 struct kaudit_record* currecord () ; 

void
audit_arg_process(struct proc *p)
{
	struct kaudit_record *ar;
	struct ucred *cred;

	KASSERT(p != NULL, ("audit_arg_process: p == NULL"));

	PROC_LOCK_ASSERT(p, MA_OWNED);

	ar = currecord();
	if (ar == NULL)
		return;

	cred = p->p_ucred;
	ar->k_ar.ar_arg_auid = cred->cr_audit.ai_auid;
	ar->k_ar.ar_arg_euid = cred->cr_uid;
	ar->k_ar.ar_arg_egid = cred->cr_groups[0];
	ar->k_ar.ar_arg_ruid = cred->cr_ruid;
	ar->k_ar.ar_arg_rgid = cred->cr_rgid;
	ar->k_ar.ar_arg_asid = cred->cr_audit.ai_asid;
	ar->k_ar.ar_arg_termid_addr = cred->cr_audit.ai_termid;
	ar->k_ar.ar_arg_pid = p->p_pid;
	ARG_SET_VALID(ar, ARG_AUID | ARG_EUID | ARG_EGID | ARG_RUID |
	    ARG_RGID | ARG_ASID | ARG_TERMID_ADDR | ARG_PID | ARG_PROCESS);
}