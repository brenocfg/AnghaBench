#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ v_state; int (* v_read ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  spa; int /*<<< orphan*/  v_nparity; int /*<<< orphan*/  v_nchildren; int /*<<< orphan*/  v_ashift; struct TYPE_16__* v_top; } ;
typedef  TYPE_1__ vdev_t ;
struct TYPE_17__ {int rm_cols; int rm_firstdatacol; scalar_t__ rm_missingdata; int rm_missingparity; TYPE_3__* rm_col; } ;
typedef  TYPE_2__ raidz_map_t ;
struct TYPE_18__ {int rc_error; int rc_tried; int rc_skipped; int /*<<< orphan*/  rc_size; int /*<<< orphan*/  rc_offset; int /*<<< orphan*/  rc_data; int /*<<< orphan*/  rc_devidx; } ;
typedef  TYPE_3__ raidz_col_t ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
struct TYPE_19__ {int /*<<< orphan*/  io_txg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DTL_MISSING ; 
 int ECKSUM ; 
 int EIO ; 
 int ENXIO ; 
 int ESTALE ; 
 int VDEV_RAIDZ_MAXPARITY ; 
 scalar_t__ VDEV_STATE_HEALTHY ; 
 scalar_t__ raidz_checksum_verify (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,void*,size_t) ; 
 int raidz_parity_verify (TYPE_2__*) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* vdev_child (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ vdev_dtl_contains (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int vdev_raidz_combrec (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ ,size_t,int,int) ; 
 TYPE_2__* vdev_raidz_map_alloc (void*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_raidz_map_free (TYPE_2__*) ; 
 int vdev_raidz_reconstruct (TYPE_2__*,int*,int) ; 
 TYPE_4__* zio ; 

__attribute__((used)) static int
vdev_raidz_read(vdev_t *vd, const blkptr_t *bp, void *data,
    off_t offset, size_t bytes)
{
	vdev_t *tvd = vd->v_top;
	vdev_t *cvd;
	raidz_map_t *rm;
	raidz_col_t *rc;
	int c, error;
	int unexpected_errors;
	int parity_errors;
	int parity_untried;
	int data_errors;
	int total_errors;
	int n;
	int tgts[VDEV_RAIDZ_MAXPARITY];
	int code;

	rc = NULL;	/* gcc */
	error = 0;

	rm = vdev_raidz_map_alloc(data, offset, bytes, tvd->v_ashift,
	    vd->v_nchildren, vd->v_nparity);

	/*
	 * Iterate over the columns in reverse order so that we hit the parity
	 * last -- any errors along the way will force us to read the parity.
	 */
	for (c = rm->rm_cols - 1; c >= 0; c--) {
		rc = &rm->rm_col[c];
		cvd = vdev_child(vd, rc->rc_devidx);
		if (cvd == NULL || cvd->v_state != VDEV_STATE_HEALTHY) {
			if (c >= rm->rm_firstdatacol)
				rm->rm_missingdata++;
			else
				rm->rm_missingparity++;
			rc->rc_error = ENXIO;
			rc->rc_tried = 1;	/* don't even try */
			rc->rc_skipped = 1;
			continue;
		}
#if 0		/* XXX: Too hard for the boot code. */
		if (vdev_dtl_contains(cvd, DTL_MISSING, zio->io_txg, 1)) {
			if (c >= rm->rm_firstdatacol)
				rm->rm_missingdata++;
			else
				rm->rm_missingparity++;
			rc->rc_error = ESTALE;
			rc->rc_skipped = 1;
			continue;
		}
#endif
		if (c >= rm->rm_firstdatacol || rm->rm_missingdata > 0) {
			rc->rc_error = cvd->v_read(cvd, NULL, rc->rc_data,
			    rc->rc_offset, rc->rc_size);
			rc->rc_tried = 1;
			rc->rc_skipped = 0;
		}
	}

reconstruct:
	unexpected_errors = 0;
	parity_errors = 0;
	parity_untried = 0;
	data_errors = 0;
	total_errors = 0;

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
			if (raidz_checksum_verify(vd->spa, bp, data, bytes) == 0) {
				/*
				 * If we read parity information (unnecessarily
				 * as it happens since no reconstruction was
				 * needed) regenerate and verify the parity.
				 * We also regenerate parity when resilvering
				 * so we can write it out to the failed device
				 * later.
				 */
				if (parity_errors + parity_untried <
				    rm->rm_firstdatacol) {
					n = raidz_parity_verify(rm);
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

			if (raidz_checksum_verify(vd->spa, bp, data, bytes) == 0) {
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
				if (parity_errors < rm->rm_firstdatacol - n) {
					n = raidz_parity_verify(rm);
					unexpected_errors += n;
					ASSERT(parity_errors + n <=
					    rm->rm_firstdatacol);
				}

				goto done;
			}
		}
	}

	/*
	 * This isn't a typical situation -- either we got a read
	 * error or a child silently returned bad data. Read every
	 * block so we can try again with as much data and parity as
	 * we can track down. If we've already been through once
	 * before, all children will be marked as tried so we'll
	 * proceed to combinatorial reconstruction.
	 */
	unexpected_errors = 1;
	rm->rm_missingdata = 0;
	rm->rm_missingparity = 0;

	n = 0;
	for (c = 0; c < rm->rm_cols; c++) {
		rc = &rm->rm_col[c];

		if (rc->rc_tried)
			continue;

		cvd = vdev_child(vd, rc->rc_devidx);
		ASSERT(cvd != NULL);
		rc->rc_error = cvd->v_read(cvd, NULL,
		    rc->rc_data, rc->rc_offset, rc->rc_size);
		if (rc->rc_error == 0)
			n++;
		rc->rc_tried = 1;
		rc->rc_skipped = 0;
	}
	/*
	 * If we managed to read anything more, retry the
	 * reconstruction.
	 */
	if (n > 0)
		goto reconstruct;

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
		error = EIO;
	} else if (total_errors < rm->rm_firstdatacol &&
	    (code = vdev_raidz_combrec(vd->spa, rm, bp, data, offset, bytes,
	     total_errors, data_errors)) != 0) {
		/*
		 * If we didn't use all the available parity for the
		 * combinatorial reconstruction, verify that the remaining
		 * parity is correct.
		 */
		if (code != (1 << rm->rm_firstdatacol) - 1)
			(void) raidz_parity_verify(rm);
	} else {
		/*
		 * We're here because either:
		 *
		 *	total_errors == rm_first_datacol, or
		 *	vdev_raidz_combrec() failed
		 *
		 * In either case, there is enough bad data to prevent
		 * reconstruction.
		 *
		 * Start checksum ereports for all children which haven't
		 * failed, and the IO wasn't speculative.
		 */
		error = ECKSUM;
	}

done:
	vdev_raidz_map_free(rm);

	return (error);
}