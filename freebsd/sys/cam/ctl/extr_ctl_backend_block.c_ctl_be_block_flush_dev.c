#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ctl_be_block_lun {int /*<<< orphan*/  vn; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  disk_stats; } ;
struct ctl_be_block_io {int num_bios_sent; int send_complete; int /*<<< orphan*/  ds_t0; } ;
struct cdevsw {int /*<<< orphan*/  (* d_strategy ) (struct bio*) ;} ;
struct cdev {int dummy; } ;
struct bio {int /*<<< orphan*/  bio_error; struct cdev* bio_dev; scalar_t__ bio_pblkno; struct ctl_be_block_io* bio_caller1; int /*<<< orphan*/  (* bio_done ) (struct bio*) ;scalar_t__ bio_data; scalar_t__ bio_offset; int /*<<< orphan*/  bio_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_FLUSH ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  binuptime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctl_be_block_biodone (struct bio*) ; 
 int /*<<< orphan*/  dev_relthread (struct cdev*,int) ; 
 int /*<<< orphan*/  devstat_start_transaction (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cdevsw* devvn_refthread (int /*<<< orphan*/ ,struct cdev**,int*) ; 
 struct bio* g_alloc_bio () ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct bio*) ; 

__attribute__((used)) static void
ctl_be_block_flush_dev(struct ctl_be_block_lun *be_lun,
		       struct ctl_be_block_io *beio)
{
	struct bio *bio;
	struct cdevsw *csw;
	struct cdev *dev;
	int ref;

	DPRINTF("entered\n");

	/* This can't fail, it's a blocking allocation. */
	bio = g_alloc_bio();

	bio->bio_cmd	    = BIO_FLUSH;
	bio->bio_offset	    = 0;
	bio->bio_data	    = 0;
	bio->bio_done	    = ctl_be_block_biodone;
	bio->bio_caller1    = beio;
	bio->bio_pblkno	    = 0;

	/*
	 * We don't need to acquire the LUN lock here, because we are only
	 * sending one bio, and so there is no other context to synchronize
	 * with.
	 */
	beio->num_bios_sent = 1;
	beio->send_complete = 1;

	binuptime(&beio->ds_t0);
	mtx_lock(&be_lun->io_lock);
	devstat_start_transaction(be_lun->disk_stats, &beio->ds_t0);
	mtx_unlock(&be_lun->io_lock);

	csw = devvn_refthread(be_lun->vn, &dev, &ref);
	if (csw) {
		bio->bio_dev = dev;
		csw->d_strategy(bio);
		dev_relthread(dev, ref);
	} else {
		bio->bio_error = ENXIO;
		ctl_be_block_biodone(bio);
	}
}