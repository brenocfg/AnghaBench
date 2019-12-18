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
typedef  int /*<<< orphan*/  u_int32_t ;
struct vnode {int v_type; TYPE_1__* v_mount; } ;
struct vattr {scalar_t__ va_uid; } ;
struct ucred {scalar_t__ cr_uid; } ;
struct thread {int dummy; } ;
struct nfsexstuff {int dummy; } ;
typedef  int accmode_t ;
struct TYPE_2__ {int mnt_flag; } ;

/* Variables and functions */
 int EACCES ; 
 int EPERM ; 
 int EROFS ; 
 int ETXTBSY ; 
 int /*<<< orphan*/  LK_SHARED ; 
 int MNT_RDONLY ; 
 int NFSACCCHK_ALLOWOWNER ; 
 int NFSACCCHK_ALLOWROOT ; 
 int NFSACCCHK_NOOVERRIDE ; 
 int /*<<< orphan*/  NFSACCESS_DELETE ; 
 int /*<<< orphan*/  NFSEXITCODE (int) ; 
 scalar_t__ NFSVNO_EXRDONLY (struct nfsexstuff*) ; 
 scalar_t__ NFSVOPLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSVOPUNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int VDELETE ; 
 int VDELETE_CHILD ; 
#define  VDIR 130 
 int VEXPLICIT_DENY ; 
#define  VLNK 129 
 int VOP_ACCESSX (struct vnode*,int,struct ucred*,struct thread*) ; 
 int VOP_GETATTR (struct vnode*,struct vattr*,struct ucred*) ; 
 scalar_t__ VOP_IS_TEXT (struct vnode*) ; 
#define  VREG 128 
 int VWRITE ; 

int
nfsvno_accchk(struct vnode *vp, accmode_t accmode, struct ucred *cred,
    struct nfsexstuff *exp, struct thread *p, int override, int vpislocked,
    u_int32_t *supportedtypep)
{
	struct vattr vattr;
	int error = 0, getret = 0;

	if (vpislocked == 0) {
		if (NFSVOPLOCK(vp, LK_SHARED) != 0) {
			error = EPERM;
			goto out;
		}
	}
	if (accmode & VWRITE) {
		/* Just vn_writechk() changed to check rdonly */
		/*
		 * Disallow write attempts on read-only file systems;
		 * unless the file is a socket or a block or character
		 * device resident on the file system.
		 */
		if (NFSVNO_EXRDONLY(exp) ||
		    (vp->v_mount->mnt_flag & MNT_RDONLY)) {
			switch (vp->v_type) {
			case VREG:
			case VDIR:
			case VLNK:
				error = EROFS;
			default:
				break;
			}
		}
		/*
		 * If there's shared text associated with
		 * the inode, try to free it up once.  If
		 * we fail, we can't allow writing.
		 */
		if (VOP_IS_TEXT(vp) && error == 0)
			error = ETXTBSY;
	}
	if (error != 0) {
		if (vpislocked == 0)
			NFSVOPUNLOCK(vp, 0);
		goto out;
	}

	/*
	 * Should the override still be applied when ACLs are enabled?
	 */
	error = VOP_ACCESSX(vp, accmode, cred, p);
	if (error != 0 && (accmode & (VDELETE | VDELETE_CHILD))) {
		/*
		 * Try again with VEXPLICIT_DENY, to see if the test for
		 * deletion is supported.
		 */
		error = VOP_ACCESSX(vp, accmode | VEXPLICIT_DENY, cred, p);
		if (error == 0) {
			if (vp->v_type == VDIR) {
				accmode &= ~(VDELETE | VDELETE_CHILD);
				accmode |= VWRITE;
				error = VOP_ACCESSX(vp, accmode, cred, p);
			} else if (supportedtypep != NULL) {
				*supportedtypep &= ~NFSACCESS_DELETE;
			}
		}
	}

	/*
	 * Allow certain operations for the owner (reads and writes
	 * on files that are already open).
	 */
	if (override != NFSACCCHK_NOOVERRIDE &&
	    (error == EPERM || error == EACCES)) {
		if (cred->cr_uid == 0 && (override & NFSACCCHK_ALLOWROOT))
			error = 0;
		else if (override & NFSACCCHK_ALLOWOWNER) {
			getret = VOP_GETATTR(vp, &vattr, cred);
			if (getret == 0 && cred->cr_uid == vattr.va_uid)
				error = 0;
		}
	}
	if (vpislocked == 0)
		NFSVOPUNLOCK(vp, 0);

out:
	NFSEXITCODE(error);
	return (error);
}