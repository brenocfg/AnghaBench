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
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  nr_lock; } ;
struct nfsmount {int nm_flag; int nm_timeo; int nm_retry; scalar_t__ nm_minorvers; scalar_t__ nm_wsize; scalar_t__ nm_rsize; scalar_t__ nm_readdirsize; scalar_t__ nm_acregmin; scalar_t__ nm_acregmax; scalar_t__ nm_acdirmin; scalar_t__ nm_acdirmax; scalar_t__ nm_readahead; int nm_wcommitsize; scalar_t__ nm_sotype; scalar_t__ nm_soproto; int /*<<< orphan*/  nm_hostname; TYPE_1__ nm_sockreq; int /*<<< orphan*/ * nm_client; } ;
struct nfs_args {scalar_t__ sotype; int flags; int timeo; int retrans; scalar_t__ wsize; scalar_t__ rsize; scalar_t__ readdirsize; scalar_t__ acregmin; scalar_t__ acregmax; scalar_t__ acdirmin; scalar_t__ acdirmax; scalar_t__ readahead; int wcommitsize; scalar_t__ proto; } ;
struct mount {int mnt_flag; int /*<<< orphan*/  mnt_optnew; } ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int MNT_RDONLY ; 
 int MNT_UPDATE ; 
 int NFSMNT_ACDIRMAX ; 
 int NFSMNT_ACDIRMIN ; 
 int NFSMNT_ACREGMAX ; 
 int NFSMNT_ACREGMIN ; 
 int NFSMNT_NFSV3 ; 
 int NFSMNT_NFSV4 ; 
 int NFSMNT_NOCONN ; 
 int NFSMNT_ONEOPENOWN ; 
 int NFSMNT_RDIRPLUS ; 
 int NFSMNT_READAHEAD ; 
 int NFSMNT_READDIRSIZE ; 
 int NFSMNT_RESVPORT ; 
 int NFSMNT_RETRANS ; 
 int NFSMNT_RSIZE ; 
 int NFSMNT_TIMEO ; 
 int NFSMNT_WCOMMITSIZE ; 
 int NFSMNT_WSIZE ; 
 void* NFS_FABLKSIZE ; 
 int NFS_HZ ; 
 scalar_t__ NFS_MAXATTRTIMO ; 
 scalar_t__ NFS_MAXDIRATTRTIMO ; 
 scalar_t__ NFS_MAXRAHEAD ; 
 int NFS_MAXREXMIT ; 
 void* NFS_MAXTIMEO ; 
 scalar_t__ NFS_MINATTRTIMO ; 
 scalar_t__ NFS_MINDIRATTRTIMO ; 
 int NFS_MINTIMEO ; 
 int NFS_RETRANS_TCP ; 
 int /*<<< orphan*/  PSOCK ; 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ SOCK_STREAM ; 
 int fls (int) ; 
 scalar_t__ newnfs_connect (struct nfsmount*,TYPE_1__*,struct ucred*,struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newnfs_disconnect (TYPE_1__*) ; 
 int newnfs_sndlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  newnfs_sndunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_catnap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ vfs_getopt (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfs_decode_args(struct mount *mp, struct nfsmount *nmp, struct nfs_args *argp,
    const char *hostname, struct ucred *cred, struct thread *td)
{
	int adjsock;
	char *p;

	/*
	 * Set read-only flag if requested; otherwise, clear it if this is
	 * an update.  If this is not an update, then either the read-only
	 * flag is already clear, or this is a root mount and it was set
	 * intentionally at some previous point.
	 */
	if (vfs_getopt(mp->mnt_optnew, "ro", NULL, NULL) == 0) {
		MNT_ILOCK(mp);
		mp->mnt_flag |= MNT_RDONLY;
		MNT_IUNLOCK(mp);
	} else if (mp->mnt_flag & MNT_UPDATE) {
		MNT_ILOCK(mp);
		mp->mnt_flag &= ~MNT_RDONLY;
		MNT_IUNLOCK(mp);
	}

	/*
	 * Silently clear NFSMNT_NOCONN if it's a TCP mount, it makes
	 * no sense in that context.  Also, set up appropriate retransmit
	 * and soft timeout behavior.
	 */
	if (argp->sotype == SOCK_STREAM) {
		nmp->nm_flag &= ~NFSMNT_NOCONN;
		nmp->nm_timeo = NFS_MAXTIMEO;
		if ((argp->flags & NFSMNT_NFSV4) != 0)
			nmp->nm_retry = INT_MAX;
		else
			nmp->nm_retry = NFS_RETRANS_TCP;
	}

	/* Also clear RDIRPLUS if NFSv2, it crashes some servers */
	if ((argp->flags & (NFSMNT_NFSV3 | NFSMNT_NFSV4)) == 0) {
		argp->flags &= ~NFSMNT_RDIRPLUS;
		nmp->nm_flag &= ~NFSMNT_RDIRPLUS;
	}

	/* Clear ONEOPENOWN for NFSv2, 3 and 4.0. */
	if (nmp->nm_minorvers == 0) {
		argp->flags &= ~NFSMNT_ONEOPENOWN;
		nmp->nm_flag &= ~NFSMNT_ONEOPENOWN;
	}

	/* Re-bind if rsrvd port requested and wasn't on one */
	adjsock = !(nmp->nm_flag & NFSMNT_RESVPORT)
		  && (argp->flags & NFSMNT_RESVPORT);
	/* Also re-bind if we're switching to/from a connected UDP socket */
	adjsock |= ((nmp->nm_flag & NFSMNT_NOCONN) !=
		    (argp->flags & NFSMNT_NOCONN));

	/* Update flags atomically.  Don't change the lock bits. */
	nmp->nm_flag = argp->flags | nmp->nm_flag;

	if ((argp->flags & NFSMNT_TIMEO) && argp->timeo > 0) {
		nmp->nm_timeo = (argp->timeo * NFS_HZ + 5) / 10;
		if (nmp->nm_timeo < NFS_MINTIMEO)
			nmp->nm_timeo = NFS_MINTIMEO;
		else if (nmp->nm_timeo > NFS_MAXTIMEO)
			nmp->nm_timeo = NFS_MAXTIMEO;
	}

	if ((argp->flags & NFSMNT_RETRANS) && argp->retrans > 1) {
		nmp->nm_retry = argp->retrans;
		if (nmp->nm_retry > NFS_MAXREXMIT)
			nmp->nm_retry = NFS_MAXREXMIT;
	}

	if ((argp->flags & NFSMNT_WSIZE) && argp->wsize > 0) {
		nmp->nm_wsize = argp->wsize;
		/*
		 * Clip at the power of 2 below the size. There is an
		 * issue (not isolated) that causes intermittent page
		 * faults if this is not done.
		 */
		if (nmp->nm_wsize > NFS_FABLKSIZE)
			nmp->nm_wsize = 1 << (fls(nmp->nm_wsize) - 1);
		else
			nmp->nm_wsize = NFS_FABLKSIZE;
	}

	if ((argp->flags & NFSMNT_RSIZE) && argp->rsize > 0) {
		nmp->nm_rsize = argp->rsize;
		/*
		 * Clip at the power of 2 below the size. There is an
		 * issue (not isolated) that causes intermittent page
		 * faults if this is not done.
		 */
		if (nmp->nm_rsize > NFS_FABLKSIZE)
			nmp->nm_rsize = 1 << (fls(nmp->nm_rsize) - 1);
		else
			nmp->nm_rsize = NFS_FABLKSIZE;
	}

	if ((argp->flags & NFSMNT_READDIRSIZE) && argp->readdirsize > 0) {
		nmp->nm_readdirsize = argp->readdirsize;
	}

	if ((argp->flags & NFSMNT_ACREGMIN) && argp->acregmin >= 0)
		nmp->nm_acregmin = argp->acregmin;
	else
		nmp->nm_acregmin = NFS_MINATTRTIMO;
	if ((argp->flags & NFSMNT_ACREGMAX) && argp->acregmax >= 0)
		nmp->nm_acregmax = argp->acregmax;
	else
		nmp->nm_acregmax = NFS_MAXATTRTIMO;
	if ((argp->flags & NFSMNT_ACDIRMIN) && argp->acdirmin >= 0)
		nmp->nm_acdirmin = argp->acdirmin;
	else
		nmp->nm_acdirmin = NFS_MINDIRATTRTIMO;
	if ((argp->flags & NFSMNT_ACDIRMAX) && argp->acdirmax >= 0)
		nmp->nm_acdirmax = argp->acdirmax;
	else
		nmp->nm_acdirmax = NFS_MAXDIRATTRTIMO;
	if (nmp->nm_acdirmin > nmp->nm_acdirmax)
		nmp->nm_acdirmin = nmp->nm_acdirmax;
	if (nmp->nm_acregmin > nmp->nm_acregmax)
		nmp->nm_acregmin = nmp->nm_acregmax;

	if ((argp->flags & NFSMNT_READAHEAD) && argp->readahead >= 0) {
		if (argp->readahead <= NFS_MAXRAHEAD)
			nmp->nm_readahead = argp->readahead;
		else
			nmp->nm_readahead = NFS_MAXRAHEAD;
	}
	if ((argp->flags & NFSMNT_WCOMMITSIZE) && argp->wcommitsize >= 0) {
		if (argp->wcommitsize < nmp->nm_wsize)
			nmp->nm_wcommitsize = nmp->nm_wsize;
		else
			nmp->nm_wcommitsize = argp->wcommitsize;
	}

	adjsock |= ((nmp->nm_sotype != argp->sotype) ||
		    (nmp->nm_soproto != argp->proto));

	if (nmp->nm_client != NULL && adjsock) {
		int haslock = 0, error = 0;

		if (nmp->nm_sotype == SOCK_STREAM) {
			error = newnfs_sndlock(&nmp->nm_sockreq.nr_lock);
			if (!error)
				haslock = 1;
		}
		if (!error) {
		    newnfs_disconnect(&nmp->nm_sockreq);
		    if (haslock)
			newnfs_sndunlock(&nmp->nm_sockreq.nr_lock);
		    nmp->nm_sotype = argp->sotype;
		    nmp->nm_soproto = argp->proto;
		    if (nmp->nm_sotype == SOCK_DGRAM)
			while (newnfs_connect(nmp, &nmp->nm_sockreq,
			    cred, td, 0)) {
				printf("newnfs_args: retrying connect\n");
				(void) nfs_catnap(PSOCK, 0, "nfscon");
			}
		}
	} else {
		nmp->nm_sotype = argp->sotype;
		nmp->nm_soproto = argp->proto;
	}

	if (hostname != NULL) {
		strlcpy(nmp->nm_hostname, hostname,
		    sizeof(nmp->nm_hostname));
		p = strchr(nmp->nm_hostname, ':');
		if (p != NULL)
			*p = '\0';
	}
}