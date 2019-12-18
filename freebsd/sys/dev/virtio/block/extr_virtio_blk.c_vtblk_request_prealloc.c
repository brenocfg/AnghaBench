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
struct vtblk_softc {int vtblk_flags; int /*<<< orphan*/  vtblk_request_count; int /*<<< orphan*/  vtblk_vq; } ;
struct vtblk_request {int /*<<< orphan*/  vbr_ack; int /*<<< orphan*/  vbr_hdr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int VTBLK_FLAG_INDIRECT ; 
 int VTBLK_MIN_SEGMENTS ; 
 struct vtblk_request* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sglist_count (int /*<<< orphan*/ *,int) ; 
 int virtqueue_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtblk_request_enqueue (struct vtblk_softc*,struct vtblk_request*) ; 

__attribute__((used)) static int
vtblk_request_prealloc(struct vtblk_softc *sc)
{
	struct vtblk_request *req;
	int i, nreqs;

	nreqs = virtqueue_size(sc->vtblk_vq);

	/*
	 * Preallocate sufficient requests to keep the virtqueue full. Each
	 * request consumes VTBLK_MIN_SEGMENTS or more descriptors so reduce
	 * the number allocated when indirect descriptors are not available.
	 */
	if ((sc->vtblk_flags & VTBLK_FLAG_INDIRECT) == 0)
		nreqs /= VTBLK_MIN_SEGMENTS;

	for (i = 0; i < nreqs; i++) {
		req = malloc(sizeof(struct vtblk_request), M_DEVBUF, M_NOWAIT);
		if (req == NULL)
			return (ENOMEM);

		MPASS(sglist_count(&req->vbr_hdr, sizeof(req->vbr_hdr)) == 1);
		MPASS(sglist_count(&req->vbr_ack, sizeof(req->vbr_ack)) == 1);

		sc->vtblk_request_count++;
		vtblk_request_enqueue(sc, req);
	}

	return (0);
}