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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int ;
struct vnode {int v_iflag; } ;
struct thread {int dummy; } ;
struct nfsnode {int dummy; } ;
struct nfsfh {int nfh_len; int /*<<< orphan*/ * nfh_fh; } ;
struct mount {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINTR ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  FNV1_32_INIT ; 
 int LK_EXCLUSIVE ; 
 int LK_NOWAIT ; 
 int /*<<< orphan*/  M_NFSFH ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ NFSCL_FORCEDISM (struct mount*) ; 
 int /*<<< orphan*/  NFSVOPUNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int VI_DOOMED ; 
 struct nfsnode* VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fnv_32_buf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct nfsfh*,int /*<<< orphan*/ ) ; 
 struct nfsfh* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  newnfs_vncmpf ; 
 int vfs_hash_get (struct mount*,int /*<<< orphan*/ ,int,struct thread*,struct vnode**,int /*<<< orphan*/ ,struct nfsfh*) ; 
 int /*<<< orphan*/  vfs_hash_ref (struct mount*,int /*<<< orphan*/ ,struct thread*,struct vnode**,int /*<<< orphan*/ ,struct nfsfh*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

int
nfscl_ngetreopen(struct mount *mntp, u_int8_t *fhp, int fhsize,
    struct thread *td, struct nfsnode **npp)
{
	struct vnode *nvp;
	u_int hash;
	struct nfsfh *nfhp;
	int error;

	*npp = NULL;
	/* For forced dismounts, just return error. */
	if (NFSCL_FORCEDISM(mntp))
		return (EINTR);
	nfhp = malloc(sizeof (struct nfsfh) + fhsize,
	    M_NFSFH, M_WAITOK);
	bcopy(fhp, &nfhp->nfh_fh[0], fhsize);
	nfhp->nfh_len = fhsize;

	hash = fnv_32_buf(fhp, fhsize, FNV1_32_INIT);

	/*
	 * First, try to get the vnode locked, but don't block for the lock.
	 */
	error = vfs_hash_get(mntp, hash, (LK_EXCLUSIVE | LK_NOWAIT), td, &nvp,
	    newnfs_vncmpf, nfhp);
	if (error == 0 && nvp != NULL) {
		NFSVOPUNLOCK(nvp, 0);
	} else if (error == EBUSY) {
		/*
		 * It is safe so long as a vflush() with
		 * FORCECLOSE has not been done. Since the Renew thread is
		 * stopped and the MNTK_UNMOUNTF flag is set before doing
		 * a vflush() with FORCECLOSE, we should be ok here.
		 */
		if (NFSCL_FORCEDISM(mntp))
			error = EINTR;
		else {
			vfs_hash_ref(mntp, hash, td, &nvp, newnfs_vncmpf, nfhp);
			if (nvp == NULL) {
				error = ENOENT;
			} else if ((nvp->v_iflag & VI_DOOMED) != 0) {
				error = ENOENT;
				vrele(nvp);
			} else {
				error = 0;
			}
		}
	}
	free(nfhp, M_NFSFH);
	if (error)
		return (error);
	if (nvp != NULL) {
		*npp = VTONFS(nvp);
		return (0);
	}
	return (EINVAL);
}