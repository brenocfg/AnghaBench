#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct vnode {TYPE_2__* v_mount; } ;
struct vattr {scalar_t__ va_size; } ;
struct uio {size_t uio_resid; scalar_t__ uio_offset; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct mount {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ off_t ;
struct TYPE_8__ {int /*<<< orphan*/  td_ucred; } ;
struct TYPE_6__ {long f_iosize; } ;
struct TYPE_7__ {TYPE_1__ mnt_stat; } ;

/* Variables and functions */
 int EFBIG ; 
 int EINVAL ; 
 int /*<<< orphan*/  FIOSEEKDATA ; 
 int /*<<< orphan*/  FIOSEEKHOLE ; 
 int /*<<< orphan*/  IO_NODELOCKED ; 
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int /*<<< orphan*/  LK_SHARED ; 
 int MAX (long,long) ; 
 void* MIN (size_t,scalar_t__) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int VOP_GETATTR (struct vnode*,struct vattr*,struct ucred*) ; 
 int VOP_IOCTL (struct vnode*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,struct ucred*,TYPE_3__*) ; 
 scalar_t__ VOP_PATHCONF (struct vnode*,int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_WAIT ; 
 int /*<<< orphan*/  _PC_MIN_HOLE_SIZE ; 
 TYPE_3__* curthread ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int mac_vnode_check_write (int /*<<< orphan*/ ,struct ucred*,struct vnode*) ; 
 char* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mem_iszero (char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int vn_lock (struct vnode*,int /*<<< orphan*/ ) ; 
 int vn_rdwr (int /*<<< orphan*/ ,struct vnode*,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucred*,scalar_t__*,TYPE_3__*) ; 
 int vn_rlimit_fsize (struct vnode*,struct uio*,struct thread*) ; 
 int vn_start_write (struct vnode*,struct mount**,int /*<<< orphan*/ ) ; 
 int vn_truncate_locked (struct vnode*,scalar_t__,int,struct ucred*) ; 
 int vn_write_outvp (struct vnode*,char*,scalar_t__,scalar_t__,int,int,int,struct ucred*) ; 

int
vn_generic_copy_file_range(struct vnode *invp, off_t *inoffp,
    struct vnode *outvp, off_t *outoffp, size_t *lenp, unsigned int flags,
    struct ucred *incred, struct ucred *outcred, struct thread *fsize_td)
{
	struct vattr va;
	struct mount *mp;
	struct uio io;
	off_t startoff, endoff, xfer, xfer2;
	u_long blksize;
	int error;
	bool cantseek, readzeros, eof, lastblock;
	ssize_t aresid;
	size_t copylen, len, savlen;
	char *dat;
	long holein, holeout;

	holein = holeout = 0;
	savlen = len = *lenp;
	error = 0;
	dat = NULL;

	error = vn_lock(invp, LK_SHARED);
	if (error != 0)
		goto out;
	if (VOP_PATHCONF(invp, _PC_MIN_HOLE_SIZE, &holein) != 0)
		holein = 0;
	VOP_UNLOCK(invp, 0);

	mp = NULL;
	error = vn_start_write(outvp, &mp, V_WAIT);
	if (error == 0)
		error = vn_lock(outvp, LK_EXCLUSIVE);
	if (error == 0) {
		/*
		 * If fsize_td != NULL, do a vn_rlimit_fsize() call,
		 * now that outvp is locked.
		 */
		if (fsize_td != NULL) {
			io.uio_offset = *outoffp;
			io.uio_resid = len;
			error = vn_rlimit_fsize(outvp, &io, fsize_td);
			if (error != 0)
				error = EFBIG;
		}
		if (VOP_PATHCONF(outvp, _PC_MIN_HOLE_SIZE, &holeout) != 0)
			holeout = 0;
		/*
		 * Holes that are past EOF do not need to be written as a block
		 * of zero bytes.  So, truncate the output file as far as
		 * possible and then use va.va_size to decide if writing 0
		 * bytes is necessary in the loop below.
		 */
		if (error == 0)
			error = VOP_GETATTR(outvp, &va, outcred);
		if (error == 0 && va.va_size > *outoffp && va.va_size <=
		    *outoffp + len) {
#ifdef MAC
			error = mac_vnode_check_write(curthread->td_ucred,
			    outcred, outvp);
			if (error == 0)
#endif
				error = vn_truncate_locked(outvp, *outoffp,
				    false, outcred);
			if (error == 0)
				va.va_size = *outoffp;
		}
		VOP_UNLOCK(outvp, 0);
	}
	if (mp != NULL)
		vn_finished_write(mp);
	if (error != 0)
		goto out;

	/*
	 * Set the blksize to the larger of the hole sizes for invp and outvp.
	 * If hole sizes aren't available, set the blksize to the larger 
	 * f_iosize of invp and outvp.
	 * This code expects the hole sizes and f_iosizes to be powers of 2.
	 * This value is clipped at 4Kbytes and 1Mbyte.
	 */
	blksize = MAX(holein, holeout);
	if (blksize == 0)
		blksize = MAX(invp->v_mount->mnt_stat.f_iosize,
		    outvp->v_mount->mnt_stat.f_iosize);
	if (blksize < 4096)
		blksize = 4096;
	else if (blksize > 1024 * 1024)
		blksize = 1024 * 1024;
	dat = malloc(blksize, M_TEMP, M_WAITOK);

	/*
	 * If VOP_IOCTL(FIOSEEKHOLE) works for invp, use it and FIOSEEKDATA
	 * to find holes.  Otherwise, just scan the read block for all 0s
	 * in the inner loop where the data copying is done.
	 * Note that some file systems such as NFSv3, NFSv4.0 and NFSv4.1 may
	 * support holes on the server, but do not support FIOSEEKHOLE.
	 */
	eof = false;
	while (len > 0 && error == 0 && !eof) {
		endoff = 0;			/* To shut up compilers. */
		cantseek = true;
		startoff = *inoffp;
		copylen = len;

		/*
		 * Find the next data area.  If there is just a hole to EOF,
		 * FIOSEEKDATA should fail and then we drop down into the
		 * inner loop and create the hole on the outvp file.
		 * (I do not know if any file system will report a hole to
		 *  EOF via FIOSEEKHOLE, but I am pretty sure FIOSEEKDATA
		 *  will fail for those file systems.)
		 *
		 * For input files that don't support FIOSEEKDATA/FIOSEEKHOLE,
		 * the code just falls through to the inner copy loop.
		 */
		error = EINVAL;
		if (holein > 0)
			error = VOP_IOCTL(invp, FIOSEEKDATA, &startoff, 0,
			    incred, curthread);
		if (error == 0) {
			endoff = startoff;
			error = VOP_IOCTL(invp, FIOSEEKHOLE, &endoff, 0,
			    incred, curthread);
			/*
			 * Since invp is unlocked, it may be possible for
			 * another thread to do a truncate(), lseek(), write()
			 * creating a hole at startoff between the above
			 * VOP_IOCTL() calls, if the other thread does not do
			 * rangelocking.
			 * If that happens, startoff == endoff and finding
			 * the hole has failed, so set an error.
			 */
			if (error == 0 && startoff == endoff)
				error = EINVAL; /* Any error. Reset to 0. */
		}
		if (error == 0) {
			if (startoff > *inoffp) {
				/* Found hole before data block. */
				xfer = MIN(startoff - *inoffp, len);
				if (*outoffp < va.va_size) {
					/* Must write 0s to punch hole. */
					xfer2 = MIN(va.va_size - *outoffp,
					    xfer);
					memset(dat, 0, MIN(xfer2, blksize));
					error = vn_write_outvp(outvp, dat,
					    *outoffp, xfer2, blksize, false,
					    holeout > 0, outcred);
				}

				if (error == 0 && *outoffp + xfer >
				    va.va_size && xfer == len)
					/* Grow last block. */
					error = vn_write_outvp(outvp, dat,
					    *outoffp, xfer, blksize, true,
					    false, outcred);
				if (error == 0) {
					*inoffp += xfer;
					*outoffp += xfer;
					len -= xfer;
				}
			}
			copylen = MIN(len, endoff - startoff);
			cantseek = false;
		} else {
			cantseek = true;
			startoff = *inoffp;
			copylen = len;
			error = 0;
		}

		xfer = blksize;
		if (cantseek) {
			/*
			 * Set first xfer to end at a block boundary, so that
			 * holes are more likely detected in the loop below via
			 * the for all bytes 0 method.
			 */
			xfer -= (*inoffp % blksize);
		}
		/* Loop copying the data block. */
		while (copylen > 0 && error == 0 && !eof) {
			if (copylen < xfer)
				xfer = copylen;
			error = vn_lock(invp, LK_SHARED);
			if (error != 0)
				goto out;
			error = vn_rdwr(UIO_READ, invp, dat, xfer,
			    startoff, UIO_SYSSPACE, IO_NODELOCKED,
			    curthread->td_ucred, incred, &aresid,
			    curthread);
			VOP_UNLOCK(invp, 0);
			lastblock = false;
			if (error == 0 && aresid > 0) {
				/* Stop the copy at EOF on the input file. */
				xfer -= aresid;
				eof = true;
				lastblock = true;
			}
			if (error == 0) {
				/*
				 * Skip the write for holes past the initial EOF
				 * of the output file, unless this is the last
				 * write of the output file at EOF.
				 */
				readzeros = cantseek ? mem_iszero(dat, xfer) :
				    false;
				if (xfer == len)
					lastblock = true;
				if (!cantseek || *outoffp < va.va_size ||
				    lastblock || !readzeros)
					error = vn_write_outvp(outvp, dat,
					    *outoffp, xfer, blksize,
					    readzeros && lastblock &&
					    *outoffp >= va.va_size, false,
					    outcred);
				if (error == 0) {
					*inoffp += xfer;
					startoff += xfer;
					*outoffp += xfer;
					copylen -= xfer;
					len -= xfer;
				}
			}
			xfer = blksize;
		}
	}
out:
	*lenp = savlen - len;
	free(dat, M_TEMP);
	return (error);
}