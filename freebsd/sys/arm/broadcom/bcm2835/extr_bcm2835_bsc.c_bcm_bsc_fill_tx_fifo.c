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
typedef  int uint32_t ;
struct bcm_bsc_softc {scalar_t__ sc_totlen; scalar_t__ sc_resid; scalar_t__ sc_dlen; scalar_t__ sc_replen; int /*<<< orphan*/  sc_flags; TYPE_1__* sc_curmsg; int /*<<< orphan*/ * sc_data; } ;
struct TYPE_2__ {scalar_t__ len; int slave; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_BSC_DATA ; 
 int BCM_BSC_READ (struct bcm_bsc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_BSC_STATUS ; 
 int BCM_BSC_STATUS_TXD ; 
 int /*<<< orphan*/  BCM_BSC_WRITE (struct bcm_bsc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_I2C_READ ; 
 int /*<<< orphan*/  DEBUGF (struct bcm_bsc_softc*,int,char*,...) ; 
 int /*<<< orphan*/  DEVICE_DEBUGF (struct bcm_bsc_softc*,int,char*,int,...) ; 

__attribute__((used)) static void
bcm_bsc_fill_tx_fifo(struct bcm_bsc_softc *sc)
{
	uint32_t status;

	/* Assumes sc_totlen > 0 and BCM_BSC_STATUS_TXD is asserted on entry. */
	do {
		if (sc->sc_resid == 0) {
			sc->sc_data  = sc->sc_curmsg->buf;
			sc->sc_dlen  = sc->sc_curmsg->len;
			sc->sc_resid = sc->sc_dlen;
			++sc->sc_curmsg;
		}
		do {
			BCM_BSC_WRITE(sc, BCM_BSC_DATA, *sc->sc_data);
			DEBUGF(sc, 1, "0x%02x ", *sc->sc_data); 
			++sc->sc_data;
			--sc->sc_resid;
			--sc->sc_totlen;
			status = BCM_BSC_READ(sc, BCM_BSC_STATUS);
		} while (sc->sc_resid > 0 && (status & BCM_BSC_STATUS_TXD));
		/*
		 * If a repeat-start was pending and we just hit the end of a tx
		 * buffer, see if it's also the end of the writes that preceeded
		 * the repeat-start.  If so, log the repeat-start and the start
		 * of the following read, and return because we're not writing
		 * anymore (and TXD will be true because there's room to write
		 * in the fifo).
		 */
		if (sc->sc_replen > 0 && sc->sc_resid == 0) {
			sc->sc_replen -= sc->sc_dlen;
			if (sc->sc_replen == 0) {
				DEBUGF(sc, 1, " err=0\n");
				DEVICE_DEBUGF(sc, 2, "rstart 0x%02x\n",
				    sc->sc_curmsg->slave | 0x01);
				DEVICE_DEBUGF(sc, 1,
				    "read   0x%02x len %d: ",
				    sc->sc_curmsg->slave | 0x01,
				    sc->sc_totlen);
				sc->sc_flags |= BCM_I2C_READ;
				return;
			}
		}
	} while (sc->sc_totlen > 0 && (status & BCM_BSC_STATUS_TXD));
}