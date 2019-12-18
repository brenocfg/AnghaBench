#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int ;
struct thread {int dummy; } ;
struct g_provider {TYPE_1__* geom; } ;
struct fdc_status {int /*<<< orphan*/  status; } ;
struct fdc_readid {int cyl; int head; } ;
struct fd_type {int /*<<< orphan*/  sectrac; } ;
struct fd_formb {int /*<<< orphan*/  format_version; } ;
struct fd_data {size_t type; int options; TYPE_2__* fdc; int /*<<< orphan*/  flags; struct fd_type* ft; struct fd_type fts; } ;
typedef  enum fd_drivetype { ____Placeholder_fd_drivetype } fd_drivetype ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  fdc_mtx; int /*<<< orphan*/  status; int /*<<< orphan*/  fdc_errs; } ;
struct TYPE_3__ {struct fd_data* softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_FMT ; 
 int /*<<< orphan*/  BIO_RDID ; 
 int EINVAL ; 
 int ENOIOCTL ; 
 int EPERM ; 
 int FDC_STAT_VALID ; 
#define  FD_CLRERR 138 
#define  FD_FORM 137 
 int /*<<< orphan*/  FD_FORMAT_VERSION ; 
#define  FD_GDTYPE 136 
#define  FD_GOPTS 135 
#define  FD_GSTAT 134 
#define  FD_GTYPE 133 
 int /*<<< orphan*/  FD_NEWDISK ; 
#define  FD_READID 132 
#define  FD_SOPTS 131 
#define  FD_STYPE 130 
#define  FIOASYNC 129 
#define  FIONBIO 128 
 int FWRITE ; 
 int /*<<< orphan*/  PRIV_DRIVER ; 
 int debugflags ; 
 struct fd_type** fd_native_types ; 
 int fdmisccmd (struct fd_data*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  fdprinttype (struct fd_type*) ; 
 int /*<<< orphan*/  fdsettype (struct fd_data*,struct fd_type*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fd_ioctl(struct g_provider *pp, u_long cmd, void *data, int fflag, struct thread *td)
{
	struct fd_data *fd;
	struct fdc_status *fsp;
	struct fdc_readid *rid;
	int error;

	fd = pp->geom->softc;

	switch (cmd) {
	case FD_GTYPE:                  /* get drive type */
		*(struct fd_type *)data = *fd->ft;
		return (0);

	case FD_STYPE:                  /* set drive type */
		/*
		 * Allow setting drive type temporarily iff
		 * currently unset.  Used for fdformat so any
		 * user can set it, and then start formatting.
		 */
		fd->fts = *(struct fd_type *)data;
		if (fd->fts.sectrac) {
			/* XXX: check for rubbish */
			fdsettype(fd, &fd->fts);
		} else {
			fdsettype(fd, fd_native_types[fd->type]);
		}
		if (debugflags & 0x40)
			fdprinttype(fd->ft);
		return (0);

	case FD_GOPTS:			/* get drive options */
		*(int *)data = fd->options;
		return (0);

	case FD_SOPTS:			/* set drive options */
		fd->options = *(int *)data;
		return (0);

	case FD_CLRERR:
		error = priv_check(td, PRIV_DRIVER);
		if (error)
			return (error);
		fd->fdc->fdc_errs = 0;
		return (0);

	case FD_GSTAT:
		fsp = (struct fdc_status *)data;
		if ((fd->fdc->flags & FDC_STAT_VALID) == 0)
			return (EINVAL);
		memcpy(fsp->status, fd->fdc->status, 7 * sizeof(u_int));
		return (0);

	case FD_GDTYPE:
		*(enum fd_drivetype *)data = fd->type;
		return (0);

	case FD_FORM:
		if (!(fflag & FWRITE))
			return (EPERM);
		if (((struct fd_formb *)data)->format_version !=
		    FD_FORMAT_VERSION)
			return (EINVAL); /* wrong version of formatting prog */
		error = fdmisccmd(fd, BIO_FMT, data);
		mtx_lock(&fd->fdc->fdc_mtx);
		fd->flags |= FD_NEWDISK;
		mtx_unlock(&fd->fdc->fdc_mtx);
		break;

	case FD_READID:
		rid = (struct fdc_readid *)data;
		if (rid->cyl > 85 || rid->head > 1)
			return (EINVAL);
		error = fdmisccmd(fd, BIO_RDID, data);
		break;

	case FIONBIO:
	case FIOASYNC:
		/* For backwards compat with old fd*(8) tools */
		error = 0;
		break;

	default:
		if (debugflags & 0x80)
			printf("Unknown ioctl %lx\n", cmd);
		error = ENOIOCTL;
		break;
	}
	return (error);
}