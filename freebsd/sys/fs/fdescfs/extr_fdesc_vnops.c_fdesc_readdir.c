#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct vop_readdir_args {scalar_t__* a_ncookies; TYPE_5__* a_vp; struct uio* a_uio; } ;
struct uio {int uio_offset; int uio_resid; TYPE_2__* uio_td; } ;
struct filedesc {int fd_nfiles; TYPE_3__* fd_ofiles; } ;
struct fdescmount {int flags; } ;
struct dirent {int d_namlen; int d_reclen; int d_off; int /*<<< orphan*/  d_fileno; int /*<<< orphan*/  d_type; int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_10__ {int /*<<< orphan*/  v_mount; } ;
struct TYPE_9__ {scalar_t__ fd_type; } ;
struct TYPE_8__ {int /*<<< orphan*/ * fde_file; } ;
struct TYPE_7__ {TYPE_1__* td_proc; } ;
struct TYPE_6__ {struct filedesc* p_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT_CHR ; 
 int /*<<< orphan*/  DT_DIR ; 
 int /*<<< orphan*/  DT_LNK ; 
 int EINVAL ; 
 int /*<<< orphan*/  FD_DESC ; 
 int /*<<< orphan*/  FD_ROOT ; 
 int /*<<< orphan*/  FILEDESC_SLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  FILEDESC_SUNLOCK (struct filedesc*) ; 
 int FMNT_LINRDLNKF ; 
 scalar_t__ Froot ; 
 int UIO_MX ; 
 struct fdescmount* VFSTOFDESC (int /*<<< orphan*/ ) ; 
 TYPE_4__* VTOFDESC (TYPE_5__*) ; 
 int /*<<< orphan*/  bcopy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dirent_terminate (struct dirent*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int uiomove (struct dirent*,int,struct uio*) ; 

__attribute__((used)) static int
fdesc_readdir(struct vop_readdir_args *ap)
{
	struct fdescmount *fmp;
	struct uio *uio = ap->a_uio;
	struct filedesc *fdp;
	struct dirent d;
	struct dirent *dp = &d;
	int error, i, off, fcnt;

	if (VTOFDESC(ap->a_vp)->fd_type != Froot)
		panic("fdesc_readdir: not dir");

	fmp = VFSTOFDESC(ap->a_vp->v_mount);
	if (ap->a_ncookies != NULL)
		*ap->a_ncookies = 0;

	off = (int)uio->uio_offset;
	if (off != uio->uio_offset || off < 0 || (u_int)off % UIO_MX != 0 ||
	    uio->uio_resid < UIO_MX)
		return (EINVAL);
	i = (u_int)off / UIO_MX;
	fdp = uio->uio_td->td_proc->p_fd;
	error = 0;

	fcnt = i - 2;		/* The first two nodes are `.' and `..' */

	FILEDESC_SLOCK(fdp);
	while (i < fdp->fd_nfiles + 2 && uio->uio_resid >= UIO_MX) {
		bzero((caddr_t)dp, UIO_MX);
		switch (i) {
		case 0:	/* `.' */
		case 1: /* `..' */
			dp->d_fileno = i + FD_ROOT;
			dp->d_namlen = i + 1;
			dp->d_reclen = UIO_MX;
			bcopy("..", dp->d_name, dp->d_namlen);
			dp->d_type = DT_DIR;
			dirent_terminate(dp);
			break;
		default:
			if (fdp->fd_ofiles[fcnt].fde_file == NULL)
				break;
			dp->d_namlen = sprintf(dp->d_name, "%d", fcnt);
			dp->d_reclen = UIO_MX;
			dp->d_type = (fmp->flags & FMNT_LINRDLNKF) == 0 ?
			    DT_CHR : DT_LNK;
			dp->d_fileno = i + FD_DESC;
			dirent_terminate(dp);
			break;
		}
		/* NOTE: d_off is the offset of the *next* entry. */
		dp->d_off = UIO_MX * (i + 1);
		if (dp->d_namlen != 0) {
			/*
			 * And ship to userland
			 */
			FILEDESC_SUNLOCK(fdp);
			error = uiomove(dp, UIO_MX, uio);
			if (error)
				goto done;
			FILEDESC_SLOCK(fdp);
		}
		i++;
		fcnt++;
	}
	FILEDESC_SUNLOCK(fdp);

done:
	uio->uio_offset = i * UIO_MX;
	return (error);
}