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
typedef  int u_int ;
struct g_stripe_softc {int sc_stripesize; int sc_stripebits; int sc_ndisks; } ;
struct bio {int bio_cmd; int bio_offset; int bio_length; int bio_flags; int bio_error; TYPE_2__* bio_to; } ;
typedef  int off_t ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  error; TYPE_1__* geom; } ;
struct TYPE_3__ {struct g_stripe_softc* softc; } ;

/* Variables and functions */
#define  BIO_DELETE 132 
#define  BIO_FLUSH 131 
#define  BIO_GETATTR 130 
#define  BIO_READ 129 
 int BIO_UNMAPPED ; 
#define  BIO_WRITE 128 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  G_STRIPE_LOGREQ (struct bio*,char*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int MAXPHYS ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int) ; 
 scalar_t__ g_stripe_fast ; 
 int /*<<< orphan*/  g_stripe_fast_failed ; 
 int /*<<< orphan*/  g_stripe_flush (struct g_stripe_softc*,struct bio*) ; 
 int g_stripe_start_economic (struct bio*,int,int,int) ; 
 int g_stripe_start_fast (struct bio*,int,int,int) ; 

__attribute__((used)) static void
g_stripe_start(struct bio *bp)
{
	off_t offset, start, length, nstripe, stripesize;
	struct g_stripe_softc *sc;
	u_int no;
	int error, fast = 0;

	sc = bp->bio_to->geom->softc;
	/*
	 * If sc == NULL, provider's error should be set and g_stripe_start()
	 * should not be called at all.
	 */
	KASSERT(sc != NULL,
	    ("Provider's error should be set (error=%d)(device=%s).",
	    bp->bio_to->error, bp->bio_to->name));

	G_STRIPE_LOGREQ(bp, "Request received.");

	switch (bp->bio_cmd) {
	case BIO_READ:
	case BIO_WRITE:
	case BIO_DELETE:
		break;
	case BIO_FLUSH:
		g_stripe_flush(sc, bp);
		return;
	case BIO_GETATTR:
		/* To which provider it should be delivered? */
	default:
		g_io_deliver(bp, EOPNOTSUPP);
		return;
	}

	stripesize = sc->sc_stripesize;

	/*
	 * Calculations are quite messy, but fast I hope.
	 */

	/* Stripe number. */
	/* nstripe = bp->bio_offset / stripesize; */
	nstripe = bp->bio_offset >> (off_t)sc->sc_stripebits;
	/* Disk number. */
	no = nstripe % sc->sc_ndisks;
	/* Start position in stripe. */
	/* start = bp->bio_offset % stripesize; */
	start = bp->bio_offset & (stripesize - 1);
	/* Start position in disk. */
	/* offset = (nstripe / sc->sc_ndisks) * stripesize + start; */
	offset = ((nstripe / sc->sc_ndisks) << sc->sc_stripebits) + start;
	/* Length of data to operate. */
	length = MIN(bp->bio_length, stripesize - start);

	/*
	 * Do use "fast" mode when:
	 * 1. "Fast" mode is ON.
	 * and
	 * 2. Request size is less than or equal to MAXPHYS,
	 *    which should always be true.
	 * and
	 * 3. Request size is bigger than stripesize * ndisks. If it isn't,
	 *    there will be no need to send more than one I/O request to
	 *    a provider, so there is nothing to optmize.
	 * and
	 * 4. Request is not unmapped.
	 * and
	 * 5. It is not a BIO_DELETE.
	 */
	if (g_stripe_fast && bp->bio_length <= MAXPHYS &&
	    bp->bio_length >= stripesize * sc->sc_ndisks &&
	    (bp->bio_flags & BIO_UNMAPPED) == 0 &&
	    bp->bio_cmd != BIO_DELETE) {
		fast = 1;
	}
	error = 0;
	if (fast) {
		error = g_stripe_start_fast(bp, no, offset, length);
		if (error != 0)
			g_stripe_fast_failed++;
	}
	/*
	 * Do use "economic" when:
	 * 1. "Economic" mode is ON.
	 * or
	 * 2. "Fast" mode failed. It can only fail if there is no memory.
	 */
	if (!fast || error != 0)
		error = g_stripe_start_economic(bp, no, offset, length);
	if (error != 0) {
		if (bp->bio_error == 0)
			bp->bio_error = error;
		g_io_deliver(bp, bp->bio_error);
	}
}