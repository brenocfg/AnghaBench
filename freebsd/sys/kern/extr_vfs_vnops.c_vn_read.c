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
struct uio {scalar_t__ uio_offset; struct thread* uio_td; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct file {int f_flag; scalar_t__ f_nextoff; int /*<<< orphan*/  f_cred; struct vnode* f_vnode; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int FNONBLOCK ; 
 int FOF_OFFSET ; 
 int IO_DIRECT ; 
 int IO_NDELAY ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 int O_DIRECT ; 
 int /*<<< orphan*/  POSIX_FADV_DONTNEED ; 
#define  POSIX_FADV_NOREUSE 131 
#define  POSIX_FADV_NORMAL 130 
#define  POSIX_FADV_RANDOM 129 
#define  POSIX_FADV_SEQUENTIAL 128 
 int VOP_ADVISE (struct vnode*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int VOP_READ (struct vnode*,struct uio*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int get_advice (struct file*,struct uio*) ; 
 int mac_vnode_check_read (struct ucred*,int /*<<< orphan*/ ,struct vnode*) ; 
 int sequential_heuristic (struct uio*,struct file*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

__attribute__((used)) static int
vn_read(struct file *fp, struct uio *uio, struct ucred *active_cred, int flags,
    struct thread *td)
{
	struct vnode *vp;
	off_t orig_offset;
	int error, ioflag;
	int advice;

	KASSERT(uio->uio_td == td, ("uio_td %p is not td %p",
	    uio->uio_td, td));
	KASSERT(flags & FOF_OFFSET, ("No FOF_OFFSET"));
	vp = fp->f_vnode;
	ioflag = 0;
	if (fp->f_flag & FNONBLOCK)
		ioflag |= IO_NDELAY;
	if (fp->f_flag & O_DIRECT)
		ioflag |= IO_DIRECT;
	advice = get_advice(fp, uio);
	vn_lock(vp, LK_SHARED | LK_RETRY);

	switch (advice) {
	case POSIX_FADV_NORMAL:
	case POSIX_FADV_SEQUENTIAL:
	case POSIX_FADV_NOREUSE:
		ioflag |= sequential_heuristic(uio, fp);
		break;
	case POSIX_FADV_RANDOM:
		/* Disable read-ahead for random I/O. */
		break;
	}
	orig_offset = uio->uio_offset;

#ifdef MAC
	error = mac_vnode_check_read(active_cred, fp->f_cred, vp);
	if (error == 0)
#endif
		error = VOP_READ(vp, uio, ioflag, fp->f_cred);
	fp->f_nextoff = uio->uio_offset;
	VOP_UNLOCK(vp, 0);
	if (error == 0 && advice == POSIX_FADV_NOREUSE &&
	    orig_offset != uio->uio_offset)
		/*
		 * Use POSIX_FADV_DONTNEED to flush pages and buffers
		 * for the backing file after a POSIX_FADV_NOREUSE
		 * read(2).
		 */
		error = VOP_ADVISE(vp, orig_offset, uio->uio_offset - 1,
		    POSIX_FADV_DONTNEED);
	return (error);
}