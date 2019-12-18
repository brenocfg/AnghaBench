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
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct ccb_nvmeio {int dummy; } ;
union ccb {TYPE_2__ ccb_h; struct bio* ccb_bp; int /*<<< orphan*/  ccb_state; struct ccb_nvmeio nvmeio; struct nda_trim_request* ccb_trim; } ;
typedef  int /*<<< orphan*/  uint32_t ;
struct nvme_dsm_range {int /*<<< orphan*/  length; int /*<<< orphan*/  starting_lba; } ;
struct nda_trim_request {struct nvme_dsm_range* dsm; int /*<<< orphan*/  bps; } ;
struct nda_softc {int state; int /*<<< orphan*/  refcount; int /*<<< orphan*/  outstanding_cmds; int /*<<< orphan*/  trim_lbas; int /*<<< orphan*/  trim_ranges; int /*<<< orphan*/  trim_count; int /*<<< orphan*/  cam_iosched; TYPE_1__* disk; int /*<<< orphan*/  force_write_error; int /*<<< orphan*/  periodic_read_count; int /*<<< orphan*/  periodic_read_error; int /*<<< orphan*/  force_read_error; int /*<<< orphan*/  flags; } ;
struct cam_periph {int /*<<< orphan*/  path; scalar_t__ softc; } ;
struct bio {int const bio_cmd; int bio_flags; int bio_bcount; int bio_ma_offset; int bio_ma_n; int bio_offset; } ;
struct TYPE_3__ {int d_sectorsize; } ;

/* Variables and functions */
#define  BIO_DELETE 132 
#define  BIO_FLUSH 131 
#define  BIO_READ 130 
 int BIO_UNMAPPED ; 
#define  BIO_WRITE 129 
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 int /*<<< orphan*/  CAM_UNLOCKED ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_NVMEDA ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NDA_CCB_BUFFER_IO ; 
 int /*<<< orphan*/  NDA_CCB_TRIM ; 
 int /*<<< orphan*/  NDA_FLAG_DIRTY ; 
#define  NDA_STATE_NORMAL 128 
 int /*<<< orphan*/  NVME_OPC_READ ; 
 int /*<<< orphan*/  NVME_OPC_WRITE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_queue ; 
 int /*<<< orphan*/  biofinish (struct bio*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct bio* cam_iosched_next_bio (int /*<<< orphan*/ ) ; 
 struct bio* cam_iosched_next_trim (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_lock (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_unlock (struct cam_periph*) ; 
 int /*<<< orphan*/  htole32 (int) ; 
 int /*<<< orphan*/  htole64 (int) ; 
 struct nda_trim_request* malloc (int,int /*<<< orphan*/ ,int) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nda_max_trim_entries ; 
 int /*<<< orphan*/  nda_nvme_flush (struct nda_softc*,struct ccb_nvmeio*) ; 
 int /*<<< orphan*/  nda_nvme_rw_bio (struct nda_softc*,struct ccb_nvmeio*,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nda_nvme_trim (struct nda_softc*,struct ccb_nvmeio*,struct nvme_dsm_range*,struct nvme_dsm_range*) ; 
 int /*<<< orphan*/  ndaschedule (struct cam_periph*) ; 
 int /*<<< orphan*/  nitems (struct nvme_dsm_range*) ; 
 int round_page (int) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_release_ccb (union ccb*) ; 

__attribute__((used)) static void
ndastart(struct cam_periph *periph, union ccb *start_ccb)
{
	struct nda_softc *softc = (struct nda_softc *)periph->softc;
	struct ccb_nvmeio *nvmeio = &start_ccb->nvmeio;

	CAM_DEBUG(periph->path, CAM_DEBUG_TRACE, ("ndastart\n"));

	switch (softc->state) {
	case NDA_STATE_NORMAL:
	{
		struct bio *bp;

		bp = cam_iosched_next_bio(softc->cam_iosched);
		CAM_DEBUG(periph->path, CAM_DEBUG_TRACE, ("ndastart: bio %p\n", bp));
		if (bp == NULL) {
			xpt_release_ccb(start_ccb);
			break;
		}

		switch (bp->bio_cmd) {
		case BIO_WRITE:
			softc->flags |= NDA_FLAG_DIRTY;
			/* FALLTHROUGH */
		case BIO_READ:
		{
#ifdef CAM_TEST_FAILURE
			int fail = 0;

			/*
			 * Support the failure ioctls.  If the command is a
			 * read, and there are pending forced read errors, or
			 * if a write and pending write errors, then fail this
			 * operation with EIO.  This is useful for testing
			 * purposes.  Also, support having every Nth read fail.
			 *
			 * This is a rather blunt tool.
			 */
			if (bp->bio_cmd == BIO_READ) {
				if (softc->force_read_error) {
					softc->force_read_error--;
					fail = 1;
				}
				if (softc->periodic_read_error > 0) {
					if (++softc->periodic_read_count >=
					    softc->periodic_read_error) {
						softc->periodic_read_count = 0;
						fail = 1;
					}
				}
			} else {
				if (softc->force_write_error) {
					softc->force_write_error--;
					fail = 1;
				}
			}
			if (fail) {
				biofinish(bp, NULL, EIO);
				xpt_release_ccb(start_ccb);
				ndaschedule(periph);
				return;
			}
#endif
			KASSERT((bp->bio_flags & BIO_UNMAPPED) == 0 ||
			    round_page(bp->bio_bcount + bp->bio_ma_offset) /
			    PAGE_SIZE == bp->bio_ma_n,
			    ("Short bio %p", bp));
			nda_nvme_rw_bio(softc, &start_ccb->nvmeio, bp, bp->bio_cmd == BIO_READ ?
			    NVME_OPC_READ : NVME_OPC_WRITE);
			break;
		}
		case BIO_DELETE:
		{
			struct nvme_dsm_range *dsm_range, *dsm_end;
			struct nda_trim_request *trim;
			struct bio *bp1;
			int ents;
			uint32_t totalcount = 0, ranges = 0;

			trim = malloc(sizeof(*trim), M_NVMEDA, M_ZERO | M_NOWAIT);
			if (trim == NULL) {
				biofinish(bp, NULL, ENOMEM);
				xpt_release_ccb(start_ccb);
				ndaschedule(periph);
				return;
			}
			TAILQ_INIT(&trim->bps);
			bp1 = bp;
			ents = min(nitems(trim->dsm), nda_max_trim_entries);
			dsm_range = trim->dsm;
			dsm_end = dsm_range + ents;
			do {
				TAILQ_INSERT_TAIL(&trim->bps, bp1, bio_queue);
				dsm_range->length =
				    htole32(bp1->bio_bcount / softc->disk->d_sectorsize);
				dsm_range->starting_lba =
				    htole64(bp1->bio_offset / softc->disk->d_sectorsize);
				ranges++;
				totalcount += dsm_range->length;
				dsm_range++;
				if (dsm_range >= dsm_end)
					break;
				bp1 = cam_iosched_next_trim(softc->cam_iosched);
				/* XXX -- Could collapse adjacent ranges, but we don't for now */
				/* XXX -- Could limit based on total payload size */
			} while (bp1 != NULL);
			start_ccb->ccb_trim = trim;
			nda_nvme_trim(softc, &start_ccb->nvmeio, trim->dsm,
			    dsm_range - trim->dsm);
			start_ccb->ccb_state = NDA_CCB_TRIM;
			softc->trim_count++;
			softc->trim_ranges += ranges;
			softc->trim_lbas += totalcount;
			/*
			 * Note: We can have multiple TRIMs in flight, so we don't call
			 * cam_iosched_submit_trim(softc->cam_iosched);
			 * since that forces the I/O scheduler to only schedule one at a time.
			 * On NVMe drives, this is a performance disaster.
			 */
			goto out;
		}
		case BIO_FLUSH:
			nda_nvme_flush(softc, nvmeio);
			break;
		}
		start_ccb->ccb_state = NDA_CCB_BUFFER_IO;
		start_ccb->ccb_bp = bp;
out:
		start_ccb->ccb_h.flags |= CAM_UNLOCKED;
		softc->outstanding_cmds++;
		softc->refcount++;			/* For submission only */
		cam_periph_unlock(periph);
		xpt_action(start_ccb);
		cam_periph_lock(periph);
		softc->refcount--;			/* Submission done */

		/* May have more work to do, so ensure we stay scheduled */
		ndaschedule(periph);
		break;
		}
	}
}