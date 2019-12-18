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
struct ucred {int dummy; } ;
struct thread {struct ucred* td_ucred; } ;
struct TYPE_2__ {int /*<<< orphan*/  va_size; } ;
struct fuse_vnode_data {int flag; TYPE_1__ cached_attrs; } ;
struct fuse_setattr_in {int /*<<< orphan*/  valid; int /*<<< orphan*/  fh; int /*<<< orphan*/  size; } ;
struct fuse_filehandle {int /*<<< orphan*/  fh_id; } ;
struct fuse_dispatcher {struct fuse_setattr_in* indata; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_ELOCKED (struct vnode*,char*) ; 
 int EBADF ; 
 int EISDIR ; 
 int EROFS ; 
 int /*<<< orphan*/  FATTR_FH ; 
 int /*<<< orphan*/  FATTR_SIZE ; 
 int FN_SIZECHANGE ; 
 int /*<<< orphan*/  FUSE_SETATTR ; 
 int /*<<< orphan*/  FWRITE ; 
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ VDIR ; 
 struct fuse_vnode_data* VTOFUD (struct vnode*) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  fdisp_destroy (struct fuse_dispatcher*) ; 
 int /*<<< orphan*/  fdisp_init (struct fuse_dispatcher*,int) ; 
 int /*<<< orphan*/  fdisp_make_vp (struct fuse_dispatcher*,int /*<<< orphan*/ ,struct vnode*,struct thread*,struct ucred*) ; 
 int fdisp_wait_answ (struct fuse_dispatcher*) ; 
 int /*<<< orphan*/  fuse_filehandle_getrw (struct vnode*,int /*<<< orphan*/ ,struct fuse_filehandle**,struct ucred*,int /*<<< orphan*/ ) ; 
 scalar_t__ fuse_isdeadfs (struct vnode*) ; 
 scalar_t__ vfs_isrdonly (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_mount (struct vnode*) ; 
 scalar_t__ vnode_vtype (struct vnode*) ; 

int
fuse_vnode_savesize(struct vnode *vp, struct ucred *cred, pid_t pid)
{
	struct fuse_vnode_data *fvdat = VTOFUD(vp);
	struct thread *td = curthread;
	struct fuse_filehandle *fufh = NULL;
	struct fuse_dispatcher fdi;
	struct fuse_setattr_in *fsai;
	int err = 0;

	ASSERT_VOP_ELOCKED(vp, "fuse_io_extend");

	if (fuse_isdeadfs(vp)) {
		return EBADF;
	}
	if (vnode_vtype(vp) == VDIR) {
		return EISDIR;
	}
	if (vfs_isrdonly(vnode_mount(vp))) {
		return EROFS;
	}
	if (cred == NULL) {
		cred = td->td_ucred;
	}
	fdisp_init(&fdi, sizeof(*fsai));
	fdisp_make_vp(&fdi, FUSE_SETATTR, vp, td, cred);
	fsai = fdi.indata;
	fsai->valid = 0;

	/* Truncate to a new value. */
	MPASS((fvdat->flag & FN_SIZECHANGE) != 0);
	fsai->size = fvdat->cached_attrs.va_size;
	fsai->valid |= FATTR_SIZE;

	fuse_filehandle_getrw(vp, FWRITE, &fufh, cred, pid);
	if (fufh) {
		fsai->fh = fufh->fh_id;
		fsai->valid |= FATTR_FH;
	}
	err = fdisp_wait_answ(&fdi);
	fdisp_destroy(&fdi);
	if (err == 0)
		fvdat->flag &= ~FN_SIZECHANGE;

	return err;
}