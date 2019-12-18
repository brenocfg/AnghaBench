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
struct g_eli_softc {int /*<<< orphan*/  sc_queue; int /*<<< orphan*/  sc_queue_mtx; } ;
struct bio {scalar_t__ bio_pflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 scalar_t__ G_ELI_NEW_BIO ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 struct bio* bioq_takefirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_eli_cancel(struct g_eli_softc *sc)
{
	struct bio *bp;

	mtx_assert(&sc->sc_queue_mtx, MA_OWNED);

	while ((bp = bioq_takefirst(&sc->sc_queue)) != NULL) {
		KASSERT(bp->bio_pflags == G_ELI_NEW_BIO,
		    ("Not new bio when canceling (bp=%p).", bp));
		g_io_deliver(bp, ENXIO);
	}
}