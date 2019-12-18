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
struct mwl_txq {int /*<<< orphan*/  qnum; } ;
struct TYPE_2__ {int fwReleaseNumber; int /*<<< orphan*/  regionCode; int /*<<< orphan*/  hwVersion; } ;
struct mwl_softc {int sc_fwrelease; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_mh; struct mwl_txq** sc_ac2q; TYPE_1__ sc_hwspecs; } ;

/* Variables and functions */
 scalar_t__ MWL_RXBUF ; 
 scalar_t__ MWL_RXDESC ; 
 scalar_t__ MWL_TXBUF ; 
 int WME_AC_VO ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * ieee80211_wme_acnames ; 
 scalar_t__ mwl_hal_ismbsscapable (int /*<<< orphan*/ ) ; 
 scalar_t__ mwl_rxbuf ; 
 scalar_t__ mwl_rxdesc ; 
 scalar_t__ mwl_txbuf ; 

__attribute__((used)) static void
mwl_announce(struct mwl_softc *sc)
{

	device_printf(sc->sc_dev, "Rev A%d hardware, v%d.%d.%d.%d firmware (regioncode %d)\n",
		sc->sc_hwspecs.hwVersion,
		(sc->sc_hwspecs.fwReleaseNumber>>24) & 0xff,
		(sc->sc_hwspecs.fwReleaseNumber>>16) & 0xff,
		(sc->sc_hwspecs.fwReleaseNumber>>8) & 0xff,
		(sc->sc_hwspecs.fwReleaseNumber>>0) & 0xff,
		sc->sc_hwspecs.regionCode);
	sc->sc_fwrelease = sc->sc_hwspecs.fwReleaseNumber;

	if (bootverbose) {
		int i;
		for (i = 0; i <= WME_AC_VO; i++) {
			struct mwl_txq *txq = sc->sc_ac2q[i];
			device_printf(sc->sc_dev, "Use hw queue %u for %s traffic\n",
				txq->qnum, ieee80211_wme_acnames[i]);
		}
	}
	if (bootverbose || mwl_rxdesc != MWL_RXDESC)
		device_printf(sc->sc_dev, "using %u rx descriptors\n", mwl_rxdesc);
	if (bootverbose || mwl_rxbuf != MWL_RXBUF)
		device_printf(sc->sc_dev, "using %u rx buffers\n", mwl_rxbuf);
	if (bootverbose || mwl_txbuf != MWL_TXBUF)
		device_printf(sc->sc_dev, "using %u tx buffers\n", mwl_txbuf);
	if (bootverbose && mwl_hal_ismbsscapable(sc->sc_mh))
		device_printf(sc->sc_dev, "multi-bss support\n");
#ifdef MWL_TX_NODROP
	if (bootverbose)
		device_printf(sc->sc_dev, "no tx drop\n");
#endif
}