#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vnode {scalar_t__ v_type; TYPE_1__* v_mount; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct pnfsdsattr {int /*<<< orphan*/  dsa_mtime; int /*<<< orphan*/  dsa_atime; int /*<<< orphan*/  dsa_size; int /*<<< orphan*/  dsa_filerev; } ;
struct nfsvattr {int /*<<< orphan*/  na_mtime; int /*<<< orphan*/  na_atime; int /*<<< orphan*/  na_size; int /*<<< orphan*/  na_filerev; } ;
struct nfsmount {int nm_privflag; } ;
struct nfsdevice {int dummy; } ;
struct mbuf {int dummy; } ;
struct acl {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  fhandle_t ;
typedef  int /*<<< orphan*/  dsattr ;
struct TYPE_2__ {int mnt_flag; } ;

/* Variables and functions */
 int ENOATTR ; 
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  EXTATTR_NAMESPACE_SYSTEM ; 
 int /*<<< orphan*/  IO_NODELOCKED ; 
 scalar_t__ LK_EXCLUSIVE ; 
 int /*<<< orphan*/  LK_SHARED ; 
 int MNT_EXPORTED ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  NFSBCOPY (char*,struct pnfsdsattr*,int) ; 
 int NFSDEV_MAXMIRRORS ; 
 int /*<<< orphan*/  NFSD_DEBUG (int,char*,...) ; 
 int /*<<< orphan*/  NFSLOCKMNT (struct nfsmount*) ; 
 int NFSMNTP_CANCELRPCS ; 
 int NFSMNTP_FORCEDISM ; 
 int NFSPROC_GETATTR ; 
 int NFSPROC_READDS ; 
 int NFSPROC_SETACL ; 
 int NFSPROC_SETATTR ; 
 int NFSPROC_WRITEDS ; 
 int /*<<< orphan*/  NFSUNLOCKMNT (struct nfsmount*) ; 
 scalar_t__ NFSVOPISLOCKED (struct vnode*) ; 
 int /*<<< orphan*/  NFSVOPUNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PNFSDOP_DELDSSERVER ; 
 struct nfsmount* VFSTONFS (TYPE_1__*) ; 
 scalar_t__ VREG ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nfsds_failerr (int) ; 
 scalar_t__ nfsrv_checkdsattr (struct vnode*,struct thread*) ; 
 struct nfsdevice* nfsrv_deldsnmp (int /*<<< orphan*/ ,struct nfsmount*,struct thread*) ; 
 scalar_t__ nfsrv_devidcnt ; 
 int nfsrv_dsgetsockmnt (struct vnode*,int /*<<< orphan*/ ,char*,int*,int*,struct thread*,struct vnode**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nfsrv_getattrdsrpc (int /*<<< orphan*/ *,struct ucred*,struct thread*,struct vnode*,struct nfsmount*,struct nfsvattr*) ; 
 int /*<<< orphan*/  nfsrv_killrpcs (struct nfsmount*) ; 
 scalar_t__ nfsrv_pnfsgetdsattr ; 
 int nfsrv_readdsrpc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct ucred*,struct thread*,struct nfsmount*,struct mbuf**,struct mbuf**) ; 
 int nfsrv_setacldsrpc (int /*<<< orphan*/ *,struct ucred*,struct thread*,struct vnode*,struct nfsmount**,int,struct acl*,int*) ; 
 int nfsrv_setattrdsrpc (int /*<<< orphan*/ *,struct ucred*,struct thread*,struct vnode*,struct nfsmount**,int,struct nfsvattr*,int*) ; 
 int nfsrv_writedsrpc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct ucred*,struct thread*,struct vnode*,struct nfsmount**,int,struct mbuf**,char*,int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int vn_extattr_get (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,char*,struct thread*) ; 
 int /*<<< orphan*/  wakeup (struct nfsmount*) ; 

__attribute__((used)) static int
nfsrv_proxyds(struct vnode *vp, off_t off, int cnt, struct ucred *cred,
    struct thread *p, int ioproc, struct mbuf **mpp, char *cp,
    struct mbuf **mpp2, struct nfsvattr *nap, struct acl *aclp)
{
	struct nfsmount *nmp[NFSDEV_MAXMIRRORS], *failnmp;
	fhandle_t fh[NFSDEV_MAXMIRRORS];
	struct vnode *dvp[NFSDEV_MAXMIRRORS];
	struct nfsdevice *ds;
	struct pnfsdsattr dsattr;
	char *buf;
	int buflen, error, failpos, i, mirrorcnt, origmircnt, trycnt;

	NFSD_DEBUG(4, "in nfsrv_proxyds\n");
	/*
	 * If not a regular file, not exported or not a pNFS server,
	 * just return ENOENT.
	 */
	if (vp->v_type != VREG || (vp->v_mount->mnt_flag & MNT_EXPORTED) == 0 ||
	    nfsrv_devidcnt == 0)
		return (ENOENT);

	buflen = 1024;
	buf = malloc(buflen, M_TEMP, M_WAITOK);
	error = 0;

	/*
	 * For Getattr, get the Change attribute (va_filerev) and size (va_size)
	 * from the MetaData file's extended attribute.
	 */
	if (ioproc == NFSPROC_GETATTR) {
		error = vn_extattr_get(vp, IO_NODELOCKED,
		    EXTATTR_NAMESPACE_SYSTEM, "pnfsd.dsattr", &buflen, buf,
		    p);
		if (error == 0 && buflen != sizeof(dsattr))
			error = ENXIO;
		if (error == 0) {
			NFSBCOPY(buf, &dsattr, buflen);
			nap->na_filerev = dsattr.dsa_filerev;
			nap->na_size = dsattr.dsa_size;
			nap->na_atime = dsattr.dsa_atime;
			nap->na_mtime = dsattr.dsa_mtime;

			/*
			 * If nfsrv_pnfsgetdsattr is 0 or nfsrv_checkdsattr()
			 * returns 0, just return now.  nfsrv_checkdsattr()
			 * returns 0 if there is no Read/Write layout
			 * plus either an Open/Write_access or Write
			 * delegation issued to a client for the file.
			 */
			if (nfsrv_pnfsgetdsattr == 0 ||
			    nfsrv_checkdsattr(vp, p) == 0) {
				free(buf, M_TEMP);
				return (error);
			}
		}

		/*
		 * Clear ENOATTR so the code below will attempt to do a
		 * nfsrv_getattrdsrpc() to get the attributes and (re)create
		 * the extended attribute.
		 */
		if (error == ENOATTR)
			error = 0;
	}

	origmircnt = -1;
	trycnt = 0;
tryagain:
	if (error == 0) {
		buflen = 1024;
		if (ioproc == NFSPROC_READDS && NFSVOPISLOCKED(vp) ==
		    LK_EXCLUSIVE)
			printf("nfsrv_proxyds: Readds vp exclusively locked\n");
		error = nfsrv_dsgetsockmnt(vp, LK_SHARED, buf, &buflen,
		    &mirrorcnt, p, dvp, fh, NULL, NULL, NULL, NULL, NULL,
		    NULL, NULL);
		if (error == 0) {
			for (i = 0; i < mirrorcnt; i++)
				nmp[i] = VFSTONFS(dvp[i]->v_mount);
		} else
			printf("pNFS: proxy getextattr sockaddr=%d\n", error);
	} else
		printf("pNFS: nfsrv_dsgetsockmnt=%d\n", error);
	if (error == 0) {
		failpos = -1;
		if (origmircnt == -1)
			origmircnt = mirrorcnt;
		/*
		 * If failpos is set to a mirror#, then that mirror has
		 * failed and will be disabled. For Read and Getattr, the
		 * function only tries one mirror, so if that mirror has
		 * failed, it will need to be retried. As such, increment
		 * tryitagain for these cases.
		 * For Write, Setattr and Setacl, the function tries all
		 * mirrors and will not return an error for the case where
		 * one mirror has failed. For these cases, the functioning
		 * mirror(s) will have been modified, so a retry isn't
		 * necessary. These functions will set failpos for the
		 * failed mirror#.
		 */
		if (ioproc == NFSPROC_READDS) {
			error = nfsrv_readdsrpc(fh, off, cnt, cred, p, nmp[0],
			    mpp, mpp2);
			if (nfsds_failerr(error) && mirrorcnt > 1) {
				/*
				 * Setting failpos will cause the mirror
				 * to be disabled and then a retry of this
				 * read is required.
				 */
				failpos = 0;
				error = 0;
				trycnt++;
			}
		} else if (ioproc == NFSPROC_WRITEDS)
			error = nfsrv_writedsrpc(fh, off, cnt, cred, p, vp,
			    &nmp[0], mirrorcnt, mpp, cp, &failpos);
		else if (ioproc == NFSPROC_SETATTR)
			error = nfsrv_setattrdsrpc(fh, cred, p, vp, &nmp[0],
			    mirrorcnt, nap, &failpos);
		else if (ioproc == NFSPROC_SETACL)
			error = nfsrv_setacldsrpc(fh, cred, p, vp, &nmp[0],
			    mirrorcnt, aclp, &failpos);
		else {
			error = nfsrv_getattrdsrpc(&fh[mirrorcnt - 1], cred, p,
			    vp, nmp[mirrorcnt - 1], nap);
			if (nfsds_failerr(error) && mirrorcnt > 1) {
				/*
				 * Setting failpos will cause the mirror
				 * to be disabled and then a retry of this
				 * getattr is required.
				 */
				failpos = mirrorcnt - 1;
				error = 0;
				trycnt++;
			}
		}
		ds = NULL;
		if (failpos >= 0) {
			failnmp = nmp[failpos];
			NFSLOCKMNT(failnmp);
			if ((failnmp->nm_privflag & (NFSMNTP_FORCEDISM |
			     NFSMNTP_CANCELRPCS)) == 0) {
				failnmp->nm_privflag |= NFSMNTP_CANCELRPCS;
				NFSUNLOCKMNT(failnmp);
				ds = nfsrv_deldsnmp(PNFSDOP_DELDSSERVER,
				    failnmp, p);
				NFSD_DEBUG(4, "dsldsnmp fail=%d ds=%p\n",
				    failpos, ds);
				if (ds != NULL)
					nfsrv_killrpcs(failnmp);
				NFSLOCKMNT(failnmp);
				failnmp->nm_privflag &= ~NFSMNTP_CANCELRPCS;
				wakeup(failnmp);
			}
			NFSUNLOCKMNT(failnmp);
		}
		for (i = 0; i < mirrorcnt; i++)
			NFSVOPUNLOCK(dvp[i], 0);
		NFSD_DEBUG(4, "nfsrv_proxyds: aft RPC=%d trya=%d\n", error,
		    trycnt);
		/* Try the Read/Getattr again if a mirror was deleted. */
		if (ds != NULL && trycnt > 0 && trycnt < origmircnt)
			goto tryagain;
	} else {
		/* Return ENOENT for any Extended Attribute error. */
		error = ENOENT;
	}
	free(buf, M_TEMP);
	NFSD_DEBUG(4, "nfsrv_proxyds: error=%d\n", error);
	return (error);
}