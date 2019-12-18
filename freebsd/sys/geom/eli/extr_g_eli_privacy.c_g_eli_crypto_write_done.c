#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct g_geom {int /*<<< orphan*/  consumer; struct g_eli_softc* softc; } ;
struct g_eli_softc {int /*<<< orphan*/  sc_inflight; } ;
struct g_consumer {TYPE_2__* provider; } ;
struct cryptop {scalar_t__ crp_etype; TYPE_1__* crp_desc; scalar_t__ crp_opaque; } ;
struct bio {int bio_inbed; int bio_children; scalar_t__ bio_error; TYPE_2__* bio_to; int /*<<< orphan*/  bio_done; int /*<<< orphan*/ * bio_driver2; int /*<<< orphan*/ * bio_data; struct bio* bio_driver1; } ;
struct TYPE_4__ {struct g_geom* geom; } ;
struct TYPE_3__ {int /*<<< orphan*/  crd_key; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  G_ELI_DEBUG (int,char*,int,int,...) ; 
 int /*<<< orphan*/  G_ELI_LOGREQ (int,struct bio*,char*,...) ; 
 struct g_consumer* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_ELI ; 
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 scalar_t__ g_eli_crypto_rerun (struct cryptop*) ; 
 int /*<<< orphan*/  g_eli_key_drop (struct g_eli_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_eli_write_done ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,scalar_t__) ; 
 int /*<<< orphan*/  g_io_request (struct bio*,struct g_consumer*) ; 

__attribute__((used)) static int
g_eli_crypto_write_done(struct cryptop *crp)
{
	struct g_eli_softc *sc;
	struct g_geom *gp;
	struct g_consumer *cp;
	struct bio *bp, *cbp;

	if (crp->crp_etype == EAGAIN) {
		if (g_eli_crypto_rerun(crp) == 0)
			return (0);
	}
	bp = (struct bio *)crp->crp_opaque;
	bp->bio_inbed++;
	if (crp->crp_etype == 0) {
		G_ELI_DEBUG(3, "Crypto WRITE request done (%d/%d).",
		    bp->bio_inbed, bp->bio_children);
	} else {
		G_ELI_DEBUG(1, "Crypto WRITE request failed (%d/%d) error=%d.",
		    bp->bio_inbed, bp->bio_children, crp->crp_etype);
		if (bp->bio_error == 0)
			bp->bio_error = crp->crp_etype;
	}
	gp = bp->bio_to->geom;
	sc = gp->softc;
	g_eli_key_drop(sc, crp->crp_desc->crd_key);
	/*
	 * All sectors are already encrypted?
	 */
	if (bp->bio_inbed < bp->bio_children)
		return (0);
	bp->bio_inbed = 0;
	bp->bio_children = 1;
	cbp = bp->bio_driver1;
	bp->bio_driver1 = NULL;
	if (bp->bio_error != 0) {
		G_ELI_LOGREQ(0, bp, "Crypto WRITE request failed (error=%d).",
		    bp->bio_error);
		free(bp->bio_driver2, M_ELI);
		bp->bio_driver2 = NULL;
		g_destroy_bio(cbp);
		g_io_deliver(bp, bp->bio_error);
		atomic_subtract_int(&sc->sc_inflight, 1);
		return (0);
	}
	cbp->bio_data = bp->bio_driver2;
	cbp->bio_done = g_eli_write_done;
	cp = LIST_FIRST(&gp->consumer);
	cbp->bio_to = cp->provider;
	G_ELI_LOGREQ(2, cbp, "Sending request.");
	/*
	 * Send encrypted data to the provider.
	 */
	g_io_request(cbp, cp);
	return (0);
}