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
struct vnode {scalar_t__ v_type; int v_vflag; } ;
struct uio {int uio_iovcnt; int uio_segflg; size_t uio_resid; struct thread* uio_td; int /*<<< orphan*/  uio_rw; scalar_t__ uio_offset; struct iovec* uio_iov; } ;
struct thread {size_t* td_retval; int /*<<< orphan*/  td_ucred; } ;
struct iovec {char* iov_base; size_t iov_len; } ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_LOCKED (struct vnode*,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  UIO_READ ; 
 scalar_t__ VLNK ; 
 int VOP_READLINK (struct vnode*,struct uio*,int /*<<< orphan*/ ) ; 
 int VV_READLINK ; 
 int mac_vnode_check_readlink (int /*<<< orphan*/ ,struct vnode*) ; 

__attribute__((used)) static int
kern_readlink_vp(struct vnode *vp, char *buf, enum uio_seg bufseg, size_t count,
    struct thread *td)
{
	struct iovec aiov;
	struct uio auio;
	int error;

	ASSERT_VOP_LOCKED(vp, "kern_readlink_vp(): vp not locked");
#ifdef MAC
	error = mac_vnode_check_readlink(td->td_ucred, vp);
	if (error != 0)
		return (error);
#endif
	if (vp->v_type != VLNK && (vp->v_vflag & VV_READLINK) == 0)
		return (EINVAL);

	aiov.iov_base = buf;
	aiov.iov_len = count;
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	auio.uio_offset = 0;
	auio.uio_rw = UIO_READ;
	auio.uio_segflg = bufseg;
	auio.uio_td = td;
	auio.uio_resid = count;
	error = VOP_READLINK(vp, &auio, td->td_ucred);
	td->td_retval[0] = count - auio.uio_resid;
	return (error);
}