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
struct cpsw_softc {int /*<<< orphan*/  avail; int /*<<< orphan*/  dev; int /*<<< orphan*/  mbuf_dtag; int /*<<< orphan*/  _slots; } ;
struct cpsw_slot {int /*<<< orphan*/  dmamap; } ;
struct cpsw_queue {int /*<<< orphan*/  queue_slots; int /*<<< orphan*/  avail_queue_len; int /*<<< orphan*/  avail; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct cpsw_slot* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cpsw_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  next ; 
 int nitems (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cpsw_add_slots(struct cpsw_softc *sc, struct cpsw_queue *queue, int requested)
{
	const int max_slots = nitems(sc->_slots);
	struct cpsw_slot *slot;
	int i;

	if (requested < 0)
		requested = max_slots;

	for (i = 0; i < requested; ++i) {
		slot = STAILQ_FIRST(&sc->avail);
		if (slot == NULL)
			return (0);
		if (bus_dmamap_create(sc->mbuf_dtag, 0, &slot->dmamap)) {
			device_printf(sc->dev, "failed to create dmamap\n");
			return (ENOMEM);
		}
		STAILQ_REMOVE_HEAD(&sc->avail, next);
		STAILQ_INSERT_TAIL(&queue->avail, slot, next);
		++queue->avail_queue_len;
		++queue->queue_slots;
	}
	return (0);
}