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
struct g_bde_work {scalar_t__ length; scalar_t__ data; scalar_t__ offset; struct bio* bp; } ;
struct g_bde_softc {int /*<<< orphan*/  worklist_mutex; } ;
struct bio {scalar_t__ bio_length; scalar_t__ bio_offset; scalar_t__ bio_data; scalar_t__ bio_error; struct g_bde_softc* bio_driver1; TYPE_2__* bio_to; } ;
typedef  scalar_t__ off_t ;
struct TYPE_4__ {TYPE_1__* geom; } ;
struct TYPE_3__ {struct g_bde_softc* softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  g_bde_contribute (struct bio*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_bde_map_sector (struct g_bde_work*) ; 
 struct g_bde_work* g_bde_new_work (struct g_bde_softc*) ; 
 int /*<<< orphan*/  g_bde_start2 (struct g_bde_work*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
g_bde_start1(struct bio *bp)
{
	struct g_bde_softc *sc;
	struct g_bde_work *wp;
	off_t done;

	sc = bp->bio_to->geom->softc;
	bp->bio_driver1 = sc;

	mtx_lock(&sc->worklist_mutex);
	for(done = 0; done < bp->bio_length; ) {
		wp = g_bde_new_work(sc);
		if (wp != NULL) {
			wp->bp = bp;
			wp->offset = bp->bio_offset + done;
			wp->data = bp->bio_data + done;
			wp->length = bp->bio_length - done;
			g_bde_map_sector(wp);
			done += wp->length;
			g_bde_start2(wp);
		}
		if (wp == NULL || bp->bio_error != 0) {
			g_bde_contribute(bp, bp->bio_length - done, ENOMEM);
			break;
		}
	}
	mtx_unlock(&sc->worklist_mutex);
	return;
}