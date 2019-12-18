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
struct bcm_bsc_softc {scalar_t__ sc_totlen; scalar_t__ sc_resid; scalar_t__ sc_dlen; void** sc_data; TYPE_1__* sc_curmsg; } ;
struct TYPE_2__ {scalar_t__ len; void** buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_BSC_DATA ; 
 void* BCM_BSC_READ (struct bcm_bsc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM_BSC_STATUS ; 
 int BCM_BSC_STATUS_RXD ; 
 int /*<<< orphan*/  DEBUGF (struct bcm_bsc_softc*,int,char*,void*) ; 

__attribute__((used)) static void
bcm_bsc_empty_rx_fifo(struct bcm_bsc_softc *sc)
{
	uint32_t status;

	/* Assumes sc_totlen > 0 and BCM_BSC_STATUS_RXD is asserted on entry. */
	do {
		if (sc->sc_resid == 0) {
			sc->sc_data  = sc->sc_curmsg->buf;
			sc->sc_dlen  = sc->sc_curmsg->len;
			sc->sc_resid = sc->sc_dlen;
			++sc->sc_curmsg;
		}
		do {
			*sc->sc_data = BCM_BSC_READ(sc, BCM_BSC_DATA);
			DEBUGF(sc, 1, "0x%02x ", *sc->sc_data); 
			++sc->sc_data;
			--sc->sc_resid;
			--sc->sc_totlen;
			status = BCM_BSC_READ(sc, BCM_BSC_STATUS);
		} while (sc->sc_resid > 0 && (status & BCM_BSC_STATUS_RXD));
	} while (sc->sc_totlen > 0 && (status & BCM_BSC_STATUS_RXD));
}