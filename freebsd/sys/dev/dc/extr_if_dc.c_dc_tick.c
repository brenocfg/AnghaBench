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
struct mii_data {int /*<<< orphan*/  mii_media_active; } ;
struct ifnet {int /*<<< orphan*/  if_snd; } ;
struct TYPE_2__ {scalar_t__ dc_tx_cnt; } ;
struct dc_softc {int dc_flags; scalar_t__ dc_link; int /*<<< orphan*/  dc_stat_ch; TYPE_1__ dc_cdata; int /*<<< orphan*/  dc_miibus; struct ifnet* dc_ifp; } ;

/* Variables and functions */
 int CSR_READ_4 (struct dc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_10BTSTAT ; 
 int DC_21143_NWAY ; 
 scalar_t__ DC_HAS_BROKEN_RXSTATE (struct dc_softc*) ; 
 int /*<<< orphan*/  DC_ISR ; 
 int DC_ISR_RX_STATE ; 
 int /*<<< orphan*/  DC_LOCK_ASSERT (struct dc_softc*) ; 
 int DC_REDUCED_MII_POLL ; 
 int DC_RXSTATE_WAIT ; 
 int DC_TSTAT_LS10 ; 
 int DC_TSTAT_LS100 ; 
 int DC_TX_USE_TX_INTR ; 
 scalar_t__ IFM_100_TX ; 
 scalar_t__ IFM_10_T ; 
 scalar_t__ IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct dc_softc*) ; 
 int /*<<< orphan*/  dc_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  dc_txeof (struct dc_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  mii_mediachg (struct mii_data*) ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 

__attribute__((used)) static void
dc_tick(void *xsc)
{
	struct dc_softc *sc;
	struct mii_data *mii;
	struct ifnet *ifp;
	uint32_t r;

	sc = xsc;
	DC_LOCK_ASSERT(sc);
	ifp = sc->dc_ifp;
	mii = device_get_softc(sc->dc_miibus);

	/*
	 * Reclaim transmitted frames for controllers that do
	 * not generate TX completion interrupt for every frame.
	 */
	if (sc->dc_flags & DC_TX_USE_TX_INTR)
		dc_txeof(sc);

	if (sc->dc_flags & DC_REDUCED_MII_POLL) {
		if (sc->dc_flags & DC_21143_NWAY) {
			r = CSR_READ_4(sc, DC_10BTSTAT);
			if (IFM_SUBTYPE(mii->mii_media_active) ==
			    IFM_100_TX && (r & DC_TSTAT_LS100)) {
				sc->dc_link = 0;
				mii_mediachg(mii);
			}
			if (IFM_SUBTYPE(mii->mii_media_active) ==
			    IFM_10_T && (r & DC_TSTAT_LS10)) {
				sc->dc_link = 0;
				mii_mediachg(mii);
			}
			if (sc->dc_link == 0)
				mii_tick(mii);
		} else {
			/*
			 * For NICs which never report DC_RXSTATE_WAIT, we
			 * have to bite the bullet...
			 */
			if ((DC_HAS_BROKEN_RXSTATE(sc) || (CSR_READ_4(sc,
			    DC_ISR) & DC_ISR_RX_STATE) == DC_RXSTATE_WAIT) &&
			    sc->dc_cdata.dc_tx_cnt == 0)
				mii_tick(mii);
		}
	} else
		mii_tick(mii);

	/*
	 * When the init routine completes, we expect to be able to send
	 * packets right away, and in fact the network code will send a
	 * gratuitous ARP the moment the init routine marks the interface
	 * as running. However, even though the MAC may have been initialized,
	 * there may be a delay of a few seconds before the PHY completes
	 * autonegotiation and the link is brought up. Any transmissions
	 * made during that delay will be lost. Dealing with this is tricky:
	 * we can't just pause in the init routine while waiting for the
	 * PHY to come ready since that would bring the whole system to
	 * a screeching halt for several seconds.
	 *
	 * What we do here is prevent the TX start routine from sending
	 * any packets until a link has been established. After the
	 * interface has been initialized, the tick routine will poll
	 * the state of the PHY until the IFM_ACTIVE flag is set. Until
	 * that time, packets will stay in the send queue, and once the
	 * link comes up, they will be flushed out to the wire.
	 */
	if (sc->dc_link != 0 && !IFQ_DRV_IS_EMPTY(&ifp->if_snd))
		dc_start_locked(ifp);

	if (sc->dc_flags & DC_21143_NWAY && !sc->dc_link)
		callout_reset(&sc->dc_stat_ch, hz/10, dc_tick, sc);
	else
		callout_reset(&sc->dc_stat_ch, hz, dc_tick, sc);
}