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
struct thread {scalar_t__* td_retval; TYPE_3__* td_proc; int /*<<< orphan*/  td_ucred; } ;
struct semop_args {int semid; size_t nsops; int /*<<< orphan*/  sops; } ;
struct TYPE_10__ {int mode; unsigned short seq; } ;
struct TYPE_7__ {size_t sem_nsems; int /*<<< orphan*/  sem_otime; struct sem* __sem_base; TYPE_4__ sem_perm; } ;
struct semid_kernel {TYPE_1__ u; } ;
struct sembuf {size_t sem_num; int sem_flg; scalar_t__ sem_op; } ;
struct sem_undo {int dummy; } ;
struct sem {scalar_t__ semval; scalar_t__ semzcnt; scalar_t__ semncnt; int /*<<< orphan*/  sempid; } ;
struct prison {int dummy; } ;
struct mtx {int dummy; } ;
typedef  int /*<<< orphan*/  sops ;
struct TYPE_9__ {int /*<<< orphan*/  p_pid; } ;
struct TYPE_8__ {int semmni; size_t semopm; scalar_t__ semvmx; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_SVIPC_ID (int) ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int E2BIG ; 
 int EAGAIN ; 
 int EFBIG ; 
 int EIDRM ; 
 int EINTR ; 
 int EINVAL ; 
 int ENOSYS ; 
 int ERANGE ; 
 int IPCID_TO_IX (int) ; 
 unsigned short IPCID_TO_SEQ (int) ; 
 int IPC_NOWAIT ; 
 int /*<<< orphan*/  M_SEM ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int PCATCH ; 
 int /*<<< orphan*/  PROC_LOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (TYPE_3__*) ; 
 int PZERO ; 
 int /*<<< orphan*/  RACCT_NSEMOP ; 
 int /*<<< orphan*/  SEMUNDO_LOCK () ; 
 int /*<<< orphan*/  SEMUNDO_UNLOCK () ; 
 size_t SEM_A ; 
 int SEM_ALLOC ; 
 size_t SEM_R ; 
 int SEM_UNDO ; 
 int SMALL_SOPS ; 
 int copyin (int /*<<< orphan*/ ,struct sembuf*,size_t) ; 
 int /*<<< orphan*/  free (struct sembuf*,int /*<<< orphan*/ ) ; 
 int ipcperm (struct thread*,TYPE_4__*,size_t) ; 
 int mac_sysvsem_check_semop (int /*<<< orphan*/ ,struct semid_kernel*,size_t) ; 
 struct sembuf* malloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int msleep (struct semid_kernel*,struct mtx*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ racct_enable ; 
 size_t racct_get_available (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sem ; 
 struct prison* sem_find_prison (int /*<<< orphan*/ ) ; 
 int sem_prison_cansee (struct prison*,struct semid_kernel*) ; 
 struct semid_kernel* sema ; 
 struct mtx* sema_mtx ; 
 TYPE_2__ seminfo ; 
 int semundo_adjust (struct thread*,struct sem_undo**,int,unsigned short,size_t,int) ; 
 int /*<<< orphan*/  time_second ; 
 int /*<<< orphan*/  wakeup (struct semid_kernel*) ; 

int
sys_semop(struct thread *td, struct semop_args *uap)
{
#define SMALL_SOPS	8
	struct sembuf small_sops[SMALL_SOPS];
	int semid = uap->semid;
	size_t nsops = uap->nsops;
	struct prison *rpr;
	struct sembuf *sops;
	struct semid_kernel *semakptr;
	struct sembuf *sopptr = NULL;
	struct sem *semptr = NULL;
	struct sem_undo *suptr;
	struct mtx *sema_mtxp;
	size_t i, j, k;
	int error;
	int do_wakeup, do_undos;
	unsigned short seq;

#ifdef SEM_DEBUG
	sops = NULL;
#endif
	DPRINTF(("call to semop(%d, %p, %u)\n", semid, sops, nsops));

	AUDIT_ARG_SVIPC_ID(semid);

	rpr = sem_find_prison(td->td_ucred);
	if (sem == NULL)
		return (ENOSYS);

	semid = IPCID_TO_IX(semid);	/* Convert back to zero origin */

	if (semid < 0 || semid >= seminfo.semmni)
		return (EINVAL);

	/* Allocate memory for sem_ops */
	if (nsops <= SMALL_SOPS)
		sops = small_sops;
	else if (nsops > seminfo.semopm) {
		DPRINTF(("too many sops (max=%d, nsops=%d)\n", seminfo.semopm,
		    nsops));
		return (E2BIG);
	} else {
#ifdef RACCT
		if (racct_enable) {
			PROC_LOCK(td->td_proc);
			if (nsops >
			    racct_get_available(td->td_proc, RACCT_NSEMOP)) {
				PROC_UNLOCK(td->td_proc);
				return (E2BIG);
			}
			PROC_UNLOCK(td->td_proc);
		}
#endif

		sops = malloc(nsops * sizeof(*sops), M_TEMP, M_WAITOK);
	}
	if ((error = copyin(uap->sops, sops, nsops * sizeof(sops[0]))) != 0) {
		DPRINTF(("error = %d from copyin(%p, %p, %d)\n", error,
		    uap->sops, sops, nsops * sizeof(sops[0])));
		if (sops != small_sops)
			free(sops, M_SEM);
		return (error);
	}

	semakptr = &sema[semid];
	sema_mtxp = &sema_mtx[semid];
	mtx_lock(sema_mtxp);
	if ((semakptr->u.sem_perm.mode & SEM_ALLOC) == 0) {
		error = EINVAL;
		goto done2;
	}
	seq = semakptr->u.sem_perm.seq;
	if (seq != IPCID_TO_SEQ(uap->semid)) {
		error = EINVAL;
		goto done2;
	}
	if ((error = sem_prison_cansee(rpr, semakptr)) != 0)
		goto done2;
	/*
	 * Initial pass through sops to see what permissions are needed.
	 * Also perform any checks that don't need repeating on each
	 * attempt to satisfy the request vector.
	 */
	j = 0;		/* permission needed */
	do_undos = 0;
	for (i = 0; i < nsops; i++) {
		sopptr = &sops[i];
		if (sopptr->sem_num >= semakptr->u.sem_nsems) {
			error = EFBIG;
			goto done2;
		}
		if (sopptr->sem_flg & SEM_UNDO && sopptr->sem_op != 0)
			do_undos = 1;
		j |= (sopptr->sem_op == 0) ? SEM_R : SEM_A;
	}

	if ((error = ipcperm(td, &semakptr->u.sem_perm, j))) {
		DPRINTF(("error = %d from ipaccess\n", error));
		goto done2;
	}
#ifdef MAC
	error = mac_sysvsem_check_semop(td->td_ucred, semakptr, j);
	if (error != 0)
		goto done2;
#endif

	/*
	 * Loop trying to satisfy the vector of requests.
	 * If we reach a point where we must wait, any requests already
	 * performed are rolled back and we go to sleep until some other
	 * process wakes us up.  At this point, we start all over again.
	 *
	 * This ensures that from the perspective of other tasks, a set
	 * of requests is atomic (never partially satisfied).
	 */
	for (;;) {
		do_wakeup = 0;
		error = 0;	/* error return if necessary */

		for (i = 0; i < nsops; i++) {
			sopptr = &sops[i];
			semptr = &semakptr->u.__sem_base[sopptr->sem_num];

			DPRINTF((
			    "semop:  semakptr=%p, __sem_base=%p, "
			    "semptr=%p, sem[%d]=%d : op=%d, flag=%s\n",
			    semakptr, semakptr->u.__sem_base, semptr,
			    sopptr->sem_num, semptr->semval, sopptr->sem_op,
			    (sopptr->sem_flg & IPC_NOWAIT) ?
			    "nowait" : "wait"));

			if (sopptr->sem_op < 0) {
				if (semptr->semval + sopptr->sem_op < 0) {
					DPRINTF(("semop:  can't do it now\n"));
					break;
				} else {
					semptr->semval += sopptr->sem_op;
					if (semptr->semval == 0 &&
					    semptr->semzcnt > 0)
						do_wakeup = 1;
				}
			} else if (sopptr->sem_op == 0) {
				if (semptr->semval != 0) {
					DPRINTF(("semop:  not zero now\n"));
					break;
				}
			} else if (semptr->semval + sopptr->sem_op >
			    seminfo.semvmx) {
				error = ERANGE;
				break;
			} else {
				if (semptr->semncnt > 0)
					do_wakeup = 1;
				semptr->semval += sopptr->sem_op;
			}
		}

		/*
		 * Did we get through the entire vector?
		 */
		if (i >= nsops)
			goto done;

		/*
		 * No ... rollback anything that we've already done
		 */
		DPRINTF(("semop:  rollback 0 through %d\n", i-1));
		for (j = 0; j < i; j++)
			semakptr->u.__sem_base[sops[j].sem_num].semval -=
			    sops[j].sem_op;

		/* If we detected an error, return it */
		if (error != 0)
			goto done2;

		/*
		 * If the request that we couldn't satisfy has the
		 * NOWAIT flag set then return with EAGAIN.
		 */
		if (sopptr->sem_flg & IPC_NOWAIT) {
			error = EAGAIN;
			goto done2;
		}

		if (sopptr->sem_op == 0)
			semptr->semzcnt++;
		else
			semptr->semncnt++;

		DPRINTF(("semop:  good night!\n"));
		error = msleep(semakptr, sema_mtxp, (PZERO - 4) | PCATCH,
		    "semwait", 0);
		DPRINTF(("semop:  good morning (error=%d)!\n", error));
		/* return code is checked below, after sem[nz]cnt-- */

		/*
		 * Make sure that the semaphore still exists
		 */
		seq = semakptr->u.sem_perm.seq;
		if ((semakptr->u.sem_perm.mode & SEM_ALLOC) == 0 ||
		    seq != IPCID_TO_SEQ(uap->semid)) {
			error = EIDRM;
			goto done2;
		}

		/*
		 * Renew the semaphore's pointer after wakeup since
		 * during msleep __sem_base may have been modified and semptr
		 * is not valid any more
		 */
		semptr = &semakptr->u.__sem_base[sopptr->sem_num];

		/*
		 * The semaphore is still alive.  Readjust the count of
		 * waiting processes.
		 */
		if (sopptr->sem_op == 0)
			semptr->semzcnt--;
		else
			semptr->semncnt--;

		/*
		 * Is it really morning, or was our sleep interrupted?
		 * (Delayed check of msleep() return code because we
		 * need to decrement sem[nz]cnt either way.)
		 */
		if (error != 0) {
			error = EINTR;
			goto done2;
		}
		DPRINTF(("semop:  good morning!\n"));
	}

done:
	/*
	 * Process any SEM_UNDO requests.
	 */
	if (do_undos) {
		SEMUNDO_LOCK();
		suptr = NULL;
		for (i = 0; i < nsops; i++) {
			/*
			 * We only need to deal with SEM_UNDO's for non-zero
			 * op's.
			 */
			int adjval;

			if ((sops[i].sem_flg & SEM_UNDO) == 0)
				continue;
			adjval = sops[i].sem_op;
			if (adjval == 0)
				continue;
			error = semundo_adjust(td, &suptr, semid, seq,
			    sops[i].sem_num, -adjval);
			if (error == 0)
				continue;

			/*
			 * Oh-Oh!  We ran out of either sem_undo's or undo's.
			 * Rollback the adjustments to this point and then
			 * rollback the semaphore ups and down so we can return
			 * with an error with all structures restored.  We
			 * rollback the undo's in the exact reverse order that
			 * we applied them.  This guarantees that we won't run
			 * out of space as we roll things back out.
			 */
			for (j = 0; j < i; j++) {
				k = i - j - 1;
				if ((sops[k].sem_flg & SEM_UNDO) == 0)
					continue;
				adjval = sops[k].sem_op;
				if (adjval == 0)
					continue;
				if (semundo_adjust(td, &suptr, semid, seq,
				    sops[k].sem_num, adjval) != 0)
					panic("semop - can't undo undos");
			}

			for (j = 0; j < nsops; j++)
				semakptr->u.__sem_base[sops[j].sem_num].semval -=
				    sops[j].sem_op;

			DPRINTF(("error = %d from semundo_adjust\n", error));
			SEMUNDO_UNLOCK();
			goto done2;
		} /* loop through the sops */
		SEMUNDO_UNLOCK();
	} /* if (do_undos) */

	/* We're definitely done - set the sempid's and time */
	for (i = 0; i < nsops; i++) {
		sopptr = &sops[i];
		semptr = &semakptr->u.__sem_base[sopptr->sem_num];
		semptr->sempid = td->td_proc->p_pid;
	}
	semakptr->u.sem_otime = time_second;

	/*
	 * Do a wakeup if any semaphore was up'd whilst something was
	 * sleeping on it.
	 */
	if (do_wakeup) {
		DPRINTF(("semop:  doing wakeup\n"));
		wakeup(semakptr);
		DPRINTF(("semop:  back from wakeup\n"));
	}
	DPRINTF(("semop:  done\n"));
	td->td_retval[0] = 0;
done2:
	mtx_unlock(sema_mtxp);
	if (sops != small_sops)
		free(sops, M_SEM);
	return (error);
}