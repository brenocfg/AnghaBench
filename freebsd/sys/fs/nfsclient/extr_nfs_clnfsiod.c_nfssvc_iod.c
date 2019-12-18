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
struct nfsmount {scalar_t__ nm_bufq; int nm_bufqiods; scalar_t__ nm_bufqlen; scalar_t__ nm_bufqwant; } ;
struct buf {int b_flags; scalar_t__ b_iocmd; int /*<<< orphan*/  b_wcred; int /*<<< orphan*/  b_vp; int /*<<< orphan*/  b_rcred; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNCIO ; 
 scalar_t__ BIO_READ ; 
 scalar_t__ BIO_WRITE ; 
 int B_DIRECT ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ NFSIOD_AVAILABLE ; 
 scalar_t__ NFSIOD_NOT_AVAILABLE ; 
 int /*<<< orphan*/  NFSLOCKIOD () ; 
 int /*<<< orphan*/  NFSUNLOCKIOD () ; 
 int /*<<< orphan*/  NFS_DPF (int /*<<< orphan*/ ,char*) ; 
 int PCATCH ; 
 int PWAIT ; 
 struct buf* TAILQ_FIRST (scalar_t__*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (scalar_t__*,struct buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b_freelist ; 
 int hz ; 
 int /*<<< orphan*/  kproc_exit (int) ; 
 int msleep (scalar_t__*,int /*<<< orphan*/ *,int,char*,int) ; 
 int /*<<< orphan*/  ncl_doio (int /*<<< orphan*/ ,struct buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncl_doio_directwrite (struct buf*) ; 
 int /*<<< orphan*/  ncl_iod_mutex ; 
 int ncl_iodmax ; 
 struct nfsmount** ncl_iodmount ; 
 scalar_t__* ncl_iodwant ; 
 scalar_t__ ncl_numasync ; 
 int* nfs_asyncdaemon ; 
 scalar_t__ nfs_defect ; 
 int nfs_iodmaxidle ; 
 int nfs_iodmin ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

__attribute__((used)) static void
nfssvc_iod(void *instance)
{
	struct buf *bp;
	struct nfsmount *nmp;
	int myiod, timo;
	int error = 0;

	NFSLOCKIOD();
	myiod = (int *)instance - nfs_asyncdaemon;
	/*
	 * Main loop
	 */
	for (;;) {
	    while (((nmp = ncl_iodmount[myiod]) == NULL)
		   || !TAILQ_FIRST(&nmp->nm_bufq)) {
		if (myiod >= ncl_iodmax)
			goto finish;
		if (nmp)
			nmp->nm_bufqiods--;
		if (ncl_iodwant[myiod] == NFSIOD_NOT_AVAILABLE)
			ncl_iodwant[myiod] = NFSIOD_AVAILABLE;
		ncl_iodmount[myiod] = NULL;
		/*
		 * Always keep at least nfs_iodmin kthreads.
		 */
		timo = (myiod < nfs_iodmin) ? 0 : nfs_iodmaxidle * hz;
		error = msleep(&ncl_iodwant[myiod], &ncl_iod_mutex, PWAIT | PCATCH,
		    "-", timo);
		if (error) {
			nmp = ncl_iodmount[myiod];
			/*
			 * Rechecking the nm_bufq closes a rare race where the 
			 * nfsiod is woken up at the exact time the idle timeout
			 * fires
			 */
			if (nmp && TAILQ_FIRST(&nmp->nm_bufq))
				error = 0;
			break;
		}
	    }
	    if (error)
		    break;
	    while ((bp = TAILQ_FIRST(&nmp->nm_bufq)) != NULL) {
		/* Take one off the front of the list */
		TAILQ_REMOVE(&nmp->nm_bufq, bp, b_freelist);
		nmp->nm_bufqlen--;
		if (nmp->nm_bufqwant && nmp->nm_bufqlen <= ncl_numasync) {
		    nmp->nm_bufqwant = 0;
		    wakeup(&nmp->nm_bufq);
		}
		NFSUNLOCKIOD();
		if (bp->b_flags & B_DIRECT) {
			KASSERT((bp->b_iocmd == BIO_WRITE), ("nfscvs_iod: BIO_WRITE not set"));
			(void)ncl_doio_directwrite(bp);
		} else {
			if (bp->b_iocmd == BIO_READ)
				(void) ncl_doio(bp->b_vp, bp, bp->b_rcred,
				    NULL, 0);
			else
				(void) ncl_doio(bp->b_vp, bp, bp->b_wcred,
				    NULL, 0);
		}
		NFSLOCKIOD();
		/*
		 * Make sure the nmp hasn't been dismounted as soon as
		 * ncl_doio() completes for the last buffer.
		 */
		nmp = ncl_iodmount[myiod];
		if (nmp == NULL)
			break;

		/*
		 * If there are more than one iod on this mount, then defect
		 * so that the iods can be shared out fairly between the mounts
		 */
		if (nfs_defect && nmp->nm_bufqiods > 1) {
		    NFS_DPF(ASYNCIO,
			    ("nfssvc_iod: iod %d defecting from mount %p\n",
			     myiod, nmp));
		    ncl_iodmount[myiod] = NULL;
		    nmp->nm_bufqiods--;
		    break;
		}
	    }
	}
finish:
	nfs_asyncdaemon[myiod] = 0;
	if (nmp)
	    nmp->nm_bufqiods--;
	ncl_iodwant[myiod] = NFSIOD_NOT_AVAILABLE;
	ncl_iodmount[myiod] = NULL;
	/* Someone may be waiting for the last nfsiod to terminate. */
	if (--ncl_numasync == 0)
		wakeup(&ncl_numasync);
	NFSUNLOCKIOD();
	if ((error == 0) || (error == EWOULDBLOCK))
		kproc_exit(0);
	/* Abnormal termination */
	kproc_exit(1);
}