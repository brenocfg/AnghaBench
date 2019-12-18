#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct g_eli_softc {int /*<<< orphan*/  sc_inflight; } ;
struct cryptop {scalar_t__ crp_etype; TYPE_3__* crp_desc; scalar_t__ crp_olen; scalar_t__ crp_opaque; } ;
struct bio {scalar_t__ bio_inbed; scalar_t__ bio_children; scalar_t__ bio_error; scalar_t__ bio_completed; int /*<<< orphan*/ * bio_driver2; TYPE_2__* bio_to; } ;
struct TYPE_6__ {int /*<<< orphan*/  crd_key; } ;
struct TYPE_5__ {TYPE_1__* geom; } ;
struct TYPE_4__ {struct g_eli_softc* softc; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  G_ELI_DEBUG (int,char*,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  G_ELI_LOGREQ (int /*<<< orphan*/ ,struct bio*,char*,scalar_t__) ; 
 int /*<<< orphan*/  M_ELI ; 
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ g_eli_crypto_rerun (struct cryptop*) ; 
 int /*<<< orphan*/  g_eli_key_drop (struct g_eli_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,scalar_t__) ; 

__attribute__((used)) static int
g_eli_crypto_read_done(struct cryptop *crp)
{
	struct g_eli_softc *sc;
	struct bio *bp;

	if (crp->crp_etype == EAGAIN) {
		if (g_eli_crypto_rerun(crp) == 0)
			return (0);
	}
	bp = (struct bio *)crp->crp_opaque;
	bp->bio_inbed++;
	if (crp->crp_etype == 0) {
		G_ELI_DEBUG(3, "Crypto READ request done (%d/%d).",
		    bp->bio_inbed, bp->bio_children);
		bp->bio_completed += crp->crp_olen;
	} else {
		G_ELI_DEBUG(1, "Crypto READ request failed (%d/%d) error=%d.",
		    bp->bio_inbed, bp->bio_children, crp->crp_etype);
		if (bp->bio_error == 0)
			bp->bio_error = crp->crp_etype;
	}
	sc = bp->bio_to->geom->softc;
	if (sc != NULL)
		g_eli_key_drop(sc, crp->crp_desc->crd_key);
	/*
	 * Do we have all sectors already?
	 */
	if (bp->bio_inbed < bp->bio_children)
		return (0);
	free(bp->bio_driver2, M_ELI);
	bp->bio_driver2 = NULL;
	if (bp->bio_error != 0) {
		G_ELI_LOGREQ(0, bp, "Crypto READ request failed (error=%d).",
		    bp->bio_error);
		bp->bio_completed = 0;
	}
	/*
	 * Read is finished, send it up.
	 */
	g_io_deliver(bp, bp->bio_error);
	if (sc != NULL)
		atomic_subtract_int(&sc->sc_inflight, 1);
	return (0);
}