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
struct cpsw_softc {int /*<<< orphan*/  mbuf_dtag; } ;
struct cpsw_slot {int /*<<< orphan*/ * mbuf; int /*<<< orphan*/ * dmamap; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cpsw_free_slot(struct cpsw_softc *sc, struct cpsw_slot *slot)
{
	int error;

	if (slot->dmamap) {
		if (slot->mbuf)
			bus_dmamap_unload(sc->mbuf_dtag, slot->dmamap);
		error = bus_dmamap_destroy(sc->mbuf_dtag, slot->dmamap);
		KASSERT(error == 0, ("Mapping still active"));
		slot->dmamap = NULL;
	}
	if (slot->mbuf) {
		m_freem(slot->mbuf);
		slot->mbuf = NULL;
	}
}