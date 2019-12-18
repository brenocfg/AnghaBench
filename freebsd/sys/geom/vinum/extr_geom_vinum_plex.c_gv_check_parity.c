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
struct gv_sd {TYPE_1__* drive_sc; } ;
struct gv_raid5_packet {int length; struct bio* parity; struct bio* waiting; } ;
struct gv_plex {int dummy; } ;
struct bio {scalar_t__* bio_data; TYPE_2__* bio_parent; struct gv_sd* bio_caller1; } ;
struct TYPE_4__ {int bio_pflags; int /*<<< orphan*/  bio_inbed; int /*<<< orphan*/  bio_error; } ;
struct TYPE_3__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int GV_BIO_PARITY ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  g_io_request (struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gv_check_parity(struct gv_plex *p, struct bio *bp, struct gv_raid5_packet *wp)
{
	struct bio *pbp;
	struct gv_sd *s;
	int err, finished, i;

	err = 0;
	finished = 1;

	if (wp->waiting != NULL) {
		pbp = wp->waiting;
		wp->waiting = NULL;
		s = pbp->bio_caller1;
		g_io_request(pbp, s->drive_sc->consumer);
		finished = 0;

	} else if (wp->parity != NULL) {
		pbp = wp->parity;
		wp->parity = NULL;

		/* Check if the parity is correct. */
		for (i = 0; i < wp->length; i++) {
			if (bp->bio_data[i] != pbp->bio_data[i]) {
				err = 1;
				break;
			}
		}

		/* The parity is not correct... */
		if (err) {
			bp->bio_parent->bio_error = EAGAIN;

			/* ... but we rebuild it. */
			if (bp->bio_parent->bio_pflags & GV_BIO_PARITY) {
				s = pbp->bio_caller1;
				g_io_request(pbp, s->drive_sc->consumer);
				finished = 0;
			}
		}

		/*
		 * Clean up the BIO we would have used for rebuilding the
		 * parity.
		 */
		if (finished) {
			bp->bio_parent->bio_inbed++;
			g_destroy_bio(pbp);
		}

	}

	return (finished);
}