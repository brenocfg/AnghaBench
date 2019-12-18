#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int z_pflags; scalar_t__ z_size; int z_blksz; int /*<<< orphan*/  z_sa_hdl; int /*<<< orphan*/  z_rangelock; int /*<<< orphan*/  z_id; int /*<<< orphan*/  z_mode; TYPE_3__* z_zfsvfs; } ;
typedef  TYPE_2__ znode_t ;
struct TYPE_20__ {scalar_t__ z_log; TYPE_1__* z_os; } ;
typedef  TYPE_3__ zfsvfs_t ;
struct TYPE_21__ {scalar_t__ xu_type; } ;
typedef  TYPE_4__ xuio_t ;
typedef  int /*<<< orphan*/  vnode_t ;
struct TYPE_22__ {scalar_t__ uio_loffset; int uio_resid; scalar_t__ uio_extflg; scalar_t__ uio_segflg; int /*<<< orphan*/  uio_fmode; } ;
typedef  TYPE_5__ uio_t ;
typedef  int uint64_t ;
typedef  int ssize_t ;
typedef  scalar_t__ offset_t ;
typedef  int /*<<< orphan*/  locked_range_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  int /*<<< orphan*/  caller_context_t ;
struct TYPE_18__ {scalar_t__ os_sync; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  EACCES ; 
 int ECKSUM ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  FREAD ; 
 int FRSYNC ; 
 scalar_t__ ISP2 (int) ; 
 scalar_t__ MANDMODE (int /*<<< orphan*/ ) ; 
 int MIN (int,scalar_t__) ; 
 int P2ALIGN (int,int) ; 
 scalar_t__ P2PHASE (int,scalar_t__) ; 
 int P2ROUNDUP (int,int) ; 
 int /*<<< orphan*/  RL_READER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ UIOTYPE_ZEROCOPY ; 
 scalar_t__ UIO_NOCOPY ; 
 scalar_t__ UIO_XUIO ; 
 TYPE_2__* VTOZ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZFS_ACCESSTIME_STAMP (TYPE_3__*,TYPE_2__*) ; 
 int ZFS_AV_QUARANTINED ; 
 int /*<<< orphan*/  ZFS_ENTER (TYPE_3__*) ; 
 int /*<<< orphan*/  ZFS_EXIT (TYPE_3__*) ; 
 scalar_t__ ZFS_SYNC_ALWAYS ; 
 int /*<<< orphan*/  ZFS_VERIFY_ZP (TYPE_2__*) ; 
 int chklock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dmu_read_uio_dbuf (int /*<<< orphan*/ ,TYPE_5__*,int) ; 
 int /*<<< orphan*/  dmu_request_arcbuf (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmu_xuio_add (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dmu_xuio_init (TYPE_4__*,int) ; 
 int mappedread (int /*<<< orphan*/ *,int,TYPE_5__*) ; 
 int mappedread_sf (int /*<<< orphan*/ *,int,TYPE_5__*) ; 
 int /*<<< orphan*/ * rangelock_enter (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rangelock_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sa_get_db (int /*<<< orphan*/ ) ; 
 scalar_t__ vn_has_cached_data (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_read_chunk_size ; 
 int /*<<< orphan*/  zil_commit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_read(vnode_t *vp, uio_t *uio, int ioflag, cred_t *cr, caller_context_t *ct)
{
	znode_t		*zp = VTOZ(vp);
	zfsvfs_t	*zfsvfs = zp->z_zfsvfs;
	ssize_t		n, nbytes;
	int		error = 0;
	xuio_t		*xuio = NULL;

	ZFS_ENTER(zfsvfs);
	ZFS_VERIFY_ZP(zp);

	if (zp->z_pflags & ZFS_AV_QUARANTINED) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(EACCES));
	}

	/*
	 * Validate file offset
	 */
	if (uio->uio_loffset < (offset_t)0) {
		ZFS_EXIT(zfsvfs);
		return (SET_ERROR(EINVAL));
	}

	/*
	 * Fasttrack empty reads
	 */
	if (uio->uio_resid == 0) {
		ZFS_EXIT(zfsvfs);
		return (0);
	}

	/*
	 * Check for mandatory locks
	 */
	if (MANDMODE(zp->z_mode)) {
		if (error = chklock(vp, FREAD,
		    uio->uio_loffset, uio->uio_resid, uio->uio_fmode, ct)) {
			ZFS_EXIT(zfsvfs);
			return (error);
		}
	}

	/*
	 * If we're in FRSYNC mode, sync out this znode before reading it.
	 */
	if (zfsvfs->z_log &&
	    (ioflag & FRSYNC || zfsvfs->z_os->os_sync == ZFS_SYNC_ALWAYS))
		zil_commit(zfsvfs->z_log, zp->z_id);

	/*
	 * Lock the range against changes.
	 */
	locked_range_t *lr = rangelock_enter(&zp->z_rangelock,
	    uio->uio_loffset, uio->uio_resid, RL_READER);

	/*
	 * If we are reading past end-of-file we can skip
	 * to the end; but we might still need to set atime.
	 */
	if (uio->uio_loffset >= zp->z_size) {
		error = 0;
		goto out;
	}

	ASSERT(uio->uio_loffset < zp->z_size);
	n = MIN(uio->uio_resid, zp->z_size - uio->uio_loffset);

#ifdef illumos
	if ((uio->uio_extflg == UIO_XUIO) &&
	    (((xuio_t *)uio)->xu_type == UIOTYPE_ZEROCOPY)) {
		int nblk;
		int blksz = zp->z_blksz;
		uint64_t offset = uio->uio_loffset;

		xuio = (xuio_t *)uio;
		if ((ISP2(blksz))) {
			nblk = (P2ROUNDUP(offset + n, blksz) - P2ALIGN(offset,
			    blksz)) / blksz;
		} else {
			ASSERT(offset + n <= blksz);
			nblk = 1;
		}
		(void) dmu_xuio_init(xuio, nblk);

		if (vn_has_cached_data(vp)) {
			/*
			 * For simplicity, we always allocate a full buffer
			 * even if we only expect to read a portion of a block.
			 */
			while (--nblk >= 0) {
				(void) dmu_xuio_add(xuio,
				    dmu_request_arcbuf(sa_get_db(zp->z_sa_hdl),
				    blksz), 0, blksz);
			}
		}
	}
#endif	/* illumos */

	while (n > 0) {
		nbytes = MIN(n, zfs_read_chunk_size -
		    P2PHASE(uio->uio_loffset, zfs_read_chunk_size));

#ifdef __FreeBSD__
		if (uio->uio_segflg == UIO_NOCOPY)
			error = mappedread_sf(vp, nbytes, uio);
		else
#endif /* __FreeBSD__ */
		if (vn_has_cached_data(vp)) {
			error = mappedread(vp, nbytes, uio);
		} else {
			error = dmu_read_uio_dbuf(sa_get_db(zp->z_sa_hdl),
			    uio, nbytes);
		}
		if (error) {
			/* convert checksum errors into IO errors */
			if (error == ECKSUM)
				error = SET_ERROR(EIO);
			break;
		}

		n -= nbytes;
	}
out:
	rangelock_exit(lr);

	ZFS_ACCESSTIME_STAMP(zfsvfs, zp);
	ZFS_EXIT(zfsvfs);
	return (error);
}