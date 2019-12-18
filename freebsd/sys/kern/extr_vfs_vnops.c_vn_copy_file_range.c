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
typedef  scalar_t__ uint64_t ;
struct vnode {scalar_t__ v_type; scalar_t__ v_mount; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int EINVAL ; 
 int EISDIR ; 
 scalar_t__ INT64_MAX ; 
 scalar_t__ VDIR ; 
 int VOP_COPY_FILE_RANGE (struct vnode*,scalar_t__*,struct vnode*,scalar_t__*,size_t*,unsigned int,struct ucred*,struct ucred*,struct thread*) ; 
 scalar_t__ VREG ; 
 int vn_generic_copy_file_range (struct vnode*,scalar_t__*,struct vnode*,scalar_t__*,size_t*,unsigned int,struct ucred*,struct ucred*,struct thread*) ; 

int
vn_copy_file_range(struct vnode *invp, off_t *inoffp, struct vnode *outvp,
    off_t *outoffp, size_t *lenp, unsigned int flags, struct ucred *incred,
    struct ucred *outcred, struct thread *fsize_td)
{
	int error;
	size_t len;
	uint64_t uvalin, uvalout;

	len = *lenp;
	*lenp = 0;		/* For error returns. */
	error = 0;

	/* Do some sanity checks on the arguments. */
	uvalin = *inoffp;
	uvalin += len;
	uvalout = *outoffp;
	uvalout += len;
	if (invp->v_type == VDIR || outvp->v_type == VDIR)
		error = EISDIR;
	else if (*inoffp < 0 || uvalin > INT64_MAX || uvalin <
	    (uint64_t)*inoffp || *outoffp < 0 || uvalout > INT64_MAX ||
	    uvalout < (uint64_t)*outoffp || invp->v_type != VREG ||
	    outvp->v_type != VREG)
		error = EINVAL;
	if (error != 0)
		goto out;

	/*
	 * If the two vnode are for the same file system, call
	 * VOP_COPY_FILE_RANGE(), otherwise call vn_generic_copy_file_range()
	 * which can handle copies across multiple file systems.
	 */
	*lenp = len;
	if (invp->v_mount == outvp->v_mount)
		error = VOP_COPY_FILE_RANGE(invp, inoffp, outvp, outoffp,
		    lenp, flags, incred, outcred, fsize_td);
	else
		error = vn_generic_copy_file_range(invp, inoffp, outvp,
		    outoffp, lenp, flags, incred, outcred, fsize_td);
out:
	return (error);
}