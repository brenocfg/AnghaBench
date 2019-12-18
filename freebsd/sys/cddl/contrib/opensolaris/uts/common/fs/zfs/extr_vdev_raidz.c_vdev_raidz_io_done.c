#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {scalar_t__ io_type; scalar_t__ io_error; int io_flags; int /*<<< orphan*/  io_spa; int /*<<< orphan*/  io_priority; int /*<<< orphan*/ * io_bp; TYPE_4__* io_vsd; TYPE_3__* io_vd; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_22__ {int /*<<< orphan*/  zbc_injected; scalar_t__ zbc_has_cksum; } ;
typedef  TYPE_2__ zio_bad_cksum_t ;
struct TYPE_23__ {struct TYPE_23__** vdev_child; } ;
typedef  TYPE_3__ vdev_t ;
struct TYPE_24__ {scalar_t__ rm_missingparity; scalar_t__ rm_firstdatacol; scalar_t__ rm_missingdata; scalar_t__ rm_cols; TYPE_5__* rm_col; int /*<<< orphan*/  rm_ecksuminjected; } ;
typedef  TYPE_4__ raidz_map_t ;
struct TYPE_25__ {scalar_t__ rc_error; size_t rc_devidx; int /*<<< orphan*/  rc_size; int /*<<< orphan*/  rc_abd; int /*<<< orphan*/  rc_offset; scalar_t__ rc_tried; int /*<<< orphan*/  rc_skipped; } ;
typedef  TYPE_5__ raidz_col_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ ECKSUM ; 
 scalar_t__ SET_ERROR (scalar_t__) ; 
 int VDEV_RAIDZ_MAXPARITY ; 
 int ZIO_FLAG_IO_REPAIR ; 
 int ZIO_FLAG_RESILVER ; 
 int ZIO_FLAG_SELF_HEAL ; 
 int ZIO_FLAG_SPECULATIVE ; 
 int /*<<< orphan*/  ZIO_PRIORITY_ASYNC_WRITE ; 
 scalar_t__ ZIO_TYPE_FREE ; 
 scalar_t__ ZIO_TYPE_READ ; 
 scalar_t__ ZIO_TYPE_WRITE ; 
 int /*<<< orphan*/  atomic_inc_64 (int /*<<< orphan*/ *) ; 
 scalar_t__ raidz_checksum_verify (TYPE_1__*) ; 
 int /*<<< orphan*/ * raidz_corrected ; 
 int raidz_parity_verify (TYPE_1__*,TYPE_4__*) ; 
 scalar_t__ spa_writeable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vdev_raidz_child_done ; 
 int vdev_raidz_combrec (TYPE_1__*,int,int) ; 
 int vdev_raidz_reconstruct (TYPE_4__*,int*,int) ; 
 void* vdev_raidz_worst_error (TYPE_4__*) ; 
 int /*<<< orphan*/  zfs_ereport_start_checksum (int /*<<< orphan*/ ,TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,TYPE_2__*) ; 
 int /*<<< orphan*/  zio_checksum_verified (TYPE_1__*) ; 
 int /*<<< orphan*/  zio_nowait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_vdev_child_io (TYPE_1__*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  zio_vdev_io_redone (TYPE_1__*) ; 

__attribute__((used)) static void
vdev_raidz_io_done(zio_t *zio)
{
	vdev_t *vd = zio->io_vd;
	vdev_t *cvd;
	raidz_map_t *rm = zio->io_vsd;
	raidz_col_t *rc;
	int unexpected_errors = 0;
	int parity_errors = 0;
	int parity_untried = 0;
	int data_errors = 0;
	int total_errors = 0;
	int n, c;
	int tgts[VDEV_RAIDZ_MAXPARITY];
	int code;

	ASSERT(zio->io_bp != NULL);  /* XXX need to add code to enforce this */

	ASSERT(rm->rm_missingparity <= rm->rm_firstdatacol);
	ASSERT(rm->rm_missingdata <= rm->rm_cols - rm->rm_firstdatacol);

	for (c = 0; c < rm->rm_cols; c++) {
		rc = &rm->rm_col[c];

		if (rc->rc_error) {
			ASSERT(rc->rc_error != ECKSUM);	/* child has no bp */

			if (c < rm->rm_firstdatacol)
				parity_errors++;
			else
				data_errors++;

			if (!rc->rc_skipped)
				unexpected_errors++;

			total_errors++;
		} else if (c < rm->rm_firstdatacol && !rc->rc_tried) {
			parity_untried++;
		}
	}

	if (zio->io_type == ZIO_TYPE_WRITE) {
		/*
		 * XXX -- for now, treat partial writes as a success.
		 * (If we couldn't write enough columns to reconstruct
		 * the data, the I/O failed.  Otherwise, good enough.)
		 *
		 * Now that we support write reallocation, it would be better
		 * to treat partial failure as real failure unless there are
		 * no non-degraded top-level vdevs left, and not update DTLs
		 * if we intend to reallocate.
		 */
		/* XXPOLICY */
		if (total_errors > rm->rm_firstdatacol)
			zio->io_error = vdev_raidz_worst_error(rm);

		return;
	} else if (zio->io_type == ZIO_TYPE_FREE) {
		return;
	}

	ASSERT(zio->io_type == ZIO_TYPE_READ);
	/*
	 * There are three potential phases for a read:
	 *	1. produce valid data from the columns read
	 *	2. read all disks and try again
	 *	3. perform combinatorial reconstruction
	 *
	 * Each phase is progressively both more expensive and less likely to
	 * occur. If we encounter more errors than we can repair or all phases
	 * fail, we have no choice but to return an error.
	 */

	/*
	 * If the number of errors we saw was correctable -- less than or equal
	 * to the number of parity disks read -- attempt to produce data that
	 * has a valid checksum. Naturally, this case applies in the absence of
	 * any errors.
	 */
	if (total_errors <= rm->rm_firstdatacol - parity_untried) {
		if (data_errors == 0) {
			if (raidz_checksum_verify(zio) == 0) {
				/*
				 * If we read parity information (unnecessarily
				 * as it happens since no reconstruction was
				 * needed) regenerate and verify the parity.
				 * We also regenerate parity when resilvering
				 * so we can write it out to the failed device
				 * later.
				 */
				if (parity_errors + parity_untried <
				    rm->rm_firstdatacol ||
				    (zio->io_flags & ZIO_FLAG_RESILVER)) {
					n = raidz_parity_verify(zio, rm);
					unexpected_errors += n;
					ASSERT(parity_errors + n <=
					    rm->rm_firstdatacol);
				}
				goto done;
			}
		} else {
			/*
			 * We either attempt to read all the parity columns or
			 * none of them. If we didn't try to read parity, we
			 * wouldn't be here in the correctable case. There must
			 * also have been fewer parity errors than parity
			 * columns or, again, we wouldn't be in this code path.
			 */
			ASSERT(parity_untried == 0);
			ASSERT(parity_errors < rm->rm_firstdatacol);

			/*
			 * Identify the data columns that reported an error.
			 */
			n = 0;
			for (c = rm->rm_firstdatacol; c < rm->rm_cols; c++) {
				rc = &rm->rm_col[c];
				if (rc->rc_error != 0) {
					ASSERT(n < VDEV_RAIDZ_MAXPARITY);
					tgts[n++] = c;
				}
			}

			ASSERT(rm->rm_firstdatacol >= n);

			code = vdev_raidz_reconstruct(rm, tgts, n);

			if (raidz_checksum_verify(zio) == 0) {
				atomic_inc_64(&raidz_corrected[code]);

				/*
				 * If we read more parity disks than were used
				 * for reconstruction, confirm that the other
				 * parity disks produced correct data. This
				 * routine is suboptimal in that it regenerates
				 * the parity that we already used in addition
				 * to the parity that we're attempting to
				 * verify, but this should be a relatively
				 * uncommon case, and can be optimized if it
				 * becomes a problem. Note that we regenerate
				 * parity when resilvering so we can write it
				 * out to failed devices later.
				 */
				if (parity_errors < rm->rm_firstdatacol - n ||
				    (zio->io_flags & ZIO_FLAG_RESILVER)) {
					n = raidz_parity_verify(zio, rm);
					unexpected_errors += n;
					ASSERT(parity_errors + n <=
					    rm->rm_firstdatacol);
				}

				goto done;
			}
		}
	}

	/*
	 * This isn't a typical situation -- either we got a read error or
	 * a child silently returned bad data. Read every block so we can
	 * try again with as much data and parity as we can track down. If
	 * we've already been through once before, all children will be marked
	 * as tried so we'll proceed to combinatorial reconstruction.
	 */
	unexpected_errors = 1;
	rm->rm_missingdata = 0;
	rm->rm_missingparity = 0;

	for (c = 0; c < rm->rm_cols; c++) {
		if (rm->rm_col[c].rc_tried)
			continue;

		zio_vdev_io_redone(zio);
		do {
			rc = &rm->rm_col[c];
			if (rc->rc_tried)
				continue;
			zio_nowait(zio_vdev_child_io(zio, NULL,
			    vd->vdev_child[rc->rc_devidx],
			    rc->rc_offset, rc->rc_abd, rc->rc_size,
			    zio->io_type, zio->io_priority, 0,
			    vdev_raidz_child_done, rc));
		} while (++c < rm->rm_cols);

		return;
	}

	/*
	 * At this point we've attempted to reconstruct the data given the
	 * errors we detected, and we've attempted to read all columns. There
	 * must, therefore, be one or more additional problems -- silent errors
	 * resulting in invalid data rather than explicit I/O errors resulting
	 * in absent data. We check if there is enough additional data to
	 * possibly reconstruct the data and then perform combinatorial
	 * reconstruction over all possible combinations. If that fails,
	 * we're cooked.
	 */
	if (total_errors > rm->rm_firstdatacol) {
		zio->io_error = vdev_raidz_worst_error(rm);

	} else if (total_errors < rm->rm_firstdatacol &&
	    (code = vdev_raidz_combrec(zio, total_errors, data_errors)) != 0) {
		/*
		 * If we didn't use all the available parity for the
		 * combinatorial reconstruction, verify that the remaining
		 * parity is correct.
		 */
		if (code != (1 << rm->rm_firstdatacol) - 1)
			(void) raidz_parity_verify(zio, rm);
	} else {
		/*
		 * We're here because either:
		 *
		 *	total_errors == rm_firstdatacol, or
		 *	vdev_raidz_combrec() failed
		 *
		 * In either case, there is enough bad data to prevent
		 * reconstruction.
		 *
		 * Start checksum ereports for all children which haven't
		 * failed, and the IO wasn't speculative.
		 */
		zio->io_error = SET_ERROR(ECKSUM);

		if (!(zio->io_flags & ZIO_FLAG_SPECULATIVE)) {
			for (c = 0; c < rm->rm_cols; c++) {
				rc = &rm->rm_col[c];
				if (rc->rc_error == 0) {
					zio_bad_cksum_t zbc;
					zbc.zbc_has_cksum = 0;
					zbc.zbc_injected =
					    rm->rm_ecksuminjected;

					zfs_ereport_start_checksum(
					    zio->io_spa,
					    vd->vdev_child[rc->rc_devidx],
					    zio, rc->rc_offset, rc->rc_size,
					    (void *)(uintptr_t)c, &zbc);
				}
			}
		}
	}

done:
	zio_checksum_verified(zio);

	if (zio->io_error == 0 && spa_writeable(zio->io_spa) &&
	    (unexpected_errors || (zio->io_flags & ZIO_FLAG_RESILVER))) {
		/*
		 * Use the good data we have in hand to repair damaged children.
		 */
		for (c = 0; c < rm->rm_cols; c++) {
			rc = &rm->rm_col[c];
			cvd = vd->vdev_child[rc->rc_devidx];

			if (rc->rc_error == 0)
				continue;

			zio_nowait(zio_vdev_child_io(zio, NULL, cvd,
			    rc->rc_offset, rc->rc_abd, rc->rc_size,
			    ZIO_TYPE_WRITE, ZIO_PRIORITY_ASYNC_WRITE,
			    ZIO_FLAG_IO_REPAIR | (unexpected_errors ?
			    ZIO_FLAG_SELF_HEAL : 0), NULL, NULL));
		}
	}
}