#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_sec; int tv_usec; } ;
struct thread {struct proc* td_proc; } ;
struct rusage {int ru_ixrss; int ru_idrss; int ru_isrss; int ru_inblock; int ru_oublock; } ;
struct proc {int p_flag; struct plimit* p_limit; int /*<<< orphan*/  p_acflag; TYPE_4__* p_ucred; TYPE_3__* p_stats; int /*<<< orphan*/  p_comm; TYPE_2__* p_pgrp; } ;
struct plimit {int dummy; } ;
struct acctv3 {int ac_btime; int ac_version; int ac_len; int ac_len2; scalar_t__ ac_zero; int /*<<< orphan*/  ac_flagx; int /*<<< orphan*/  ac_gid; int /*<<< orphan*/  ac_uid; void* ac_io; void* ac_mem; void* ac_etime; void* ac_stime; void* ac_utime; int /*<<< orphan*/  ac_comm; int /*<<< orphan*/  ac_tty; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  acct ;
struct TYPE_8__ {int /*<<< orphan*/  cr_rgid; int /*<<< orphan*/  cr_ruid; } ;
struct TYPE_7__ {struct timeval p_start; } ;
struct TYPE_6__ {TYPE_1__* pg_session; } ;
struct TYPE_5__ {scalar_t__ s_ttyp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANVER ; 
 int IO_APPEND ; 
 int IO_UNIT ; 
 int /*<<< orphan*/  NOCRED ; 
 int /*<<< orphan*/  NODEV ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int P_CONTROLT ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int /*<<< orphan*/  acct_cred ; 
 int /*<<< orphan*/  acct_limit ; 
 scalar_t__ acct_suspended ; 
 int /*<<< orphan*/  acct_sx ; 
 int /*<<< orphan*/ * acct_vp ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* encode_long (int) ; 
 void* encode_timeval (struct timeval) ; 
 int /*<<< orphan*/  getboottime (struct timeval*) ; 
 int hz ; 
 int /*<<< orphan*/  lim_free (struct plimit*) ; 
 struct plimit* lim_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  microuptime (struct timeval*) ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  rufetchcalc (struct proc*,struct rusage*,struct timeval*,struct timeval*) ; 
 int /*<<< orphan*/  sx_slock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 
 int tick ; 
 int /*<<< orphan*/  timevaladd (struct timeval*,struct timeval*) ; 
 int /*<<< orphan*/  timevalsub (struct timeval*,struct timeval*) ; 
 int /*<<< orphan*/  tty_udev (scalar_t__) ; 
 int vn_rdwr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct thread*) ; 

int
acct_process(struct thread *td)
{
	struct acctv3 acct;
	struct timeval ut, st, tmp;
	struct plimit *oldlim;
	struct proc *p;
	struct rusage ru;
	int t, ret;

	/*
	 * Lockless check of accounting condition before doing the hard
	 * work.
	 */
	if (acct_vp == NULL || acct_suspended)
		return (0);

	sx_slock(&acct_sx);

	/*
	 * If accounting isn't enabled, don't bother.  Have to check again
	 * once we own the lock in case we raced with disabling of accounting
	 * by another thread.
	 */
	if (acct_vp == NULL || acct_suspended) {
		sx_sunlock(&acct_sx);
		return (0);
	}

	p = td->td_proc;

	/*
	 * Get process accounting information.
	 */

	sx_slock(&proctree_lock);
	PROC_LOCK(p);

	/* (1) The terminal from which the process was started */
	if ((p->p_flag & P_CONTROLT) && p->p_pgrp->pg_session->s_ttyp)
		acct.ac_tty = tty_udev(p->p_pgrp->pg_session->s_ttyp);
	else
		acct.ac_tty = NODEV;
	sx_sunlock(&proctree_lock);

	/* (2) The name of the command that ran */
	bcopy(p->p_comm, acct.ac_comm, sizeof acct.ac_comm);

	/* (3) The amount of user and system time that was used */
	rufetchcalc(p, &ru, &ut, &st);
	acct.ac_utime = encode_timeval(ut);
	acct.ac_stime = encode_timeval(st);

	/* (4) The elapsed time the command ran (and its starting time) */
	getboottime(&tmp);
	timevaladd(&tmp, &p->p_stats->p_start);
	acct.ac_btime = tmp.tv_sec;
	microuptime(&tmp);
	timevalsub(&tmp, &p->p_stats->p_start);
	acct.ac_etime = encode_timeval(tmp);

	/* (5) The average amount of memory used */
	tmp = ut;
	timevaladd(&tmp, &st);
	/* Convert tmp (i.e. u + s) into hz units to match ru_i*. */
	t = tmp.tv_sec * hz + tmp.tv_usec / tick;
	if (t)
		acct.ac_mem = encode_long((ru.ru_ixrss + ru.ru_idrss +
		    + ru.ru_isrss) / t);
	else
		acct.ac_mem = 0;

	/* (6) The number of disk I/O operations done */
	acct.ac_io = encode_long(ru.ru_inblock + ru.ru_oublock);

	/* (7) The UID and GID of the process */
	acct.ac_uid = p->p_ucred->cr_ruid;
	acct.ac_gid = p->p_ucred->cr_rgid;

	/* (8) The boolean flags that tell how the process terminated, etc. */
	acct.ac_flagx = p->p_acflag;

	/* Setup ancillary structure fields. */
	acct.ac_flagx |= ANVER;
	acct.ac_zero = 0;
	acct.ac_version = 3;
	acct.ac_len = acct.ac_len2 = sizeof(acct);

	/*
	 * Eliminate rlimits (file size limit in particular).
	 */
	oldlim = p->p_limit;
	p->p_limit = lim_hold(acct_limit);
	PROC_UNLOCK(p);
	lim_free(oldlim);

	/*
	 * Write the accounting information to the file.
	 */
	ret = vn_rdwr(UIO_WRITE, acct_vp, (caddr_t)&acct, sizeof (acct),
	    (off_t)0, UIO_SYSSPACE, IO_APPEND|IO_UNIT, acct_cred, NOCRED,
	    NULL, td);
	sx_sunlock(&acct_sx);
	return (ret);
}