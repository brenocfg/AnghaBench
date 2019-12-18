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
struct vtblk_softc {int /*<<< orphan*/ * vtblk_req_ordered; struct virtqueue* vtblk_vq; } ;
struct vtblk_request {int /*<<< orphan*/  vbr_bp; } ;
struct virtqueue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct vtblk_request* virtqueue_drain (struct virtqueue*,int*) ; 
 int /*<<< orphan*/  virtqueue_empty (struct virtqueue*) ; 
 int /*<<< orphan*/  vtblk_bio_done (struct vtblk_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtblk_request_enqueue (struct vtblk_softc*,struct vtblk_request*) ; 

__attribute__((used)) static void
vtblk_drain_vq(struct vtblk_softc *sc)
{
	struct virtqueue *vq;
	struct vtblk_request *req;
	int last;

	vq = sc->vtblk_vq;
	last = 0;

	while ((req = virtqueue_drain(vq, &last)) != NULL) {
		vtblk_bio_done(sc, req->vbr_bp, ENXIO);
		vtblk_request_enqueue(sc, req);
	}

	sc->vtblk_req_ordered = NULL;
	KASSERT(virtqueue_empty(vq), ("virtqueue not empty"));
}