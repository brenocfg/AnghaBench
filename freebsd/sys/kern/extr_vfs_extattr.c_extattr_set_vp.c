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
struct uio {int uio_iovcnt; size_t uio_resid; struct thread* uio_td; int /*<<< orphan*/  uio_segflg; int /*<<< orphan*/  uio_rw; scalar_t__ uio_offset; struct iovec* uio_iov; } ;
struct thread {size_t* td_retval; int /*<<< orphan*/  td_ucred; } ;
struct mount {int dummy; } ;
struct iovec {size_t iov_len; void* iov_base; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 size_t IOSIZE_MAX ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int PCATCH ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int VOP_SETEXTATTR (struct vnode*,int,char const*,struct uio*,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int V_WAIT ; 
 int mac_vnode_check_setextattr (int /*<<< orphan*/ ,struct vnode*,int,char const*) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 
 int vn_start_write (struct vnode*,struct mount**,int) ; 

__attribute__((used)) static int
extattr_set_vp(struct vnode *vp, int attrnamespace, const char *attrname,
    void *data, size_t nbytes, struct thread *td)
{
	struct mount *mp;
	struct uio auio;
	struct iovec aiov;
	ssize_t cnt;
	int error;

	if (nbytes > IOSIZE_MAX)
		return (EINVAL);

	error = vn_start_write(vp, &mp, V_WAIT | PCATCH);
	if (error)
		return (error);
	vn_lock(vp, LK_EXCLUSIVE | LK_RETRY);

	aiov.iov_base = data;
	aiov.iov_len = nbytes;
	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	auio.uio_offset = 0;
	auio.uio_resid = nbytes;
	auio.uio_rw = UIO_WRITE;
	auio.uio_segflg = UIO_USERSPACE;
	auio.uio_td = td;
	cnt = nbytes;

#ifdef MAC
	error = mac_vnode_check_setextattr(td->td_ucred, vp, attrnamespace,
	    attrname);
	if (error)
		goto done;
#endif

	error = VOP_SETEXTATTR(vp, attrnamespace, attrname, &auio,
	    td->td_ucred, td);
	cnt -= auio.uio_resid;
	td->td_retval[0] = cnt;

#ifdef MAC
done:
#endif
	VOP_UNLOCK(vp, 0);
	vn_finished_write(mp);
	return (error);
}