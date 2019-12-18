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
struct vnode {int dummy; } ;
struct uio {int uio_iovcnt; int uio_offset; int uio_rw; int uio_resid; int /*<<< orphan*/  uio_td; int /*<<< orphan*/  uio_segflg; struct iovec* uio_iov; } ;
struct mount {int dummy; } ;
struct iovec {int dummy; } ;
struct beri_vtblk_softc {int /*<<< orphan*/  cred; struct vnode* vnode; } ;
typedef  int /*<<< orphan*/  auio ;

/* Variables and functions */
 int /*<<< orphan*/  IO_DIRECT ; 
 int /*<<< orphan*/  IO_SYNC ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int VOP_READ (struct vnode*,struct uio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int VOP_WRITE (struct vnode*,struct uio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_WAIT ; 
 int /*<<< orphan*/  bzero (struct uio*,int) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int /*<<< orphan*/  vn_start_write (struct vnode*,struct mount**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vtblk_rdwr(struct beri_vtblk_softc *sc, struct iovec *iov,
	int cnt, int offset, int operation, int iolen)
{
	struct vnode *vp;
	struct mount *mp;
	struct uio auio;
	int error;

	bzero(&auio, sizeof(auio));

	vp = sc->vnode;

	KASSERT(vp != NULL, ("file not opened"));

	auio.uio_iov = iov;
	auio.uio_iovcnt = cnt;
	auio.uio_offset = offset;
	auio.uio_segflg = UIO_SYSSPACE;
	auio.uio_rw = operation;
	auio.uio_resid = iolen;
	auio.uio_td = curthread;

	if (operation == 0) {
		vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
		error = VOP_READ(vp, &auio, IO_DIRECT, sc->cred);
		VOP_UNLOCK(vp, 0);
	} else {
		(void) vn_start_write(vp, &mp, V_WAIT);
		vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);
		error = VOP_WRITE(vp, &auio, IO_SYNC, sc->cred);
		VOP_UNLOCK(vp, 0);
		vn_finished_write(mp);
	}

	return (error);
}