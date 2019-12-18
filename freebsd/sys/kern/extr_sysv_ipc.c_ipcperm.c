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
struct ucred {scalar_t__ cr_uid; } ;
struct thread {struct ucred* td_ucred; } ;
struct ipc_perm {scalar_t__ cuid; scalar_t__ uid; int mode; int /*<<< orphan*/  cgid; int /*<<< orphan*/  gid; } ;

/* Variables and functions */
 int EACCES ; 
 int IPC_M ; 
 int IPC_R ; 
 int IPC_W ; 
 int /*<<< orphan*/  PRIV_IPC_ADMIN ; 
 int /*<<< orphan*/  PRIV_IPC_READ ; 
 int /*<<< orphan*/  PRIV_IPC_WRITE ; 
 scalar_t__ groupmember (int /*<<< orphan*/ ,struct ucred*) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 

int
ipcperm(struct thread *td, struct ipc_perm *perm, int acc_mode)
{
	struct ucred *cred = td->td_ucred;
	int error, obj_mode, dac_granted, priv_granted;

	dac_granted = 0;
	if (cred->cr_uid == perm->cuid || cred->cr_uid == perm->uid) {
		obj_mode = perm->mode;
		dac_granted |= IPC_M;
	} else if (groupmember(perm->gid, cred) ||
	    groupmember(perm->cgid, cred)) {
		obj_mode = perm->mode;
		obj_mode <<= 3;
	} else {
		obj_mode = perm->mode;
		obj_mode <<= 6;
	}

	/*
	 * While the System V IPC permission model allows IPC_M to be
	 * granted, as part of the mode, our implementation requires
	 * privilege to adminster the object if not the owner or creator.
	 */
#if 0
	if (obj_mode & IPC_M)
		dac_granted |= IPC_M;
#endif
	if (obj_mode & IPC_R)
		dac_granted |= IPC_R;
	if (obj_mode & IPC_W)
		dac_granted |= IPC_W;

	/*
	 * Simple case: all required rights are granted by DAC.
	 */
	if ((dac_granted & acc_mode) == acc_mode)
		return (0);

	/*
	 * Privilege is required to satisfy the request.
	 */
	priv_granted = 0;
	if ((acc_mode & IPC_M) && !(dac_granted & IPC_M)) {
		error = priv_check(td, PRIV_IPC_ADMIN);
		if (error == 0)
			priv_granted |= IPC_M;
	}

	if ((acc_mode & IPC_R) && !(dac_granted & IPC_R)) {
		error = priv_check(td, PRIV_IPC_READ);
		if (error == 0)
			priv_granted |= IPC_R;
	}

	if ((acc_mode & IPC_W) && !(dac_granted & IPC_W)) {
		error = priv_check(td, PRIV_IPC_WRITE);
		if (error == 0)
			priv_granted |= IPC_W;
	}

	if (((dac_granted | priv_granted) & acc_mode) == acc_mode)
		return (0);
	else
		return (EACCES);
}