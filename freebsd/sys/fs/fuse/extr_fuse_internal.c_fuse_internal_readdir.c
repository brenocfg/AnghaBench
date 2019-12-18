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
typedef  int /*<<< orphan*/  u_long ;
struct vnode {int /*<<< orphan*/  v_mount; } ;
struct uio {scalar_t__ uio_offset; int /*<<< orphan*/  uio_resid; } ;
struct fuse_read_in {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; int /*<<< orphan*/  fh; } ;
struct fuse_iov {int dummy; } ;
struct fuse_filehandle {int /*<<< orphan*/  fh_id; } ;
struct fuse_dispatcher {int iosize; int /*<<< orphan*/  answ; struct fuse_read_in* indata; } ;
typedef  scalar_t__ off_t ;
struct TYPE_2__ {int /*<<< orphan*/  max_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_READDIR ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdisp_destroy (struct fuse_dispatcher*) ; 
 int /*<<< orphan*/  fdisp_init (struct fuse_dispatcher*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdisp_make_vp (struct fuse_dispatcher*,int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fdisp_refresh_vp (struct fuse_dispatcher*,int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fdisp_wait_answ (struct fuse_dispatcher*) ; 
 TYPE_1__* fuse_get_mpdata (int /*<<< orphan*/ ) ; 
 int fuse_internal_readdir_processdata (struct uio*,scalar_t__,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct fuse_iov*,int*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uio_offset (struct uio*) ; 
 scalar_t__ uio_resid (struct uio*) ; 

int
fuse_internal_readdir(struct vnode *vp,
    struct uio *uio,
    off_t startoff,
    struct fuse_filehandle *fufh,
    struct fuse_iov *cookediov,
    int *ncookies,
    u_long *cookies)
{
	int err = 0;
	struct fuse_dispatcher fdi;
	struct fuse_read_in *fri = NULL;
	int fnd_start;

	if (uio_resid(uio) == 0)
		return 0;
	fdisp_init(&fdi, 0);

	/*
	 * Note that we DO NOT have a UIO_SYSSPACE here (so no need for p2p
	 * I/O).
	 */

	/*
	 * fnd_start is set non-zero once the offset in the directory gets
	 * to the startoff.  This is done because directories must be read
	 * from the beginning (offset == 0) when fuse_vnop_readdir() needs
	 * to do an open of the directory.
	 * If it is not set non-zero here, it will be set non-zero in
	 * fuse_internal_readdir_processdata() when uio_offset == startoff.
	 */
	fnd_start = 0;
	if (uio->uio_offset == startoff)
		fnd_start = 1;
	while (uio_resid(uio) > 0) {
		fdi.iosize = sizeof(*fri);
		if (fri == NULL)
			fdisp_make_vp(&fdi, FUSE_READDIR, vp, NULL, NULL);
		else
			fdisp_refresh_vp(&fdi, FUSE_READDIR, vp, NULL, NULL);

		fri = fdi.indata;
		fri->fh = fufh->fh_id;
		fri->offset = uio_offset(uio);
		fri->size = MIN(uio->uio_resid,
		    fuse_get_mpdata(vp->v_mount)->max_read);

		if ((err = fdisp_wait_answ(&fdi)))
			break;
		if ((err = fuse_internal_readdir_processdata(uio, startoff,
		    &fnd_start, fri->size, fdi.answ, fdi.iosize, cookediov,
		    ncookies, &cookies)))
			break;
	}

	fdisp_destroy(&fdi);
	return ((err == -1) ? 0 : err);
}