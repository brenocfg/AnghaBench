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
struct gv_sd {TYPE_1__* drive_sc; } ;
struct gv_raid5_packet {scalar_t__ length; int lockbase; int /*<<< orphan*/  bits; } ;
struct gv_plex {scalar_t__ org; int /*<<< orphan*/  bqueue; int /*<<< orphan*/  wqueue; int /*<<< orphan*/  packets; } ;
struct bio {scalar_t__ bio_length; scalar_t__ bio_offset; struct gv_sd* bio_caller1; int /*<<< orphan*/  bio_pflags; int /*<<< orphan*/ * bio_caller2; int /*<<< orphan*/  bio_data; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int /*<<< orphan*/  GV_BIO_ONHOLD ; 
 scalar_t__ GV_PLEX_RAID5 ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct gv_raid5_packet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bioq_disksort (int /*<<< orphan*/ ,struct bio*) ; 
 struct bio* bioq_takefirst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (struct gv_raid5_packet*) ; 
 int /*<<< orphan*/  g_io_request (struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ gv_plex_normal_request (struct gv_plex*,struct bio*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct gv_raid5_packet* gv_raid5_start (struct gv_plex*,struct bio*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ gv_stripe_active (struct gv_plex*,struct bio*) ; 
 int /*<<< orphan*/  list ; 

void
gv_plex_start(struct gv_plex *p, struct bio *bp)
{
	struct bio *cbp;
	struct gv_sd *s;
	struct gv_raid5_packet *wp;
	caddr_t addr;
	off_t bcount, boff, len;

	bcount = bp->bio_length;
	addr = bp->bio_data;
	boff = bp->bio_offset;

	/* Walk over the whole length of the request, we might split it up. */
	while (bcount > 0) {
		wp = NULL;

 		/*
		 * RAID5 plexes need special treatment, as a single request
		 * might involve several read/write sub-requests.
 		 */
		if (p->org == GV_PLEX_RAID5) {
			wp = gv_raid5_start(p, bp, addr, boff, bcount);
 			if (wp == NULL)
 				return;
 
			len = wp->length;

			if (TAILQ_EMPTY(&wp->bits))
				g_free(wp);
			else if (wp->lockbase != -1)
				TAILQ_INSERT_TAIL(&p->packets, wp, list);

		/*
		 * Requests to concatenated and striped plexes go straight
		 * through.
		 */
		} else {
			len = gv_plex_normal_request(p, bp, boff, bcount, addr);
		}
		if (len < 0)
			return;
			
		bcount -= len;
		addr += len;
		boff += len;
	}

	/*
	 * Fire off all sub-requests.  We get the correct consumer (== drive)
	 * to send each request to via the subdisk that was stored in
	 * cbp->bio_caller1.
	 */
	cbp = bioq_takefirst(p->bqueue);
	while (cbp != NULL) {
		/*
		 * RAID5 sub-requests need to come in correct order, otherwise
		 * we trip over the parity, as it might be overwritten by
		 * another sub-request.  We abuse cbp->bio_caller2 to mark
		 * potential overlap situations. 
		 */
		if (cbp->bio_caller2 != NULL && gv_stripe_active(p, cbp)) {
			/* Park the bio on the waiting queue. */
			cbp->bio_pflags |= GV_BIO_ONHOLD;
			bioq_disksort(p->wqueue, cbp);
		} else {
			s = cbp->bio_caller1;
			g_io_request(cbp, s->drive_sc->consumer);
		}
		cbp = bioq_takefirst(p->bqueue);
	}
}