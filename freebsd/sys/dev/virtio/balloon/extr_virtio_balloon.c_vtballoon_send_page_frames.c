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
typedef  int /*<<< orphan*/  uint32_t ;
struct vtballoon_softc {int /*<<< orphan*/  vtballoon_page_frames; } ;
typedef  void virtqueue ;
struct sglist_seg {int dummy; } ;
struct sglist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  VTBALLOON_LOCK (struct vtballoon_softc*) ; 
 int /*<<< orphan*/  VTBALLOON_MTX (struct vtballoon_softc*) ; 
 int /*<<< orphan*/  VTBALLOON_UNLOCK (struct vtballoon_softc*) ; 
 int /*<<< orphan*/  msleep (struct vtballoon_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int sglist_append (struct sglist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sglist_init (struct sglist*,int,struct sglist_seg*) ; 
 void* virtqueue_dequeue (void*,int /*<<< orphan*/ *) ; 
 int virtqueue_enqueue (void*,void*,struct sglist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_notify (void*) ; 

__attribute__((used)) static void
vtballoon_send_page_frames(struct vtballoon_softc *sc, struct virtqueue *vq,
    int npages)
{
	struct sglist sg;
	struct sglist_seg segs[1];
	void *c;
	int error;

	sglist_init(&sg, 1, segs);

	error = sglist_append(&sg, sc->vtballoon_page_frames,
	    npages * sizeof(uint32_t));
	KASSERT(error == 0, ("error adding page frames to sglist"));

	error = virtqueue_enqueue(vq, vq, &sg, 1, 0);
	KASSERT(error == 0, ("error enqueuing page frames to virtqueue"));
	virtqueue_notify(vq);

	/*
	 * Inflate and deflate operations are done synchronously. The
	 * interrupt handler will wake us up.
	 */
	VTBALLOON_LOCK(sc);
	while ((c = virtqueue_dequeue(vq, NULL)) == NULL)
		msleep(sc, VTBALLOON_MTX(sc), 0, "vtbspf", 0);
	VTBALLOON_UNLOCK(sc);

	KASSERT(c == vq, ("unexpected balloon operation response"));
}