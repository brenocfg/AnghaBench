#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {struct proc* td_proc; } ;
struct proc {TYPE_1__* p_session; } ;
struct getlogin_args {int namelen; int /*<<< orphan*/  namebuf; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_login; } ;

/* Variables and functions */
 int ERANGE ; 
 int MAXLOGNAME ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  SESS_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  SESS_UNLOCK (TYPE_1__*) ; 
 int copyout (char*,int /*<<< orphan*/ ,size_t) ; 
 int strlcpy (char*,int /*<<< orphan*/ ,int) ; 

int
sys_getlogin(struct thread *td, struct getlogin_args *uap)
{
	char login[MAXLOGNAME];
	struct proc *p = td->td_proc;
	size_t len;

	if (uap->namelen > MAXLOGNAME)
		uap->namelen = MAXLOGNAME;
	PROC_LOCK(p);
	SESS_LOCK(p->p_session);
	len = strlcpy(login, p->p_session->s_login, uap->namelen) + 1;
	SESS_UNLOCK(p->p_session);
	PROC_UNLOCK(p);
	if (len > uap->namelen)
		return (ERANGE);
	return (copyout(login, uap->namebuf, len));
}