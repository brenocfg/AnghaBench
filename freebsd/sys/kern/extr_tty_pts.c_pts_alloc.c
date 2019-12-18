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
struct ucred {int /*<<< orphan*/  cr_ruidinfo; } ;
struct tty {int /*<<< orphan*/  t_mtx; } ;
struct thread {struct ucred* td_ucred; struct proc* td_proc; } ;
struct TYPE_4__ {int /*<<< orphan*/  si_note; } ;
struct TYPE_3__ {int /*<<< orphan*/  si_note; } ;
struct pts_softc {int pts_unit; TYPE_2__ pts_outpoll; TYPE_1__ pts_inpoll; int /*<<< orphan*/  pts_cred; int /*<<< orphan*/  pts_outwait; int /*<<< orphan*/  pts_inwait; } ;
struct proc {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTYPE_PTS ; 
 int EAGAIN ; 
 int /*<<< orphan*/  M_PTS ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  RACCT_NPTS ; 
 int /*<<< orphan*/  RLIMIT_NPTS ; 
 int alloc_unr (int /*<<< orphan*/ ) ; 
 int chgptscnt (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crhold (struct ucred*) ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  finit (struct file*,int,int /*<<< orphan*/ ,struct tty*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  knlist_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lim_cur (struct thread*,int /*<<< orphan*/ ) ; 
 struct pts_softc* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pts_class ; 
 int /*<<< orphan*/  pts_pool ; 
 int /*<<< orphan*/  ptsdev_ops ; 
 int racct_add (struct proc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  racct_sub (struct proc*,int /*<<< orphan*/ ,int) ; 
 struct tty* tty_alloc (int /*<<< orphan*/ *,struct pts_softc*) ; 
 int /*<<< orphan*/  tty_makedev (struct tty*,struct ucred*,char*,int) ; 

int
pts_alloc(int fflags, struct thread *td, struct file *fp)
{
	int unit, ok, error;
	struct tty *tp;
	struct pts_softc *psc;
	struct proc *p = td->td_proc;
	struct ucred *cred = td->td_ucred;

	/* Resource limiting. */
	PROC_LOCK(p);
	error = racct_add(p, RACCT_NPTS, 1);
	if (error != 0) {
		PROC_UNLOCK(p);
		return (EAGAIN);
	}
	ok = chgptscnt(cred->cr_ruidinfo, 1, lim_cur(td, RLIMIT_NPTS));
	if (!ok) {
		racct_sub(p, RACCT_NPTS, 1);
		PROC_UNLOCK(p);
		return (EAGAIN);
	}
	PROC_UNLOCK(p);

	/* Try to allocate a new pts unit number. */
	unit = alloc_unr(pts_pool);
	if (unit < 0) {
		racct_sub(p, RACCT_NPTS, 1);
		chgptscnt(cred->cr_ruidinfo, -1, 0);
		return (EAGAIN);
	}

	/* Allocate TTY and softc. */
	psc = malloc(sizeof(struct pts_softc), M_PTS, M_WAITOK|M_ZERO);
	cv_init(&psc->pts_inwait, "ptsin");
	cv_init(&psc->pts_outwait, "ptsout");

	psc->pts_unit = unit;
	psc->pts_cred = crhold(cred);

	tp = tty_alloc(&pts_class, psc);
	knlist_init_mtx(&psc->pts_inpoll.si_note, tp->t_mtx);
	knlist_init_mtx(&psc->pts_outpoll.si_note, tp->t_mtx);

	/* Expose the slave device as well. */
	tty_makedev(tp, td->td_ucred, "pts/%u", psc->pts_unit);

	finit(fp, fflags, DTYPE_PTS, tp, &ptsdev_ops);

	return (0);
}