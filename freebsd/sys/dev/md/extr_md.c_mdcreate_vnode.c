#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct vattr {scalar_t__ va_fileid; scalar_t__ va_fsid; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct nameidata {TYPE_1__* ni_vp; } ;
struct md_s {scalar_t__ fwsectors; scalar_t__ fwheads; int flags; TYPE_1__* vnode; int /*<<< orphan*/  ident; int /*<<< orphan*/  file; } ;
struct md_req {char* md_file; scalar_t__ md_file_seg; int md_options; scalar_t__ md_fwsectors; scalar_t__ md_fwheads; } ;
struct TYPE_6__ {scalar_t__ v_type; int v_iflag; int /*<<< orphan*/  v_vflag; } ;

/* Variables and functions */
 int EBADF ; 
 int EDOOFUS ; 
 int EINVAL ; 
 int /*<<< orphan*/  FOLLOW ; 
 int FREAD ; 
 int FWRITE ; 
 int LK_EXCLUSIVE ; 
 int LK_RETRY ; 
 int LK_UPGRADE ; 
 int /*<<< orphan*/  LOOKUP ; 
 int MD_ASYNC ; 
 int MD_CACHE ; 
 int MD_FORCE ; 
 int MD_READONLY ; 
 int MD_VERIFY ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct thread*) ; 
 int O_VERIFY ; 
 scalar_t__ UIO_SYSSPACE ; 
 scalar_t__ UIO_USERSPACE ; 
 int VI_DOOMED ; 
 int VOP_GETATTR (TYPE_1__*,struct vattr*,int /*<<< orphan*/ ) ; 
 int VOP_ISLOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ VREG ; 
 int /*<<< orphan*/  VV_MD ; 
 int copyinstr (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int mdsetcred (struct md_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vn_close (TYPE_1__*,int,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  vn_lock (TYPE_1__*,int) ; 
 int vn_open (struct nameidata*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mdcreate_vnode(struct md_s *sc, struct md_req *mdr, struct thread *td)
{
	struct vattr vattr;
	struct nameidata nd;
	char *fname;
	int error, flags;

	fname = mdr->md_file;
	if (mdr->md_file_seg == UIO_USERSPACE) {
		error = copyinstr(fname, sc->file, sizeof(sc->file), NULL);
		if (error != 0)
			return (error);
	} else if (mdr->md_file_seg == UIO_SYSSPACE)
		strlcpy(sc->file, fname, sizeof(sc->file));
	else
		return (EDOOFUS);

	/*
	 * If the user specified that this is a read only device, don't
	 * set the FWRITE mask before trying to open the backing store.
	 */
	flags = FREAD | ((mdr->md_options & MD_READONLY) ? 0 : FWRITE) \
	    | ((mdr->md_options & MD_VERIFY) ? O_VERIFY : 0);
	NDINIT(&nd, LOOKUP, FOLLOW, UIO_SYSSPACE, sc->file, td);
	error = vn_open(&nd, &flags, 0, NULL);
	if (error != 0)
		return (error);
	NDFREE(&nd, NDF_ONLY_PNBUF);
	if (nd.ni_vp->v_type != VREG) {
		error = EINVAL;
		goto bad;
	}
	error = VOP_GETATTR(nd.ni_vp, &vattr, td->td_ucred);
	if (error != 0)
		goto bad;
	if (VOP_ISLOCKED(nd.ni_vp) != LK_EXCLUSIVE) {
		vn_lock(nd.ni_vp, LK_UPGRADE | LK_RETRY);
		if (nd.ni_vp->v_iflag & VI_DOOMED) {
			/* Forced unmount. */
			error = EBADF;
			goto bad;
		}
	}
	nd.ni_vp->v_vflag |= VV_MD;
	VOP_UNLOCK(nd.ni_vp, 0);

	if (mdr->md_fwsectors != 0)
		sc->fwsectors = mdr->md_fwsectors;
	if (mdr->md_fwheads != 0)
		sc->fwheads = mdr->md_fwheads;
	snprintf(sc->ident, sizeof(sc->ident), "MD-DEV%ju-INO%ju",
	    (uintmax_t)vattr.va_fsid, (uintmax_t)vattr.va_fileid);
	sc->flags = mdr->md_options & (MD_ASYNC | MD_CACHE | MD_FORCE |
	    MD_VERIFY);
	if (!(flags & FWRITE))
		sc->flags |= MD_READONLY;
	sc->vnode = nd.ni_vp;

	error = mdsetcred(sc, td->td_ucred);
	if (error != 0) {
		sc->vnode = NULL;
		vn_lock(nd.ni_vp, LK_EXCLUSIVE | LK_RETRY);
		nd.ni_vp->v_vflag &= ~VV_MD;
		goto bad;
	}
	return (0);
bad:
	VOP_UNLOCK(nd.ni_vp, 0);
	(void)vn_close(nd.ni_vp, flags, td->td_ucred, td);
	return (error);
}