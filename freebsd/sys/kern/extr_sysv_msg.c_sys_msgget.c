#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ucred {scalar_t__ cr_prison; int /*<<< orphan*/  cr_gid; int /*<<< orphan*/  cr_uid; } ;
struct thread {int /*<<< orphan*/ * td_retval; int /*<<< orphan*/  td_proc; struct ucred* td_ucred; } ;
struct TYPE_9__ {int key; int mode; int seq; int /*<<< orphan*/  gid; int /*<<< orphan*/  cgid; int /*<<< orphan*/  uid; int /*<<< orphan*/  cuid; } ;
struct TYPE_7__ {scalar_t__ msg_qbytes; TYPE_3__ msg_perm; int /*<<< orphan*/  msg_ctime; scalar_t__ msg_rtime; scalar_t__ msg_stime; scalar_t__ msg_lrpid; scalar_t__ msg_lspid; scalar_t__ msg_qnum; scalar_t__ msg_cbytes; int /*<<< orphan*/ * __msg_last; int /*<<< orphan*/ * __msg_first; } ;
struct msqid_kernel {TYPE_1__ u; TYPE_4__* cred; } ;
struct msgget_args {int key; int msgflg; } ;
struct TYPE_10__ {scalar_t__ cr_prison; } ;
struct TYPE_8__ {int msgmni; scalar_t__ msgmnb; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_SVIPC_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AUDIT_ARG_SVIPC_PERM (TYPE_3__*) ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int EEXIST ; 
 int ENOENT ; 
 int ENOSPC ; 
 int ENOSYS ; 
 int IPC_CREAT ; 
 int IPC_EXCL ; 
 int IPC_PRIVATE ; 
 int /*<<< orphan*/  IXSEQ_TO_IPCID (int,TYPE_3__) ; 
 int MSG_LOCKED ; 
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RACCT_NMSGQ ; 
 TYPE_4__* crhold (struct ucred*) ; 
 int ipcperm (struct thread*,TYPE_3__*,int) ; 
 int mac_sysvmsq_check_msqget (struct ucred*,struct msqid_kernel*) ; 
 int /*<<< orphan*/  mac_sysvmsq_create (struct ucred*,struct msqid_kernel*) ; 
 int /*<<< orphan*/ * msg_find_prison (struct ucred*) ; 
 TYPE_2__ msginfo ; 
 int /*<<< orphan*/  msq_mtx ; 
 struct msqid_kernel* msqids ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int racct_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ racct_enable ; 
 int /*<<< orphan*/  time_second ; 

int
sys_msgget(struct thread *td, struct msgget_args *uap)
{
	int msqid, error = 0;
	int key = uap->key;
	int msgflg = uap->msgflg;
	struct ucred *cred = td->td_ucred;
	struct msqid_kernel *msqkptr = NULL;

	DPRINTF(("msgget(0x%x, 0%o)\n", key, msgflg));

	if (msg_find_prison(cred) == NULL)
		return (ENOSYS);

	mtx_lock(&msq_mtx);
	if (key != IPC_PRIVATE) {
		for (msqid = 0; msqid < msginfo.msgmni; msqid++) {
			msqkptr = &msqids[msqid];
			if (msqkptr->u.msg_qbytes != 0 &&
			    msqkptr->cred != NULL &&
			    msqkptr->cred->cr_prison == cred->cr_prison &&
			    msqkptr->u.msg_perm.key == key)
				break;
		}
		if (msqid < msginfo.msgmni) {
			DPRINTF(("found public key\n"));
			if ((msgflg & IPC_CREAT) && (msgflg & IPC_EXCL)) {
				DPRINTF(("not exclusive\n"));
				error = EEXIST;
				goto done2;
			}
			AUDIT_ARG_SVIPC_ID(IXSEQ_TO_IPCID(msqid,
			    msqkptr->u.msg_perm));
			if ((error = ipcperm(td, &msqkptr->u.msg_perm,
			    msgflg & 0700))) {
				DPRINTF(("requester doesn't have 0%o access\n",
				    msgflg & 0700));
				goto done2;
			}
#ifdef MAC
			error = mac_sysvmsq_check_msqget(cred, msqkptr);
			if (error != 0)
				goto done2;
#endif
			goto found;
		}
	}

	DPRINTF(("need to allocate the msqid_ds\n"));
	if (key == IPC_PRIVATE || (msgflg & IPC_CREAT)) {
		for (msqid = 0; msqid < msginfo.msgmni; msqid++) {
			/*
			 * Look for an unallocated and unlocked msqid_ds.
			 * msqid_ds's can be locked by msgsnd or msgrcv while
			 * they are copying the message in/out.  We can't
			 * re-use the entry until they release it.
			 */
			msqkptr = &msqids[msqid];
			if (msqkptr->u.msg_qbytes == 0 &&
			    (msqkptr->u.msg_perm.mode & MSG_LOCKED) == 0)
				break;
		}
		if (msqid == msginfo.msgmni) {
			DPRINTF(("no more msqid_ds's available\n"));
			error = ENOSPC;
			goto done2;
		}
#ifdef RACCT
		if (racct_enable) {
			PROC_LOCK(td->td_proc);
			error = racct_add(td->td_proc, RACCT_NMSGQ, 1);
			PROC_UNLOCK(td->td_proc);
			if (error != 0) {
				error = ENOSPC;
				goto done2;
			}
		}
#endif
		DPRINTF(("msqid %d is available\n", msqid));
		msqkptr->u.msg_perm.key = key;
		msqkptr->u.msg_perm.cuid = cred->cr_uid;
		msqkptr->u.msg_perm.uid = cred->cr_uid;
		msqkptr->u.msg_perm.cgid = cred->cr_gid;
		msqkptr->u.msg_perm.gid = cred->cr_gid;
		msqkptr->u.msg_perm.mode = (msgflg & 0777);
		msqkptr->cred = crhold(cred);
		/* Make sure that the returned msqid is unique */
		msqkptr->u.msg_perm.seq = (msqkptr->u.msg_perm.seq + 1) & 0x7fff;
		msqkptr->u.__msg_first = NULL;
		msqkptr->u.__msg_last = NULL;
		msqkptr->u.msg_cbytes = 0;
		msqkptr->u.msg_qnum = 0;
		msqkptr->u.msg_qbytes = msginfo.msgmnb;
		msqkptr->u.msg_lspid = 0;
		msqkptr->u.msg_lrpid = 0;
		msqkptr->u.msg_stime = 0;
		msqkptr->u.msg_rtime = 0;
		msqkptr->u.msg_ctime = time_second;
#ifdef MAC
		mac_sysvmsq_create(cred, msqkptr);
#endif
		AUDIT_ARG_SVIPC_PERM(&msqkptr->u.msg_perm);
	} else {
		DPRINTF(("didn't find it and wasn't asked to create it\n"));
		error = ENOENT;
		goto done2;
	}

found:
	/* Construct the unique msqid */
	td->td_retval[0] = IXSEQ_TO_IPCID(msqid, msqkptr->u.msg_perm);
done2:
	mtx_unlock(&msq_mtx);
	return (error);
}