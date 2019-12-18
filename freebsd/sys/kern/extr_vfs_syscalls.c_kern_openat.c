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
struct vnode {scalar_t__ v_type; } ;
struct thread {int td_dupfd; int* td_retval; int /*<<< orphan*/  td_ucred; struct proc* td_proc; } ;
struct proc {struct filedesc* p_fd; } ;
struct filecaps {int dummy; } ;
struct nameidata {int ni_lcf; struct filecaps ni_filecaps; struct vnode* ni_vp; } ;
struct filedesc {int fd_cmask; } ;
struct file {int f_flag; int f_seqcount; int /*<<< orphan*/ * f_ops; struct vnode* f_vnode; } ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int ALLPERMS ; 
 int AUDITVNODE1 ; 
 int /*<<< orphan*/  AUDIT_ARG_FFLAGS (int) ; 
 int /*<<< orphan*/  AUDIT_ARG_MODE (int) ; 
 int /*<<< orphan*/  CAP_LOOKUP ; 
 int /*<<< orphan*/  DTYPE_VNODE ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENXIO ; 
 int FFLAGS (int) ; 
 int FHASLOCK ; 
 int FMASK ; 
 int FOLLOW ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT_ATRIGHTS (struct nameidata*,int /*<<< orphan*/ ,int,int,char const*,int,int /*<<< orphan*/ *,struct thread*) ; 
 int NI_LCF_STRICTRELATIVE ; 
 int O_ACCMODE ; 
 int O_EXEC ; 
 int O_TRUNC ; 
 int S_ISTXT ; 
 scalar_t__ VFIFO ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  badfileops ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int dupfdopen (struct thread*,struct filedesc*,scalar_t__,int,int,int*) ; 
 int falloc_noinstall (struct thread*,struct file**) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int /*<<< orphan*/  filecaps_free (struct filecaps*) ; 
 int /*<<< orphan*/  finit (struct file*,int,int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ *) ; 
 int finstall (struct thread*,struct file*,int*,int,struct filecaps*) ; 
 int /*<<< orphan*/  flags_to_rights (int,int /*<<< orphan*/ *) ; 
 int fo_truncate (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 
 int vn_open (struct nameidata*,int*,int,struct file*) ; 
 int /*<<< orphan*/  vnops ; 

int
kern_openat(struct thread *td, int fd, const char *path, enum uio_seg pathseg,
    int flags, int mode)
{
	struct proc *p = td->td_proc;
	struct filedesc *fdp = p->p_fd;
	struct file *fp;
	struct vnode *vp;
	struct nameidata nd;
	cap_rights_t rights;
	int cmode, error, indx;

	indx = -1;

	AUDIT_ARG_FFLAGS(flags);
	AUDIT_ARG_MODE(mode);
	cap_rights_init(&rights, CAP_LOOKUP);
	flags_to_rights(flags, &rights);
	/*
	 * Only one of the O_EXEC, O_RDONLY, O_WRONLY and O_RDWR flags
	 * may be specified.
	 */
	if (flags & O_EXEC) {
		if (flags & O_ACCMODE)
			return (EINVAL);
	} else if ((flags & O_ACCMODE) == O_ACCMODE) {
		return (EINVAL);
	} else {
		flags = FFLAGS(flags);
	}

	/*
	 * Allocate a file structure. The descriptor to reference it
	 * is allocated and set by finstall() below.
	 */
	error = falloc_noinstall(td, &fp);
	if (error != 0)
		return (error);
	/*
	 * An extra reference on `fp' has been held for us by
	 * falloc_noinstall().
	 */
	/* Set the flags early so the finit in devfs can pick them up. */
	fp->f_flag = flags & FMASK;
	cmode = ((mode & ~fdp->fd_cmask) & ALLPERMS) & ~S_ISTXT;
	NDINIT_ATRIGHTS(&nd, LOOKUP, FOLLOW | AUDITVNODE1, pathseg, path, fd,
	    &rights, td);
	td->td_dupfd = -1;		/* XXX check for fdopen */
	error = vn_open(&nd, &flags, cmode, fp);
	if (error != 0) {
		/*
		 * If the vn_open replaced the method vector, something
		 * wonderous happened deep below and we just pass it up
		 * pretending we know what we do.
		 */
		if (error == ENXIO && fp->f_ops != &badfileops)
			goto success;

		/*
		 * Handle special fdopen() case. bleh.
		 *
		 * Don't do this for relative (capability) lookups; we don't
		 * understand exactly what would happen, and we don't think
		 * that it ever should.
		 */
		if ((nd.ni_lcf & NI_LCF_STRICTRELATIVE) == 0 &&
		    (error == ENODEV || error == ENXIO) &&
		    td->td_dupfd >= 0) {
			error = dupfdopen(td, fdp, td->td_dupfd, flags, error,
			    &indx);
			if (error == 0)
				goto success;
		}

		goto bad;
	}
	td->td_dupfd = 0;
	NDFREE(&nd, NDF_ONLY_PNBUF);
	vp = nd.ni_vp;

	/*
	 * Store the vnode, for any f_type. Typically, the vnode use
	 * count is decremented by direct call to vn_closefile() for
	 * files that switched type in the cdevsw fdopen() method.
	 */
	fp->f_vnode = vp;
	/*
	 * If the file wasn't claimed by devfs bind it to the normal
	 * vnode operations here.
	 */
	if (fp->f_ops == &badfileops) {
		KASSERT(vp->v_type != VFIFO, ("Unexpected fifo."));
		fp->f_seqcount = 1;
		finit(fp, (flags & FMASK) | (fp->f_flag & FHASLOCK),
		    DTYPE_VNODE, vp, &vnops);
	}

	VOP_UNLOCK(vp, 0);
	if (flags & O_TRUNC) {
		error = fo_truncate(fp, 0, td->td_ucred, td);
		if (error != 0)
			goto bad;
	}
success:
	/*
	 * If we haven't already installed the FD (for dupfdopen), do so now.
	 */
	if (indx == -1) {
		struct filecaps *fcaps;

#ifdef CAPABILITIES
		if ((nd.ni_lcf & NI_LCF_STRICTRELATIVE) != 0)
			fcaps = &nd.ni_filecaps;
		else
#endif
			fcaps = NULL;
		error = finstall(td, fp, &indx, flags, fcaps);
		/* On success finstall() consumes fcaps. */
		if (error != 0) {
			filecaps_free(&nd.ni_filecaps);
			goto bad;
		}
	} else {
		filecaps_free(&nd.ni_filecaps);
	}

	/*
	 * Release our private reference, leaving the one associated with
	 * the descriptor table intact.
	 */
	fdrop(fp, td);
	td->td_retval[0] = indx;
	return (0);
bad:
	KASSERT(indx == -1, ("indx=%d, should be -1", indx));
	fdrop(fp, td);
	return (error);
}