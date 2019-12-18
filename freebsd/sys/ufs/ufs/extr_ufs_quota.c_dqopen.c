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
typedef  scalar_t__ uint32_t ;
struct vnode {int dummy; } ;
struct uio {int uio_iovcnt; int uio_resid; struct thread* uio_td; int /*<<< orphan*/  uio_rw; int /*<<< orphan*/  uio_segflg; scalar_t__ uio_offset; struct iovec* uio_iov; } ;
struct ufsmount {int /*<<< orphan*/ * um_qflags; int /*<<< orphan*/ * um_cred; } ;
struct thread {int dummy; } ;
struct iovec {int iov_len; struct dqhdr64* iov_base; } ;
struct dqhdr64 {int /*<<< orphan*/  dqh_reclen; int /*<<< orphan*/  dqh_hdrlen; int /*<<< orphan*/  dqh_version; int /*<<< orphan*/  dqh_magic; } ;
struct dqblk64 {int dummy; } ;
typedef  int /*<<< orphan*/  dqh ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_LOCKED (struct vnode*,char*) ; 
 int /*<<< orphan*/  QTF_64BIT ; 
 int /*<<< orphan*/  Q_DQHDR64_MAGIC ; 
 scalar_t__ Q_DQHDR64_VERSION ; 
 int /*<<< orphan*/  UFS_LOCK (struct ufsmount*) ; 
 int /*<<< orphan*/  UFS_UNLOCK (struct ufsmount*) ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int VOP_READ (struct vnode*,struct uio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ be32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dqopen(struct vnode *vp, struct ufsmount *ump, int type)
{
	struct dqhdr64 dqh;
	struct iovec aiov;
	struct uio auio;
	int error;

	ASSERT_VOP_LOCKED(vp, "dqopen");
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	aiov.iov_base = &dqh;
	aiov.iov_len = sizeof(dqh);
	auio.uio_resid = sizeof(dqh);
	auio.uio_offset = 0;
	auio.uio_segflg = UIO_SYSSPACE;
	auio.uio_rw = UIO_READ;
	auio.uio_td = (struct thread *)0;
	error = VOP_READ(vp, &auio, 0, ump->um_cred[type]);

	if (error != 0)
		return (error);
	if (auio.uio_resid > 0) {
		/* assume 32 bits */
		return (0);
	}

	UFS_LOCK(ump);
	if (strcmp(dqh.dqh_magic, Q_DQHDR64_MAGIC) == 0 &&
	    be32toh(dqh.dqh_version) == Q_DQHDR64_VERSION &&
	    be32toh(dqh.dqh_hdrlen) == (uint32_t)sizeof(struct dqhdr64) &&
	    be32toh(dqh.dqh_reclen) == (uint32_t)sizeof(struct dqblk64)) {
		/* XXX: what if the magic matches, but the sizes are wrong? */
		ump->um_qflags[type] |= QTF_64BIT;
	} else {
		ump->um_qflags[type] &= ~QTF_64BIT;
	}
	UFS_UNLOCK(ump);

	return (0);
}