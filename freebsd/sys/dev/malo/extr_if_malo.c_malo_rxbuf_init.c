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
struct malo_softc {int dummy; } ;
struct malo_rxdesc {int /*<<< orphan*/  rxcontrol; int /*<<< orphan*/  physbuffdata; scalar_t__ nf; int /*<<< orphan*/  pktlen; scalar_t__ channel; int /*<<< orphan*/  status; scalar_t__ snr; scalar_t__ qosctrl; } ;
struct malo_rxbuf {int /*<<< orphan*/  bf_data; int /*<<< orphan*/ * bf_m; struct malo_rxdesc* bf_desc; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MALO_RXDESC_SYNC (struct malo_softc*,struct malo_rxdesc*,int) ; 
 int /*<<< orphan*/  MALO_RXD_CTRL_DRIVER_OWN ; 
 int /*<<< orphan*/  MALO_RXD_CTRL_OS_OWN ; 
 int /*<<< orphan*/  MALO_RXD_STATUS_IDLE ; 
 int /*<<< orphan*/  MALO_RXSIZE ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malo_getrxmbuf (struct malo_softc*,struct malo_rxbuf*) ; 

__attribute__((used)) static int
malo_rxbuf_init(struct malo_softc *sc, struct malo_rxbuf *bf)
{
	struct malo_rxdesc *ds;

	ds = bf->bf_desc;
	if (bf->bf_m == NULL) {
		bf->bf_m = malo_getrxmbuf(sc, bf);
		if (bf->bf_m == NULL) {
			/* mark descriptor to be skipped */
			ds->rxcontrol = MALO_RXD_CTRL_OS_OWN;
			/* NB: don't need PREREAD */
			MALO_RXDESC_SYNC(sc, ds, BUS_DMASYNC_PREWRITE);
			return ENOMEM;
		}
	}

	/*
	 * Setup descriptor.
	 */
	ds->qosctrl = 0;
	ds->snr = 0;
	ds->status = MALO_RXD_STATUS_IDLE;
	ds->channel = 0;
	ds->pktlen = htole16(MALO_RXSIZE);
	ds->nf = 0;
	ds->physbuffdata = htole32(bf->bf_data);
	/* NB: don't touch pPhysNext, set once */
	ds->rxcontrol = MALO_RXD_CTRL_DRIVER_OWN;
	MALO_RXDESC_SYNC(sc, ds, BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	return 0;
}