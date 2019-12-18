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
typedef  int /*<<< orphan*/  uint32_t ;
struct vnode {int v_type; } ;
struct vattr {int /*<<< orphan*/  va_gid; int /*<<< orphan*/  va_uid; int /*<<< orphan*/  va_mode; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct mount {int dummy; } ;
struct fuse_dispatcher {struct fuse_access_in* indata; } ;
struct fuse_data {int dataflags; int /*<<< orphan*/  daemoncred; } ;
struct fuse_access_in {int /*<<< orphan*/  mask; } ;
typedef  int accmode_t ;

/* Variables and functions */
 int ENOSYS ; 
 int EPERM ; 
 int EROFS ; 
 int FSESS_DAEMON_CAN_SPY ; 
 int FSESS_DEFAULT_PERMISSIONS ; 
 int /*<<< orphan*/  FUSE_ACCESS ; 
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/  R_OK ; 
 int VADMIN ; 
 int VAPPEND ; 
#define  VDIR 130 
 int VEXEC ; 
#define  VLNK 129 
 int VMODIFY_PERMS ; 
 int VREAD ; 
#define  VREG 128 
 int VWRITE ; 
 int /*<<< orphan*/  W_OK ; 
 int /*<<< orphan*/  X_OK ; 
 int /*<<< orphan*/  fdisp_destroy (struct fuse_dispatcher*) ; 
 int /*<<< orphan*/  fdisp_init (struct fuse_dispatcher*,int) ; 
 int /*<<< orphan*/  fdisp_make_vp (struct fuse_dispatcher*,int /*<<< orphan*/ ,struct vnode*,struct thread*,struct ucred*) ; 
 int fdisp_wait_answ (struct fuse_dispatcher*) ; 
 int /*<<< orphan*/  fsess_isimpl (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsess_set_notimpl (struct mount*,int /*<<< orphan*/ ) ; 
 struct fuse_data* fuse_get_mpdata (struct mount*) ; 
 int /*<<< orphan*/  fuse_internal_getattr (struct vnode*,struct vattr*,struct ucred*,struct thread*) ; 
 scalar_t__ fuse_match_cred (int /*<<< orphan*/ ,struct ucred*) ; 
 int vaccess (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct ucred*,int /*<<< orphan*/ *) ; 
 scalar_t__ vfs_isrdonly (struct mount*) ; 
 struct mount* vnode_mount (struct vnode*) ; 
 int vnode_vtype (struct vnode*) ; 

int
fuse_internal_access(struct vnode *vp,
    accmode_t mode,
    struct thread *td,
    struct ucred *cred)
{
	int err = 0;
	uint32_t mask = F_OK;
	int dataflags;
	int vtype;
	struct mount *mp;
	struct fuse_dispatcher fdi;
	struct fuse_access_in *fai;
	struct fuse_data *data;

	mp = vnode_mount(vp);
	vtype = vnode_vtype(vp);

	data = fuse_get_mpdata(mp);
	dataflags = data->dataflags;

	if (mode == 0)
		return 0;

	if (mode & VMODIFY_PERMS && vfs_isrdonly(mp)) {
		switch (vp->v_type) {
		case VDIR:
			/* FALLTHROUGH */
		case VLNK:
			/* FALLTHROUGH */
		case VREG:
			return EROFS;
		default:
			break;
		}
	}

	/* Unless explicitly permitted, deny everyone except the fs owner. */
	if (!(dataflags & FSESS_DAEMON_CAN_SPY)) {
		if (fuse_match_cred(data->daemoncred, cred))
			return EPERM;
	}

	if (dataflags & FSESS_DEFAULT_PERMISSIONS) {
		struct vattr va;

		fuse_internal_getattr(vp, &va, cred, td);
		return vaccess(vp->v_type, va.va_mode, va.va_uid,
		    va.va_gid, mode, cred, NULL);
	}

	if (!fsess_isimpl(mp, FUSE_ACCESS))
		return 0;

	if ((mode & (VWRITE | VAPPEND | VADMIN)) != 0)
		mask |= W_OK;
	if ((mode & VREAD) != 0)
		mask |= R_OK;
	if ((mode & VEXEC) != 0)
		mask |= X_OK;

	fdisp_init(&fdi, sizeof(*fai));
	fdisp_make_vp(&fdi, FUSE_ACCESS, vp, td, cred);

	fai = fdi.indata;
	fai->mask = mask;

	err = fdisp_wait_answ(&fdi);
	fdisp_destroy(&fdi);

	if (err == ENOSYS) {
		fsess_set_notimpl(mp, FUSE_ACCESS);
		err = 0;
	}
	return err;
}