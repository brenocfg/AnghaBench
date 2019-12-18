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
struct TYPE_2__ {int bo_bsize; } ;
struct vnode {scalar_t__ v_type; TYPE_1__ v_bufobj; struct mount* v_mount; } ;
struct thread {int dummy; } ;
struct nfsmount {int nm_flag; } ;
struct mount {int dummy; } ;
struct buf {int b_blkno; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int daddr_t ;

/* Variables and functions */
 int DEV_BSIZE ; 
 int NFSMNT_INT ; 
 int /*<<< orphan*/  PCATCH ; 
 struct nfsmount* VFSTONFS (struct mount*) ; 
 scalar_t__ VREG ; 
 struct buf* getblk (struct vnode*,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  newnfs_restore_sigmask (struct thread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  newnfs_set_sigmask (struct thread*,int /*<<< orphan*/ *) ; 
 scalar_t__ newnfs_sigintr (struct nfsmount*,struct thread*) ; 

__attribute__((used)) static struct buf *
nfs_getcacheblk(struct vnode *vp, daddr_t bn, int size, struct thread *td)
{
	struct buf *bp;
	struct mount *mp;
	struct nfsmount *nmp;

	mp = vp->v_mount;
	nmp = VFSTONFS(mp);

	if (nmp->nm_flag & NFSMNT_INT) {
		sigset_t oldset;

		newnfs_set_sigmask(td, &oldset);
		bp = getblk(vp, bn, size, PCATCH, 0, 0);
		newnfs_restore_sigmask(td, &oldset);
		while (bp == NULL) {
			if (newnfs_sigintr(nmp, td))
				return (NULL);
			bp = getblk(vp, bn, size, 0, 2 * hz, 0);
		}
	} else {
		bp = getblk(vp, bn, size, 0, 0, 0);
	}

	if (vp->v_type == VREG)
		bp->b_blkno = bn * (vp->v_bufobj.bo_bsize / DEV_BSIZE);
	return (bp);
}