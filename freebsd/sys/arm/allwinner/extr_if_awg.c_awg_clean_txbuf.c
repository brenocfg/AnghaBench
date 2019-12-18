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
struct TYPE_2__ {int /*<<< orphan*/  buf_tag; struct awg_bufmap* buf_map; int /*<<< orphan*/  queued; } ;
struct awg_softc {TYPE_1__ tx; } ;
struct awg_bufmap {int /*<<< orphan*/ * mbuf; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
awg_clean_txbuf(struct awg_softc *sc, int index)
{
	struct awg_bufmap *bmap;

	--sc->tx.queued;

	bmap = &sc->tx.buf_map[index];
	if (bmap->mbuf != NULL) {
		bus_dmamap_sync(sc->tx.buf_tag, bmap->map,
		    BUS_DMASYNC_POSTWRITE);
		bus_dmamap_unload(sc->tx.buf_tag, bmap->map);
		m_freem(bmap->mbuf);
		bmap->mbuf = NULL;
	}
}