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
struct vtblk_softc {struct vtblk_request* vtblk_req_ordered; int /*<<< orphan*/  vtblk_vq; } ;
struct vtblk_request {struct bio* vbr_bp; } ;
struct bio_queue {int dummy; } ;
struct bio {int /*<<< orphan*/  bio_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct bio_queue*,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_queue ; 
 struct vtblk_request* virtqueue_dequeue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vtblk_request_enqueue (struct vtblk_softc*,struct vtblk_request*) ; 
 int /*<<< orphan*/  vtblk_request_error (struct vtblk_request*) ; 

__attribute__((used)) static void
vtblk_queue_completed(struct vtblk_softc *sc, struct bio_queue *queue)
{
	struct vtblk_request *req;
	struct bio *bp;

	while ((req = virtqueue_dequeue(sc->vtblk_vq, NULL)) != NULL) {
		if (sc->vtblk_req_ordered != NULL) {
			MPASS(sc->vtblk_req_ordered == req);
			sc->vtblk_req_ordered = NULL;
		}

		bp = req->vbr_bp;
		bp->bio_error = vtblk_request_error(req);
		TAILQ_INSERT_TAIL(queue, bp, bio_queue);

		vtblk_request_enqueue(sc, req);
	}
}