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
struct ccd_s {scalar_t__ sc_secsize; int sc_flags; int sc_pick; int sc_size; scalar_t__* sc_blk; } ;
struct bio {scalar_t__ bio_cmd; scalar_t__ bio_offset; long bio_data; long bio_length; long bio_completed; int bio_error; int /*<<< orphan*/  bio_from; TYPE_2__* bio_to; } ;
typedef  scalar_t__ daddr_t ;
typedef  long caddr_t ;
struct TYPE_4__ {TYPE_1__* geom; } ;
struct TYPE_3__ {struct ccd_s* softc; } ;

/* Variables and functions */
 scalar_t__ BIO_GETATTR ; 
 scalar_t__ BIO_READ ; 
 int CCDF_MIRROR ; 
 int EINVAL ; 
 scalar_t__ btodb (long) ; 
 int ccdbuffer (struct bio**,struct ccd_s*,struct bio*,scalar_t__,long,long) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int) ; 
 int /*<<< orphan*/  g_io_request (struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_ccd_start(struct bio *bp)
{
	long bcount, rcount;
	struct bio *cbp[2];
	caddr_t addr;
	daddr_t bn;
	int err;
	struct ccd_s *cs;

	cs = bp->bio_to->geom->softc;

	/*
	 * Block all GETATTR requests, we wouldn't know which of our
	 * subdevices we should ship it off to.
	 * XXX: this may not be the right policy.
	 */
	if(bp->bio_cmd == BIO_GETATTR) {
		g_io_deliver(bp, EINVAL);
		return;
	}

	/*
	 * Translate the partition-relative block number to an absolute.
	 */
	bn = bp->bio_offset / cs->sc_secsize;

	/*
	 * Allocate component buffers and fire off the requests
	 */
	addr = bp->bio_data;
	for (bcount = bp->bio_length; bcount > 0; bcount -= rcount) {
		err = ccdbuffer(cbp, cs, bp, bn, addr, bcount);
		if (err) {
			bp->bio_completed += bcount;
			if (bp->bio_error == 0)
				bp->bio_error = err;
			if (bp->bio_completed == bp->bio_length)
				g_io_deliver(bp, bp->bio_error);
			return;
		}
		rcount = cbp[0]->bio_length;

		if (cs->sc_flags & CCDF_MIRROR) {
			/*
			 * Mirroring.  Writes go to both disks, reads are
			 * taken from whichever disk seems most appropriate.
			 *
			 * We attempt to localize reads to the disk whos arm
			 * is nearest the read request.  We ignore seeks due
			 * to writes when making this determination and we
			 * also try to avoid hogging.
			 */
			if (cbp[0]->bio_cmd != BIO_READ) {
				g_io_request(cbp[0], cbp[0]->bio_from);
				g_io_request(cbp[1], cbp[1]->bio_from);
			} else {
				int pick = cs->sc_pick;
				daddr_t range = cs->sc_size / 16;

				if (bn < cs->sc_blk[pick] - range ||
				    bn > cs->sc_blk[pick] + range
				) {
					cs->sc_pick = pick = 1 - pick;
				}
				cs->sc_blk[pick] = bn + btodb(rcount);
				g_io_request(cbp[pick], cbp[pick]->bio_from);
			}
		} else {
			/*
			 * Not mirroring
			 */
			g_io_request(cbp[0], cbp[0]->bio_from);
		}
		bn += btodb(rcount);
		addr += rcount;
	}
}