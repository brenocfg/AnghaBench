#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct g_eli_softc {int sc_bytes_per_sector; TYPE_3__* sc_geom; int /*<<< orphan*/  sc_inflight; } ;
struct g_consumer {TYPE_4__* provider; } ;
struct cryptop {scalar_t__ crp_etype; TYPE_2__* crp_desc; scalar_t__ crp_opaque; } ;
struct bio {int bio_inbed; int bio_children; scalar_t__ bio_error; int bio_length; int bio_offset; void* bio_done; TYPE_4__* bio_to; int /*<<< orphan*/ * bio_data; int /*<<< orphan*/ * bio_driver2; struct bio* bio_driver1; } ;
struct TYPE_8__ {int sectorsize; TYPE_1__* geom; } ;
struct TYPE_7__ {int /*<<< orphan*/  consumer; } ;
struct TYPE_6__ {int /*<<< orphan*/  crd_key; } ;
struct TYPE_5__ {struct g_eli_softc* softc; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  G_ELI_DEBUG (int,char*,int,int,...) ; 
 int /*<<< orphan*/  G_ELI_LOGREQ (int,struct bio*,char*,...) ; 
 struct g_consumer* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int MAXPHYS ; 
 int /*<<< orphan*/  M_ELI ; 
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 struct bio* g_duplicate_bio (struct bio*) ; 
 scalar_t__ g_eli_crypto_rerun (struct cryptop*) ; 
 int /*<<< orphan*/  g_eli_key_drop (struct g_eli_softc*,int /*<<< orphan*/ ) ; 
 void* g_eli_write_done ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,scalar_t__) ; 
 int /*<<< orphan*/  g_io_request (struct bio*,struct g_consumer*) ; 

__attribute__((used)) static int
g_eli_auth_write_done(struct cryptop *crp)
{
	struct g_eli_softc *sc;
	struct g_consumer *cp;
	struct bio *bp, *cbp, *cbp2;
	u_int nsec;

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
	sc = bp->bio_to->geom->softc;
	g_eli_key_drop(sc, crp->crp_desc->crd_key);
	/*
	 * All sectors are already encrypted?
	 */
	if (bp->bio_inbed < bp->bio_children)
		return (0);
	if (bp->bio_error != 0) {
		G_ELI_LOGREQ(0, bp, "Crypto WRITE request failed (error=%d).",
		    bp->bio_error);
		free(bp->bio_driver2, M_ELI);
		bp->bio_driver2 = NULL;
		cbp = bp->bio_driver1;
		bp->bio_driver1 = NULL;
		g_destroy_bio(cbp);
		g_io_deliver(bp, bp->bio_error);
		atomic_subtract_int(&sc->sc_inflight, 1);
		return (0);
	}
	cp = LIST_FIRST(&sc->sc_geom->consumer);
	cbp = bp->bio_driver1;
	bp->bio_driver1 = NULL;
	cbp->bio_to = cp->provider;
	cbp->bio_done = g_eli_write_done;

	/* Number of sectors from decrypted provider, eg. 1. */
	nsec = bp->bio_length / bp->bio_to->sectorsize;
	/* Number of sectors from encrypted provider, eg. 9. */
	nsec = (nsec * sc->sc_bytes_per_sector) / cp->provider->sectorsize;

	cbp->bio_length = cp->provider->sectorsize * nsec;
	cbp->bio_offset = (bp->bio_offset / bp->bio_to->sectorsize) * sc->sc_bytes_per_sector;
	cbp->bio_data = bp->bio_driver2;

	/*
	 * We write more than what is requested, so we have to be ready to write
	 * more than MAXPHYS.
	 */
	cbp2 = NULL;
	if (cbp->bio_length > MAXPHYS) {
		cbp2 = g_duplicate_bio(bp);
		cbp2->bio_length = cbp->bio_length - MAXPHYS;
		cbp2->bio_data = cbp->bio_data + MAXPHYS;
		cbp2->bio_offset = cbp->bio_offset + MAXPHYS;
		cbp2->bio_to = cp->provider;
		cbp2->bio_done = g_eli_write_done;
		cbp->bio_length = MAXPHYS;
	}
	/*
	 * Send encrypted data to the provider.
	 */
	G_ELI_LOGREQ(2, cbp, "Sending request.");
	bp->bio_inbed = 0;
	bp->bio_children = (cbp2 != NULL ? 2 : 1);
	g_io_request(cbp, cp);
	if (cbp2 != NULL) {
		G_ELI_LOGREQ(2, cbp2, "Sending request.");
		g_io_request(cbp2, cp);
	}
	return (0);
}