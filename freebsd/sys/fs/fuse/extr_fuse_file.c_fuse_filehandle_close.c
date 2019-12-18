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
struct thread {TYPE_1__* td_proc; } ;
struct fuse_release_in {int /*<<< orphan*/  lock_owner; int /*<<< orphan*/  flags; int /*<<< orphan*/  fh; } ;
struct fuse_filehandle {int /*<<< orphan*/  fufh_type; int /*<<< orphan*/  fh_id; } ;
struct fuse_dispatcher {struct fuse_release_in* indata; } ;
struct TYPE_2__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int FUSE_RELEASE ; 
 int FUSE_RELEASEDIR ; 
 int /*<<< orphan*/  LIST_REMOVE (struct fuse_filehandle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_FUSE_FILEHANDLE ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fdisp_destroy (struct fuse_dispatcher*) ; 
 int /*<<< orphan*/  fdisp_init (struct fuse_dispatcher*,int) ; 
 int /*<<< orphan*/  fdisp_make_vp (struct fuse_dispatcher*,int,struct vnode*,struct thread*,struct ucred*) ; 
 int fdisp_wait_answ (struct fuse_dispatcher*) ; 
 int /*<<< orphan*/  free (struct fuse_filehandle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fufh_type_2_fflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_fh_count ; 
 scalar_t__ fuse_isdeadfs (struct vnode*) ; 
 int /*<<< orphan*/  next ; 
 scalar_t__ vnode_isdir (struct vnode*) ; 

int
fuse_filehandle_close(struct vnode *vp, struct fuse_filehandle *fufh,
    struct thread *td, struct ucred *cred)
{
	struct fuse_dispatcher fdi;
	struct fuse_release_in *fri;

	int err = 0;
	int op = FUSE_RELEASE;

	if (fuse_isdeadfs(vp)) {
		goto out;
	}
	if (vnode_isdir(vp))
		op = FUSE_RELEASEDIR;
	fdisp_init(&fdi, sizeof(*fri));
	fdisp_make_vp(&fdi, op, vp, td, cred);
	fri = fdi.indata;
	fri->fh = fufh->fh_id;
	fri->flags = fufh_type_2_fflags(fufh->fufh_type);
	/* 
	 * If the file has a POSIX lock then we're supposed to set lock_owner.
	 * If not, then lock_owner is undefined.  So we may as well always set
	 * it.
	 */
	fri->lock_owner = td->td_proc->p_pid;

	err = fdisp_wait_answ(&fdi);
	fdisp_destroy(&fdi);

out:
	counter_u64_add(fuse_fh_count, -1);
	LIST_REMOVE(fufh, next);
	free(fufh, M_FUSE_FILEHANDLE);

	return err;
}