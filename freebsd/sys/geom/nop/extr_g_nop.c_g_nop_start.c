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
typedef  scalar_t__ u_int ;
struct g_provider {struct g_geom* geom; } ;
struct g_nop_softc {scalar_t__ sc_count_until_fail; int sc_rfailprob; int sc_wfailprob; scalar_t__ sc_rdelayprob; scalar_t__ sc_delaymsec; scalar_t__ sc_wdelayprob; int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_head_delay; scalar_t__ sc_offset; int /*<<< orphan*/  sc_error; int /*<<< orphan*/  sc_cmd2s; int /*<<< orphan*/  sc_cmd1s; int /*<<< orphan*/  sc_cmd0s; int /*<<< orphan*/  sc_flushes; int /*<<< orphan*/  sc_physpath; int /*<<< orphan*/  sc_getattrs; int /*<<< orphan*/  sc_deletes; int /*<<< orphan*/  sc_wrotebytes; int /*<<< orphan*/  sc_writes; int /*<<< orphan*/  sc_readbytes; int /*<<< orphan*/  sc_reads; } ;
struct g_nop_delay {int /*<<< orphan*/  dl_cal; struct bio* dl_bio; } ;
struct g_geom {int /*<<< orphan*/  provider; struct g_nop_softc* softc; } ;
struct bio {int bio_cmd; struct g_provider* bio_to; scalar_t__ bio_offset; int /*<<< orphan*/  bio_done; int /*<<< orphan*/  bio_attribute; int /*<<< orphan*/  bio_length; } ;

/* Variables and functions */
#define  BIO_CMD0 135 
#define  BIO_CMD1 134 
#define  BIO_CMD2 133 
#define  BIO_DELETE 132 
#define  BIO_FLUSH 131 
#define  BIO_GETATTR 130 
#define  BIO_READ 129 
#define  BIO_WRITE 128 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  G_NOP_LOGREQ (struct bio*,char*) ; 
 int /*<<< orphan*/  G_NOP_LOGREQLVL (int,struct bio*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct g_provider* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSEC_2_TICKS (scalar_t__) ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct g_nop_delay*,int /*<<< orphan*/ ) ; 
 int arc4random () ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct g_nop_delay*) ; 
 int /*<<< orphan*/  dl_next ; 
 struct bio* g_clone_bio (struct bio*) ; 
 int /*<<< orphan*/  g_handleattr_str (struct bio*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int /*<<< orphan*/ ) ; 
 struct g_nop_delay* g_malloc (int,int) ; 
 int /*<<< orphan*/  g_nop_kerneldump (struct bio*,struct g_nop_softc*) ; 
 int /*<<< orphan*/  g_nop_pass (struct bio*,struct g_geom*) ; 
 int /*<<< orphan*/  g_nop_pass_timeout ; 
 int /*<<< orphan*/  g_std_done ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
g_nop_start(struct bio *bp)
{
	struct g_nop_softc *sc;
	struct g_geom *gp;
	struct g_provider *pp;
	struct bio *cbp;
	u_int failprob, delayprob, delaytime;

	failprob = delayprob = 0;

	gp = bp->bio_to->geom;
	sc = gp->softc;

	G_NOP_LOGREQ(bp, "Request received.");
	mtx_lock(&sc->sc_lock);
	if (sc->sc_count_until_fail != 0 && --sc->sc_count_until_fail == 0) {
		sc->sc_rfailprob = 100;
		sc->sc_wfailprob = 100;
	}
	switch (bp->bio_cmd) {
	case BIO_READ:
		sc->sc_reads++;
		sc->sc_readbytes += bp->bio_length;
		failprob = sc->sc_rfailprob;
		delayprob = sc->sc_rdelayprob;
		delaytime = sc->sc_delaymsec;
		break;
	case BIO_WRITE:
		sc->sc_writes++;
		sc->sc_wrotebytes += bp->bio_length;
		failprob = sc->sc_wfailprob;
		delayprob = sc->sc_wdelayprob;
		delaytime = sc->sc_delaymsec;
		break;
	case BIO_DELETE:
		sc->sc_deletes++;
		break;
	case BIO_GETATTR:
		sc->sc_getattrs++;
		if (sc->sc_physpath &&
		    g_handleattr_str(bp, "GEOM::physpath", sc->sc_physpath))
			;
		else if (strcmp(bp->bio_attribute, "GEOM::kerneldump") == 0)
			g_nop_kerneldump(bp, sc);
		else
			/*
			 * Fallthrough to forwarding the GETATTR down to the
			 * lower level device.
			 */
			break;
		mtx_unlock(&sc->sc_lock);
		return;
	case BIO_FLUSH:
		sc->sc_flushes++;
		break;
	case BIO_CMD0:
		sc->sc_cmd0s++;
		break;
	case BIO_CMD1:
		sc->sc_cmd1s++;
		break;
	case BIO_CMD2:
		sc->sc_cmd2s++;
		break;
	}
	mtx_unlock(&sc->sc_lock);
	if (failprob > 0) {
		u_int rval;

		rval = arc4random() % 100;
		if (rval < failprob) {
			G_NOP_LOGREQLVL(1, bp, "Returning error=%d.", sc->sc_error);
			g_io_deliver(bp, sc->sc_error);
			return;
		}
	}

	cbp = g_clone_bio(bp);
	if (cbp == NULL) {
		g_io_deliver(bp, ENOMEM);
		return;
	}
	cbp->bio_done = g_std_done;
	cbp->bio_offset = bp->bio_offset + sc->sc_offset;
	pp = LIST_FIRST(&gp->provider);
	KASSERT(pp != NULL, ("NULL pp"));
	cbp->bio_to = pp;

	if (delayprob > 0) {
		struct g_nop_delay *gndelay;
		u_int rval;

		rval = arc4random() % 100;
		if (rval < delayprob) {
			gndelay = g_malloc(sizeof(*gndelay), M_NOWAIT | M_ZERO);
			if (gndelay != NULL) {
				callout_init(&gndelay->dl_cal, 1);

				gndelay->dl_bio = cbp;

				mtx_lock(&sc->sc_lock);
				TAILQ_INSERT_TAIL(&sc->sc_head_delay, gndelay,
				    dl_next);
				mtx_unlock(&sc->sc_lock);

				callout_reset(&gndelay->dl_cal,
				    MSEC_2_TICKS(delaytime), g_nop_pass_timeout,
				    gndelay);
				return;
			}
		}
	}

	g_nop_pass(cbp, gp);
}