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
struct vnode {scalar_t__ v_type; } ;
struct thread {int /*<<< orphan*/  td_proc; } ;
struct file {scalar_t__ f_type; struct fadvise_info* f_advice; struct vnode* f_vnode; TYPE_1__* f_ops; } ;
struct fadvise_info {int fa_advice; scalar_t__ fa_start; scalar_t__ fa_end; } ;
typedef  scalar_t__ off_t ;
struct TYPE_2__ {int fo_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FD (int) ; 
 int /*<<< orphan*/  AUDIT_ARG_FILE (int /*<<< orphan*/ ,struct file*) ; 
 int /*<<< orphan*/  AUDIT_ARG_VALUE (int) ; 
 int DFLAG_SEEKABLE ; 
 scalar_t__ DTYPE_VNODE ; 
 int EINVAL ; 
 int ENODEV ; 
 int ESPIPE ; 
 int /*<<< orphan*/  M_FADVISE ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ OFF_MAX ; 
#define  POSIX_FADV_DONTNEED 133 
#define  POSIX_FADV_NOREUSE 132 
#define  POSIX_FADV_NORMAL 131 
#define  POSIX_FADV_RANDOM 130 
#define  POSIX_FADV_SEQUENTIAL 129 
#define  POSIX_FADV_WILLNEED 128 
 int VOP_ADVISE (struct vnode*,scalar_t__,scalar_t__,int) ; 
 scalar_t__ VREG ; 
 int /*<<< orphan*/  cap_no_rights ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget (struct thread*,int,int /*<<< orphan*/ *,struct file**) ; 
 int /*<<< orphan*/  free (struct fadvise_info*,int /*<<< orphan*/ ) ; 
 struct fadvise_info* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_pool_lock (int /*<<< orphan*/ ,struct file*) ; 
 int /*<<< orphan*/  mtx_pool_unlock (int /*<<< orphan*/ ,struct file*) ; 
 int /*<<< orphan*/  mtxpool_sleep ; 

int
kern_posix_fadvise(struct thread *td, int fd, off_t offset, off_t len,
    int advice)
{
	struct fadvise_info *fa, *new;
	struct file *fp;
	struct vnode *vp;
	off_t end;
	int error;

	if (offset < 0 || len < 0 || offset > OFF_MAX - len)
		return (EINVAL);
	AUDIT_ARG_VALUE(advice);
	switch (advice) {
	case POSIX_FADV_SEQUENTIAL:
	case POSIX_FADV_RANDOM:
	case POSIX_FADV_NOREUSE:
		new = malloc(sizeof(*fa), M_FADVISE, M_WAITOK);
		break;
	case POSIX_FADV_NORMAL:
	case POSIX_FADV_WILLNEED:
	case POSIX_FADV_DONTNEED:
		new = NULL;
		break;
	default:
		return (EINVAL);
	}
	/* XXX: CAP_POSIX_FADVISE? */
	AUDIT_ARG_FD(fd);
	error = fget(td, fd, &cap_no_rights, &fp);
	if (error != 0)
		goto out;
	AUDIT_ARG_FILE(td->td_proc, fp);
	if ((fp->f_ops->fo_flags & DFLAG_SEEKABLE) == 0) {
		error = ESPIPE;
		goto out;
	}
	if (fp->f_type != DTYPE_VNODE) {
		error = ENODEV;
		goto out;
	}
	vp = fp->f_vnode;
	if (vp->v_type != VREG) {
		error = ENODEV;
		goto out;
	}
	if (len == 0)
		end = OFF_MAX;
	else
		end = offset + len - 1;
	switch (advice) {
	case POSIX_FADV_SEQUENTIAL:
	case POSIX_FADV_RANDOM:
	case POSIX_FADV_NOREUSE:
		/*
		 * Try to merge any existing non-standard region with
		 * this new region if possible, otherwise create a new
		 * non-standard region for this request.
		 */
		mtx_pool_lock(mtxpool_sleep, fp);
		fa = fp->f_advice;
		if (fa != NULL && fa->fa_advice == advice &&
		    ((fa->fa_start <= end && fa->fa_end >= offset) ||
		    (end != OFF_MAX && fa->fa_start == end + 1) ||
		    (fa->fa_end != OFF_MAX && fa->fa_end + 1 == offset))) {
			if (offset < fa->fa_start)
				fa->fa_start = offset;
			if (end > fa->fa_end)
				fa->fa_end = end;
		} else {
			new->fa_advice = advice;
			new->fa_start = offset;
			new->fa_end = end;
			fp->f_advice = new;
			new = fa;
		}
		mtx_pool_unlock(mtxpool_sleep, fp);
		break;
	case POSIX_FADV_NORMAL:
		/*
		 * If a the "normal" region overlaps with an existing
		 * non-standard region, trim or remove the
		 * non-standard region.
		 */
		mtx_pool_lock(mtxpool_sleep, fp);
		fa = fp->f_advice;
		if (fa != NULL) {
			if (offset <= fa->fa_start && end >= fa->fa_end) {
				new = fa;
				fp->f_advice = NULL;
			} else if (offset <= fa->fa_start &&
			    end >= fa->fa_start)
				fa->fa_start = end + 1;
			else if (offset <= fa->fa_end && end >= fa->fa_end)
				fa->fa_end = offset - 1;
			else if (offset >= fa->fa_start && end <= fa->fa_end) {
				/*
				 * If the "normal" region is a middle
				 * portion of the existing
				 * non-standard region, just remove
				 * the whole thing rather than picking
				 * one side or the other to
				 * preserve.
				 */
				new = fa;
				fp->f_advice = NULL;
			}
		}
		mtx_pool_unlock(mtxpool_sleep, fp);
		break;
	case POSIX_FADV_WILLNEED:
	case POSIX_FADV_DONTNEED:
		error = VOP_ADVISE(vp, offset, end, advice);
		break;
	}
out:
	if (fp != NULL)
		fdrop(fp, td);
	free(new, M_FADVISE);
	return (error);
}