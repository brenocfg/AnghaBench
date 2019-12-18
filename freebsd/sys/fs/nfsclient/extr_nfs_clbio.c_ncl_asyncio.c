#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct nfsmount {int nm_bufqiods; int nm_flag; int nm_bufqlen; int /*<<< orphan*/  nm_bufq; void* nm_bufqwant; } ;
struct buf {scalar_t__ b_iocmd; int b_flags; TYPE_2__* b_vp; struct ucred* b_wcred; struct ucred* b_rcred; } ;
struct TYPE_6__ {scalar_t__ v_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  n_directio_asyncwr; int /*<<< orphan*/  n_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNCIO ; 
 scalar_t__ BIO_READ ; 
 scalar_t__ BIO_WRITE ; 
 int /*<<< orphan*/  BUF_KERNPROC (struct buf*) ; 
 int B_DIRECT ; 
 int B_NEEDCOMMIT ; 
 int B_REMFREE ; 
 int EIO ; 
 int FALSE ; 
 scalar_t__ NFSIOD_AVAILABLE ; 
 scalar_t__ NFSIOD_NOT_AVAILABLE ; 
 int /*<<< orphan*/  NFSLOCKIOD () ; 
 int /*<<< orphan*/  NFSLOCKNODE (TYPE_1__*) ; 
 int NFSMNT_INT ; 
 int NFSMNT_RDIRPLUS ; 
 int /*<<< orphan*/  NFSUNLOCKIOD () ; 
 int /*<<< orphan*/  NFSUNLOCKNODE (TYPE_1__*) ; 
 int /*<<< orphan*/  NFS_DPF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NMODIFIED ; 
 struct ucred* NOCRED ; 
 int PCATCH ; 
 int PRIBIO ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct buf*,int /*<<< orphan*/ ) ; 
 void* TRUE ; 
 scalar_t__ VDIR ; 
 TYPE_1__* VTONFS (TYPE_2__*) ; 
 int /*<<< orphan*/  b_freelist ; 
 int /*<<< orphan*/  bremfreef (struct buf*) ; 
 void* crhold (struct ucred*) ; 
 int hz ; 
 int /*<<< orphan*/  ncl_iod_mutex ; 
 struct nfsmount** ncl_iodmount ; 
 scalar_t__* ncl_iodwant ; 
 int /*<<< orphan*/  ncl_nfsiodnew () ; 
 int ncl_numasync ; 
 int newnfs_msleep (struct thread*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*,int) ; 
 int newnfs_sigintr (struct nfsmount*,struct thread*) ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

int
ncl_asyncio(struct nfsmount *nmp, struct buf *bp, struct ucred *cred, struct thread *td)
{
	int iod;
	int gotiod;
	int slpflag = 0;
	int slptimeo = 0;
	int error, error2;

	/*
	 * Commits are usually short and sweet so lets save some cpu and
	 * leave the async daemons for more important rpc's (such as reads
	 * and writes).
	 *
	 * Readdirplus RPCs do vget()s to acquire the vnodes for entries
	 * in the directory in order to update attributes. This can deadlock
	 * with another thread that is waiting for async I/O to be done by
	 * an nfsiod thread while holding a lock on one of these vnodes.
	 * To avoid this deadlock, don't allow the async nfsiod threads to
	 * perform Readdirplus RPCs.
	 */
	NFSLOCKIOD();
	if ((bp->b_iocmd == BIO_WRITE && (bp->b_flags & B_NEEDCOMMIT) &&
	     (nmp->nm_bufqiods > ncl_numasync / 2)) ||
	    (bp->b_vp->v_type == VDIR && (nmp->nm_flag & NFSMNT_RDIRPLUS))) {
		NFSUNLOCKIOD();
		return(EIO);
	}
again:
	if (nmp->nm_flag & NFSMNT_INT)
		slpflag = PCATCH;
	gotiod = FALSE;

	/*
	 * Find a free iod to process this request.
	 */
	for (iod = 0; iod < ncl_numasync; iod++)
		if (ncl_iodwant[iod] == NFSIOD_AVAILABLE) {
			gotiod = TRUE;
			break;
		}

	/*
	 * Try to create one if none are free.
	 */
	if (!gotiod)
		ncl_nfsiodnew();
	else {
		/*
		 * Found one, so wake it up and tell it which
		 * mount to process.
		 */
		NFS_DPF(ASYNCIO, ("ncl_asyncio: waking iod %d for mount %p\n",
		    iod, nmp));
		ncl_iodwant[iod] = NFSIOD_NOT_AVAILABLE;
		ncl_iodmount[iod] = nmp;
		nmp->nm_bufqiods++;
		wakeup(&ncl_iodwant[iod]);
	}

	/*
	 * If none are free, we may already have an iod working on this mount
	 * point.  If so, it will process our request.
	 */
	if (!gotiod) {
		if (nmp->nm_bufqiods > 0) {
			NFS_DPF(ASYNCIO,
				("ncl_asyncio: %d iods are already processing mount %p\n",
				 nmp->nm_bufqiods, nmp));
			gotiod = TRUE;
		}
	}

	/*
	 * If we have an iod which can process the request, then queue
	 * the buffer.
	 */
	if (gotiod) {
		/*
		 * Ensure that the queue never grows too large.  We still want
		 * to asynchronize so we block rather then return EIO.
		 */
		while (nmp->nm_bufqlen >= 2*ncl_numasync) {
			NFS_DPF(ASYNCIO,
				("ncl_asyncio: waiting for mount %p queue to drain\n", nmp));
			nmp->nm_bufqwant = TRUE;
			error = newnfs_msleep(td, &nmp->nm_bufq,
			    &ncl_iod_mutex, slpflag | PRIBIO, "nfsaio",
			   slptimeo);
			if (error) {
				error2 = newnfs_sigintr(nmp, td);
				if (error2) {
					NFSUNLOCKIOD();
					return (error2);
				}
				if (slpflag == PCATCH) {
					slpflag = 0;
					slptimeo = 2 * hz;
				}
			}
			/*
			 * We might have lost our iod while sleeping,
			 * so check and loop if necessary.
			 */
			goto again;
		}

		/* We might have lost our nfsiod */
		if (nmp->nm_bufqiods == 0) {
			NFS_DPF(ASYNCIO,
				("ncl_asyncio: no iods after mount %p queue was drained, looping\n", nmp));
			goto again;
		}

		if (bp->b_iocmd == BIO_READ) {
			if (bp->b_rcred == NOCRED && cred != NOCRED)
				bp->b_rcred = crhold(cred);
		} else {
			if (bp->b_wcred == NOCRED && cred != NOCRED)
				bp->b_wcred = crhold(cred);
		}

		if (bp->b_flags & B_REMFREE)
			bremfreef(bp);
		BUF_KERNPROC(bp);
		TAILQ_INSERT_TAIL(&nmp->nm_bufq, bp, b_freelist);
		nmp->nm_bufqlen++;
		if ((bp->b_flags & B_DIRECT) && bp->b_iocmd == BIO_WRITE) {
			NFSLOCKNODE(VTONFS(bp->b_vp));
			VTONFS(bp->b_vp)->n_flag |= NMODIFIED;
			VTONFS(bp->b_vp)->n_directio_asyncwr++;
			NFSUNLOCKNODE(VTONFS(bp->b_vp));
		}
		NFSUNLOCKIOD();
		return (0);
	}

	NFSUNLOCKIOD();

	/*
	 * All the iods are busy on other mounts, so return EIO to
	 * force the caller to process the i/o synchronously.
	 */
	NFS_DPF(ASYNCIO, ("ncl_asyncio: no iods available, i/o is synchronous\n"));
	return (EIO);
}