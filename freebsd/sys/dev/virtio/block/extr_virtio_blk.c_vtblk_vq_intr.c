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
struct vtblk_softc {int vtblk_flags; struct virtqueue* vtblk_vq; } ;
struct virtqueue {int dummy; } ;
struct bio_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (struct bio_queue*) ; 
 int VTBLK_FLAG_DETACH ; 
 int VTBLK_FLAG_SUSPEND ; 
 int /*<<< orphan*/  VTBLK_LOCK (struct vtblk_softc*) ; 
 int /*<<< orphan*/  VTBLK_UNLOCK (struct vtblk_softc*) ; 
 int /*<<< orphan*/  virtqueue_disable_intr (struct virtqueue*) ; 
 scalar_t__ virtqueue_enable_intr (struct virtqueue*) ; 
 int /*<<< orphan*/  vtblk_done_completed (struct vtblk_softc*,struct bio_queue*) ; 
 int /*<<< orphan*/  vtblk_queue_completed (struct vtblk_softc*,struct bio_queue*) ; 
 int /*<<< orphan*/  vtblk_startio (struct vtblk_softc*) ; 
 int /*<<< orphan*/  wakeup (struct virtqueue**) ; 

__attribute__((used)) static void
vtblk_vq_intr(void *xsc)
{
	struct vtblk_softc *sc;
	struct virtqueue *vq;
	struct bio_queue queue;

	sc = xsc;
	vq = sc->vtblk_vq;
	TAILQ_INIT(&queue);

	VTBLK_LOCK(sc);

again:
	if (sc->vtblk_flags & VTBLK_FLAG_DETACH)
		goto out;

	vtblk_queue_completed(sc, &queue);
	vtblk_startio(sc);

	if (virtqueue_enable_intr(vq) != 0) {
		virtqueue_disable_intr(vq);
		goto again;
	}

	if (sc->vtblk_flags & VTBLK_FLAG_SUSPEND)
		wakeup(&sc->vtblk_vq);

out:
	VTBLK_UNLOCK(sc);
	vtblk_done_completed(sc, &queue);
}