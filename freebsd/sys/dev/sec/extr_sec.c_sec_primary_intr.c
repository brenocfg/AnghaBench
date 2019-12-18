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
typedef  int uint64_t ;
struct sec_softc {int sc_int_error_mask; int sc_blocked; int /*<<< orphan*/  sc_cid; int /*<<< orphan*/  sc_shutdown; int /*<<< orphan*/  sc_dev; } ;
struct sec_desc {scalar_t__ sd_error; TYPE_2__* sd_crp; TYPE_1__* sd_desc; } ;
struct TYPE_4__ {scalar_t__ crp_etype; } ;
struct TYPE_3__ {int shd_done; } ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 scalar_t__ EIO ; 
 int SEC_CHANNELS ; 
 int /*<<< orphan*/  SEC_CHAN_CDPR (int) ; 
 int /*<<< orphan*/  SEC_DESC_FREE_LT (struct sec_softc*,struct sec_desc*) ; 
 int /*<<< orphan*/  SEC_DESC_FREE_POINTERS (struct sec_desc*) ; 
 int /*<<< orphan*/  SEC_DESC_QUEUED2FREE (struct sec_softc*) ; 
 int /*<<< orphan*/  SEC_DESC_SYNC (struct sec_softc*,int) ; 
 int /*<<< orphan*/  SEC_DESC_SYNC_POINTERS (struct sec_desc*,int) ; 
 struct sec_desc* SEC_GET_QUEUED_DESC (struct sec_softc*) ; 
 int /*<<< orphan*/  SEC_ICR ; 
 int SEC_INT_CH_ERR (int) ; 
 int /*<<< orphan*/  SEC_ISR ; 
 int /*<<< orphan*/  SEC_LOCK (struct sec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEC_PUT_BACK_QUEUED_DESC (struct sec_softc*) ; 
 scalar_t__ SEC_QUEUED_DESC_CNT (struct sec_softc*) ; 
 int SEC_READ (struct sec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEC_UNLOCK (struct sec_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEC_WRITE (struct sec_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  controller ; 
 int /*<<< orphan*/  crypto_done (TYPE_2__*) ; 
 int /*<<< orphan*/  crypto_unblock (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  descriptors ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sec_channel_reset (struct sec_softc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_enqueue (struct sec_softc*) ; 
 struct sec_desc* sec_find_desc (struct sec_softc*,int) ; 

__attribute__((used)) static void
sec_primary_intr(void *arg)
{
	struct sec_softc *sc = arg;
	struct sec_desc *desc;
	uint64_t isr;
	int i, wakeup = 0;

	SEC_LOCK(sc, controller);

	/* Check for errors */
	isr = SEC_READ(sc, SEC_ISR);
	if (isr & sc->sc_int_error_mask) {
		/* Check each channel for error */
		for (i = 0; i < SEC_CHANNELS; i++) {
			if ((isr & SEC_INT_CH_ERR(i)) == 0)
				continue;

			device_printf(sc->sc_dev,
			    "I/O error on channel %i!\n", i);

			/* Find and mark problematic descriptor */
			desc = sec_find_desc(sc, SEC_READ(sc,
			    SEC_CHAN_CDPR(i)));

			if (desc != NULL)
				desc->sd_error = EIO;

			/* Do partial channel reset */
			sec_channel_reset(sc, i, 0);
		}
	}

	/* ACK interrupt */
	SEC_WRITE(sc, SEC_ICR, 0xFFFFFFFFFFFFFFFFULL);

	SEC_UNLOCK(sc, controller);
	SEC_LOCK(sc, descriptors);

	/* Handle processed descriptors */
	SEC_DESC_SYNC(sc, BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	while (SEC_QUEUED_DESC_CNT(sc) > 0) {
		desc = SEC_GET_QUEUED_DESC(sc);

		if (desc->sd_desc->shd_done != 0xFF && desc->sd_error == 0) {
			SEC_PUT_BACK_QUEUED_DESC(sc);
			break;
		}

		SEC_DESC_SYNC_POINTERS(desc, BUS_DMASYNC_PREREAD |
		    BUS_DMASYNC_PREWRITE);

		desc->sd_crp->crp_etype = desc->sd_error;
		crypto_done(desc->sd_crp);

		SEC_DESC_FREE_POINTERS(desc);
		SEC_DESC_FREE_LT(sc, desc);
		SEC_DESC_QUEUED2FREE(sc);
	}

	SEC_DESC_SYNC(sc, BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);

	if (!sc->sc_shutdown) {
		wakeup = sc->sc_blocked;
		sc->sc_blocked = 0;
	}

	SEC_UNLOCK(sc, descriptors);

	/* Enqueue ready descriptors in hardware */
	sec_enqueue(sc);

	if (wakeup)
		crypto_unblock(sc->sc_cid, wakeup);
}