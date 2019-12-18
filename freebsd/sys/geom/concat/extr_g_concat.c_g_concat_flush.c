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
typedef  size_t u_int ;
struct g_consumer {int /*<<< orphan*/  provider; } ;
struct g_concat_softc {size_t sc_ndisks; TYPE_1__* sc_disks; } ;
struct bio_queue_head {int dummy; } ;
struct bio {scalar_t__ bio_error; struct g_consumer* bio_caller1; int /*<<< orphan*/  bio_to; int /*<<< orphan*/  bio_done; } ;
struct TYPE_2__ {struct g_consumer* d_consumer; } ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  G_CONCAT_LOGREQ (struct bio*,char*) ; 
 int /*<<< orphan*/  bioq_init (struct bio_queue_head*) ; 
 int /*<<< orphan*/  bioq_insert_tail (struct bio_queue_head*,struct bio*) ; 
 struct bio* bioq_takefirst (struct bio_queue_head*) ; 
 struct bio* g_clone_bio (struct bio*) ; 
 int /*<<< orphan*/  g_concat_done ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,scalar_t__) ; 
 int /*<<< orphan*/  g_io_request (struct bio*,struct g_consumer*) ; 

__attribute__((used)) static void
g_concat_flush(struct g_concat_softc *sc, struct bio *bp)
{
	struct bio_queue_head queue;
	struct g_consumer *cp;
	struct bio *cbp;
	u_int no;

	bioq_init(&queue);
	for (no = 0; no < sc->sc_ndisks; no++) {
		cbp = g_clone_bio(bp);
		if (cbp == NULL) {
			while ((cbp = bioq_takefirst(&queue)) != NULL)
				g_destroy_bio(cbp);
			if (bp->bio_error == 0)
				bp->bio_error = ENOMEM;
			g_io_deliver(bp, bp->bio_error);
			return;
		}
		bioq_insert_tail(&queue, cbp);
		cbp->bio_done = g_concat_done;
		cbp->bio_caller1 = sc->sc_disks[no].d_consumer;
		cbp->bio_to = sc->sc_disks[no].d_consumer->provider;
	}
	while ((cbp = bioq_takefirst(&queue)) != NULL) {
		G_CONCAT_LOGREQ(cbp, "Sending request.");
		cp = cbp->bio_caller1;
		cbp->bio_caller1 = NULL;
		g_io_request(cbp, cp);
	}
}