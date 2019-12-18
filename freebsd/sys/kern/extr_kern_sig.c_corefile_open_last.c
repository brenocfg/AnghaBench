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
struct vnode {int dummy; } ;
struct timespec {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
struct vattr {struct timespec va_mtime; } ;
struct thread {TYPE_1__* td_proc; int /*<<< orphan*/  td_ucred; } ;
struct nameidata {struct vnode* ni_vp; } ;
struct TYPE_2__ {int p_flag; } ;

/* Variables and functions */
 int EFAULT ; 
 int FWRITE ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct thread*) ; 
 int /*<<< orphan*/  NOFOLLOW ; 
 int O_CREAT ; 
 int O_NOFOLLOW ; 
 int P_SUGID ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int VN_OPEN_NAMECACHE ; 
 int VN_OPEN_NOAUDIT ; 
 int VN_OPEN_NOCAPCHECK ; 
 int VOP_GETATTR (struct vnode*,struct vattr*,int /*<<< orphan*/ ) ; 
 scalar_t__ capmode_coredump ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int vn_open_cred (struct nameidata*,int*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vnode_close_locked (struct thread*,struct vnode*) ; 

__attribute__((used)) static int
corefile_open_last(struct thread *td, char *name, int indexpos,
    int indexlen, int ncores, struct vnode **vpp)
{
	struct vnode *oldvp, *nextvp, *vp;
	struct vattr vattr;
	struct nameidata nd;
	int error, i, flags, oflags, cmode;
	char ch;
	struct timespec lasttime;

	nextvp = oldvp = NULL;
	cmode = S_IRUSR | S_IWUSR;
	oflags = VN_OPEN_NOAUDIT | VN_OPEN_NAMECACHE |
	    (capmode_coredump ? VN_OPEN_NOCAPCHECK : 0);

	for (i = 0; i < ncores; i++) {
		flags = O_CREAT | FWRITE | O_NOFOLLOW;

		ch = name[indexpos + indexlen];
		(void)snprintf(name + indexpos, indexlen + 1, "%.*u", indexlen,
		    i);
		name[indexpos + indexlen] = ch;

		NDINIT(&nd, LOOKUP, NOFOLLOW, UIO_SYSSPACE, name, td);
		error = vn_open_cred(&nd, &flags, cmode, oflags, td->td_ucred,
		    NULL);
		if (error != 0)
			break;

		vp = nd.ni_vp;
		NDFREE(&nd, NDF_ONLY_PNBUF);
		if ((flags & O_CREAT) == O_CREAT) {
			nextvp = vp;
			break;
		}

		error = VOP_GETATTR(vp, &vattr, td->td_ucred);
		if (error != 0) {
			vnode_close_locked(td, vp);
			break;
		}

		if (oldvp == NULL ||
		    lasttime.tv_sec > vattr.va_mtime.tv_sec ||
		    (lasttime.tv_sec == vattr.va_mtime.tv_sec &&
		    lasttime.tv_nsec >= vattr.va_mtime.tv_nsec)) {
			if (oldvp != NULL)
				vnode_close_locked(td, oldvp);
			oldvp = vp;
			lasttime = vattr.va_mtime;
		} else {
			vnode_close_locked(td, vp);
		}
	}

	if (oldvp != NULL) {
		if (nextvp == NULL) {
			if ((td->td_proc->p_flag & P_SUGID) != 0) {
				error = EFAULT;
				vnode_close_locked(td, oldvp);
			} else {
				nextvp = oldvp;
			}
		} else {
			vnode_close_locked(td, oldvp);
		}
	}
	if (error != 0) {
		if (nextvp != NULL)
			vnode_close_locked(td, oldvp);
	} else {
		*vpp = nextvp;
	}

	return (error);
}