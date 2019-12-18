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
struct gv_raid5_packet {int length; struct bio* parity; struct bio* waiting; } ;
struct gv_plex {int dummy; } ;
struct bio {struct gv_sd* bio_caller1; int /*<<< orphan*/ * bio_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_io_request (struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gv_normal_parity(struct gv_plex *p, struct bio *bp, struct gv_raid5_packet *wp)
{
	struct bio *cbp, *pbp;
	struct gv_sd *s;
	int finished, i;

	finished = 1;

	if (wp->waiting != NULL) {
		pbp = wp->waiting;
		wp->waiting = NULL;
		cbp = wp->parity;
		for (i = 0; i < wp->length; i++)
			cbp->bio_data[i] ^= pbp->bio_data[i];
		s = pbp->bio_caller1;
		g_io_request(pbp, s->drive_sc->consumer);
		finished = 0;

	} else if (wp->parity != NULL) {
		cbp = wp->parity;
		wp->parity = NULL;
		s = cbp->bio_caller1;
		g_io_request(cbp, s->drive_sc->consumer);
		finished = 0;
	}

	return (finished);
}