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
struct mmcsd_softc {int /*<<< orphan*/  log_count; int /*<<< orphan*/  log_time; int /*<<< orphan*/  rca; int /*<<< orphan*/  mmcbus; int /*<<< orphan*/  dev; } ;
struct mmcsd_part {scalar_t__ running; scalar_t__ eend; scalar_t__ eblock; int /*<<< orphan*/  type; TYPE_1__* disk; scalar_t__ ro; int /*<<< orphan*/  disk_mtx; int /*<<< orphan*/  bio_queue; struct mmcsd_softc* sc; } ;
struct bio {scalar_t__ bio_cmd; int bio_resid; int bio_bcount; scalar_t__ bio_pblkno; int /*<<< orphan*/  bio_flags; void* bio_error; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ daddr_t ;
struct TYPE_2__ {int d_sectorsize; } ;

/* Variables and functions */
 scalar_t__ BIO_DELETE ; 
 int /*<<< orphan*/  BIO_ERROR ; 
 scalar_t__ BIO_FLUSH ; 
 scalar_t__ BIO_READ ; 
 scalar_t__ BIO_WRITE ; 
 void* EIO ; 
 void* EROFS ; 
 int /*<<< orphan*/  LOG_PPS ; 
 int /*<<< orphan*/  MMCBUS_ACQUIRE_BUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMCBUS_RELEASE_BUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMCSD_DISK_LOCK (struct mmcsd_part*) ; 
 int /*<<< orphan*/  MMCSD_DISK_UNLOCK (struct mmcsd_part*) ; 
 int MMC_ERR_NONE ; 
 int /*<<< orphan*/  PRIBIO ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  biodone (struct bio*) ; 
 struct bio* bioq_takefirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 scalar_t__ mmcsd_delete (struct mmcsd_part*,struct bio*) ; 
 int mmcsd_flush_cache (struct mmcsd_softc*) ; 
 scalar_t__ mmcsd_rw (struct mmcsd_part*,struct bio*) ; 
 int mmcsd_switch_part (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (struct mmcsd_part*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ppsratecheck (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (struct mmcsd_part*) ; 

__attribute__((used)) static void
mmcsd_task(void *arg)
{
	daddr_t block, end;
	struct mmcsd_part *part;
	struct mmcsd_softc *sc;
	struct bio *bp;
	device_t dev, mmcbus;
	int err, sz;

	part = arg;
	sc = part->sc;
	dev = sc->dev;
	mmcbus = sc->mmcbus;

	while (1) {
		MMCSD_DISK_LOCK(part);
		do {
			if (part->running == 0)
				goto out;
			bp = bioq_takefirst(&part->bio_queue);
			if (bp == NULL)
				msleep(part, &part->disk_mtx, PRIBIO,
				    "mmcsd disk jobqueue", 0);
		} while (bp == NULL);
		MMCSD_DISK_UNLOCK(part);
		if (__predict_false(bp->bio_cmd == BIO_FLUSH)) {
			if (mmcsd_flush_cache(sc) != MMC_ERR_NONE) {
				bp->bio_error = EIO;
				bp->bio_flags |= BIO_ERROR;
			}
			biodone(bp);
			continue;
		}
		if (bp->bio_cmd != BIO_READ && part->ro) {
			bp->bio_error = EROFS;
			bp->bio_resid = bp->bio_bcount;
			bp->bio_flags |= BIO_ERROR;
			biodone(bp);
			continue;
		}
		MMCBUS_ACQUIRE_BUS(mmcbus, dev);
		sz = part->disk->d_sectorsize;
		block = bp->bio_pblkno;
		end = bp->bio_pblkno + (bp->bio_bcount / sz);
		err = mmcsd_switch_part(mmcbus, dev, sc->rca, part->type);
		if (err != MMC_ERR_NONE) {
			if (ppsratecheck(&sc->log_time, &sc->log_count,
			    LOG_PPS))
				device_printf(dev, "Partition switch error\n");
			goto release;
		}
		if (bp->bio_cmd == BIO_READ || bp->bio_cmd == BIO_WRITE) {
			/* Access to the remaining erase block obsoletes it. */
			if (block < part->eend && end > part->eblock)
				part->eblock = part->eend = 0;
			block = mmcsd_rw(part, bp);
		} else if (bp->bio_cmd == BIO_DELETE) {
			block = mmcsd_delete(part, bp);
		}
release:
		MMCBUS_RELEASE_BUS(mmcbus, dev);
		if (block < end) {
			bp->bio_error = EIO;
			bp->bio_resid = (end - block) * sz;
			bp->bio_flags |= BIO_ERROR;
		} else {
			bp->bio_resid = 0;
		}
		biodone(bp);
	}
out:
	/* tell parent we're done */
	part->running = -1;
	MMCSD_DISK_UNLOCK(part);
	wakeup(part);

	kproc_exit(0);
}