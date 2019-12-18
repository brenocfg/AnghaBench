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
struct cpsw_softc {int /*<<< orphan*/  avail; struct cpsw_slot* _slots; } ;
struct cpsw_slot {int /*<<< orphan*/  bd_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cpsw_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_cpdma_bd_offset (int) ; 
 int /*<<< orphan*/  next ; 
 int nitems (struct cpsw_slot*) ; 

__attribute__((used)) static void
cpsw_init_slots(struct cpsw_softc *sc)
{
	struct cpsw_slot *slot;
	int i;

	STAILQ_INIT(&sc->avail);

	/* Put the slot descriptors onto the global avail list. */
	for (i = 0; i < nitems(sc->_slots); i++) {
		slot = &sc->_slots[i];
		slot->bd_offset = cpsw_cpdma_bd_offset(i);
		STAILQ_INSERT_TAIL(&sc->avail, slot, next);
	}
}