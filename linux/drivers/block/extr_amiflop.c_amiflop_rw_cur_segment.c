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
struct request {int /*<<< orphan*/  bio; } ;
struct amiga_floppy_struct {char* trackbuf; int dirty; TYPE_2__* type; TYPE_1__* dtype; } ;
typedef  int /*<<< orphan*/  blk_status_t ;
struct TYPE_4__ {unsigned int sect_mult; } ;
struct TYPE_3__ {unsigned int sects; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
 int /*<<< orphan*/  BLK_STS_OK ; 
 scalar_t__ READ ; 
 char* bio_data (int /*<<< orphan*/ ) ; 
 unsigned int blk_rq_cur_sectors (struct request*) ; 
 unsigned int blk_rq_pos (struct request*) ; 
 int /*<<< orphan*/  fd_motor_on (int) ; 
 scalar_t__ flush_track_timer ; 
 int get_track (int,unsigned int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  mod_timer (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,unsigned int,unsigned int,char*) ; 
 scalar_t__ rq_data_dir (struct request*) ; 
 struct amiga_floppy_struct* unit ; 

__attribute__((used)) static blk_status_t amiflop_rw_cur_segment(struct amiga_floppy_struct *floppy,
					   struct request *rq)
{
	int drive = floppy - unit;
	unsigned int cnt, block, track, sector;
	char *data;

	for (cnt = 0; cnt < blk_rq_cur_sectors(rq); cnt++) {
#ifdef DEBUG
		printk("fd: sector %ld + %d requested for %s\n",
		       blk_rq_pos(rq), cnt,
		       (rq_data_dir(rq) == READ) ? "read" : "write");
#endif
		block = blk_rq_pos(rq) + cnt;
		track = block / (floppy->dtype->sects * floppy->type->sect_mult);
		sector = block % (floppy->dtype->sects * floppy->type->sect_mult);
		data = bio_data(rq->bio) + 512 * cnt;
#ifdef DEBUG
		printk("access to track %d, sector %d, with buffer at "
		       "0x%08lx\n", track, sector, data);
#endif

		if (get_track(drive, track) == -1)
			return BLK_STS_IOERR;

		if (rq_data_dir(rq) == READ) {
			memcpy(data, floppy->trackbuf + sector * 512, 512);
		} else {
			memcpy(floppy->trackbuf + sector * 512, data, 512);

			/* keep the drive spinning while writes are scheduled */
			if (!fd_motor_on(drive))
				return BLK_STS_IOERR;
			/*
			 * setup a callback to write the track buffer
			 * after a short (1 tick) delay.
			 */
			floppy->dirty = 1;
		        /* reset the timer */
			mod_timer (flush_track_timer + drive, jiffies + 1);
		}
	}

	return BLK_STS_OK;
}