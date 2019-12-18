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
typedef  int /*<<< orphan*/  vnode_t ;
struct nfsnode {TYPE_1__* n_fhp; } ;
struct nfsmount {struct nfsclclient* nm_clp; } ;
struct nfscllayout {int nfsly_flags; int /*<<< orphan*/  nfsly_lock; } ;
struct nfsclclient {int /*<<< orphan*/  nfsc_nmp; } ;
typedef  int /*<<< orphan*/  mount_t ;
struct TYPE_2__ {int /*<<< orphan*/  nfh_len; int /*<<< orphan*/  nfh_fh; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  NFSCLSTATEMUTEXPTR ; 
 int /*<<< orphan*/  NFSCL_DEBUG (int,char*) ; 
 scalar_t__ NFSCL_FORCEDISM (int /*<<< orphan*/ ) ; 
 scalar_t__ NFSHASNOLAYOUTCOMMIT (struct nfsmount*) ; 
 int /*<<< orphan*/  NFSLOCKCLSTATE () ; 
 int NFSLY_WRITTEN ; 
 int /*<<< orphan*/  NFSPROCCRED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NFSUNLOCKCLSTATE () ; 
 struct nfsmount* VFSTONFS (int /*<<< orphan*/ ) ; 
 struct nfsnode* VTONFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfscl_dolayoutcommit (int /*<<< orphan*/ ,struct nfscllayout*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nfscllayout* nfscl_findlayout (struct nfsclclient*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsv4_getref (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsv4_relref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnode_mount (int /*<<< orphan*/ ) ; 

int
nfscl_layoutcommit(vnode_t vp, NFSPROC_T *p)
{
	struct nfsclclient *clp;
	struct nfscllayout *lyp;
	struct nfsnode *np = VTONFS(vp);
	mount_t mp;
	struct nfsmount *nmp;

	mp = vnode_mount(vp);
	nmp = VFSTONFS(mp);
	if (NFSHASNOLAYOUTCOMMIT(nmp))
		return (0);
	NFSLOCKCLSTATE();
	clp = nmp->nm_clp;
	if (clp == NULL) {
		NFSUNLOCKCLSTATE();
		return (EPERM);
	}
	lyp = nfscl_findlayout(clp, np->n_fhp->nfh_fh, np->n_fhp->nfh_len);
	if (lyp == NULL) {
		NFSUNLOCKCLSTATE();
		return (EPERM);
	}
	nfsv4_getref(&lyp->nfsly_lock, NULL, NFSCLSTATEMUTEXPTR, mp);
	if (NFSCL_FORCEDISM(mp)) {
		NFSUNLOCKCLSTATE();
		return (EPERM);
	}
tryagain:
	if ((lyp->nfsly_flags & NFSLY_WRITTEN) != 0) {
		lyp->nfsly_flags &= ~NFSLY_WRITTEN;
		NFSUNLOCKCLSTATE();
		NFSCL_DEBUG(4, "do layoutcommit2\n");
		nfscl_dolayoutcommit(clp->nfsc_nmp, lyp, NFSPROCCRED(p), p);
		NFSLOCKCLSTATE();
		goto tryagain;
	}
	nfsv4_relref(&lyp->nfsly_lock);
	NFSUNLOCKCLSTATE();
	return (0);
}