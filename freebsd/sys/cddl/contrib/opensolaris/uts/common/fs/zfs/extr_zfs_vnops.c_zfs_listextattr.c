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
typedef  int /*<<< orphan*/  zfsvfs_t ;
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int u_char ;
struct vop_listextattr_args {size_t* a_size; int /*<<< orphan*/  a_cred; int /*<<< orphan*/  a_vp; int /*<<< orphan*/  a_attrnamespace; struct thread* a_td; struct uio* a_uio; } ;
struct uio {int uio_iovcnt; int uio_resid; int /*<<< orphan*/  uio_rw; scalar_t__ uio_offset; struct thread* uio_td; int /*<<< orphan*/  uio_segflg; struct iovec* uio_iov; } ;
struct thread {int dummy; } ;
struct nameidata {int /*<<< orphan*/ * ni_vp; } ;
struct iovec {int iov_len; void* iov_base; } ;
struct dirent {scalar_t__ d_type; int* d_name; int d_namlen; scalar_t__ d_reclen; } ;
typedef  int /*<<< orphan*/  dirbuf ;
typedef  int /*<<< orphan*/  attrprefix ;
struct TYPE_2__ {int /*<<< orphan*/ * z_zfsvfs; } ;

/* Variables and functions */
 scalar_t__ DT_REG ; 
 scalar_t__ DT_UNKNOWN ; 
 int ENOATTR ; 
 int LOCKLEAF ; 
 int LOCKSHARED ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  LOOKUP_XATTR ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT_ATVP (struct nameidata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct thread*) ; 
 int NOFOLLOW ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int VOP_READDIR (int /*<<< orphan*/ *,struct uio*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VREAD ; 
 TYPE_1__* VTOZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_ENTER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_EXIT (int /*<<< orphan*/ *) ; 
 int extattr_check_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*,int /*<<< orphan*/ ) ; 
 int namei (struct nameidata*) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (int*,char*,size_t) ; 
 int uiomove (int*,int,int /*<<< orphan*/ ,struct uio*) ; 
 int /*<<< orphan*/  vput (int /*<<< orphan*/ *) ; 
 int zfs_create_attrname (int /*<<< orphan*/ ,char*,char*,int) ; 
 int zfs_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_listextattr(struct vop_listextattr_args *ap)
/*
vop_listextattr {
	IN struct vnode *a_vp;
	IN int a_attrnamespace;
	INOUT struct uio *a_uio;
	OUT size_t *a_size;
	IN struct ucred *a_cred;
	IN struct thread *a_td;
};
*/
{
	zfsvfs_t *zfsvfs = VTOZ(ap->a_vp)->z_zfsvfs;
	struct thread *td = ap->a_td;
	struct nameidata nd;
	char attrprefix[16];
	u_char dirbuf[sizeof(struct dirent)];
	struct dirent *dp;
	struct iovec aiov;
	struct uio auio, *uio = ap->a_uio;
	size_t *sizep = ap->a_size;
	size_t plen;
	vnode_t *xvp = NULL, *vp;
	int done, error, eof, pos;

	error = extattr_check_cred(ap->a_vp, ap->a_attrnamespace,
	    ap->a_cred, ap->a_td, VREAD);
	if (error != 0)
		return (error);

	error = zfs_create_attrname(ap->a_attrnamespace, "", attrprefix,
	    sizeof(attrprefix));
	if (error != 0)
		return (error);
	plen = strlen(attrprefix);

	ZFS_ENTER(zfsvfs);

	if (sizep != NULL)
		*sizep = 0;

	error = zfs_lookup(ap->a_vp, NULL, &xvp, NULL, 0, ap->a_cred, td,
	    LOOKUP_XATTR);
	if (error != 0) {
		ZFS_EXIT(zfsvfs);
		/*
		 * ENOATTR means that the EA directory does not yet exist,
		 * i.e. there are no extended attributes there.
		 */
		if (error == ENOATTR)
			error = 0;
		return (error);
	}

	NDINIT_ATVP(&nd, LOOKUP, NOFOLLOW | LOCKLEAF | LOCKSHARED,
	    UIO_SYSSPACE, ".", xvp, td);
	error = namei(&nd);
	vp = nd.ni_vp;
	NDFREE(&nd, NDF_ONLY_PNBUF);
	if (error != 0) {
		ZFS_EXIT(zfsvfs);
		return (error);
	}

	auio.uio_iov = &aiov;
	auio.uio_iovcnt = 1;
	auio.uio_segflg = UIO_SYSSPACE;
	auio.uio_td = td;
	auio.uio_rw = UIO_READ;
	auio.uio_offset = 0;

	do {
		u_char nlen;

		aiov.iov_base = (void *)dirbuf;
		aiov.iov_len = sizeof(dirbuf);
		auio.uio_resid = sizeof(dirbuf);
		error = VOP_READDIR(vp, &auio, ap->a_cred, &eof, NULL, NULL);
		done = sizeof(dirbuf) - auio.uio_resid;
		if (error != 0)
			break;
		for (pos = 0; pos < done;) {
			dp = (struct dirent *)(dirbuf + pos);
			pos += dp->d_reclen;
			/*
			 * XXX: Temporarily we also accept DT_UNKNOWN, as this
			 * is what we get when attribute was created on Solaris.
			 */
			if (dp->d_type != DT_REG && dp->d_type != DT_UNKNOWN)
				continue;
			if (plen == 0 && strncmp(dp->d_name, "freebsd:", 8) == 0)
				continue;
			else if (strncmp(dp->d_name, attrprefix, plen) != 0)
				continue;
			nlen = dp->d_namlen - plen;
			if (sizep != NULL)
				*sizep += 1 + nlen;
			else if (uio != NULL) {
				/*
				 * Format of extattr name entry is one byte for
				 * length and the rest for name.
				 */
				error = uiomove(&nlen, 1, uio->uio_rw, uio);
				if (error == 0) {
					error = uiomove(dp->d_name + plen, nlen,
					    uio->uio_rw, uio);
				}
				if (error != 0)
					break;
			}
		}
	} while (!eof && error == 0);

	vput(vp);
	ZFS_EXIT(zfsvfs);

	return (error);
}