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
struct ifnet {int /*<<< orphan*/  if_drv_flags; int /*<<< orphan*/  if_xname; } ;
struct hn_softc {int hn_flags; int hn_xvf_flags; int hn_tx_ring_inuse; TYPE_2__* hn_tx_ring; TYPE_1__* hn_vf_ifp; struct ifnet* hn_ifp; } ;
struct TYPE_4__ {scalar_t__ hn_oactive; } ;
struct TYPE_3__ {int /*<<< orphan*/  if_flags; } ;

/* Variables and functions */
 int HN_FLAG_RXVF ; 
 int HN_FLAG_SYNTH_ATTACHED ; 
 int /*<<< orphan*/  HN_LOCK_ASSERT (struct hn_softc*) ; 
 int /*<<< orphan*/  HN_NVS_DATAPATH_SYNTH ; 
 int HN_XVFFLAG_ENABLED ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFF_UP ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  atomic_clear_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hn_nvs_set_datapath (struct hn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hn_polling (struct hn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hn_rxfilter_config (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_suspend_data (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_xpnt_vf_iocsetflags (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_xpnt_vf_saveifflags (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_xpnt_vf_setdisable (struct hn_softc*,int) ; 

__attribute__((used)) static void
hn_stop(struct hn_softc *sc, bool detaching)
{
	struct ifnet *ifp = sc->hn_ifp;
	int i;

	HN_LOCK_ASSERT(sc);

	KASSERT(sc->hn_flags & HN_FLAG_SYNTH_ATTACHED,
	    ("synthetic parts were not attached"));

	/* Clear RUNNING bit ASAP. */
	atomic_clear_int(&ifp->if_drv_flags, IFF_DRV_RUNNING);

	/* Disable polling. */
	hn_polling(sc, 0);

	if (sc->hn_xvf_flags & HN_XVFFLAG_ENABLED) {
		KASSERT(sc->hn_vf_ifp != NULL,
		    ("%s: VF is not attached", ifp->if_xname));

		/* Mark transparent mode VF as disabled. */
		hn_xpnt_vf_setdisable(sc, false /* keep hn_vf_ifp */);

		/*
		 * NOTE:
		 * Datapath setting must happen _before_ bringing
		 * the VF down.
		 */
		hn_nvs_set_datapath(sc, HN_NVS_DATAPATH_SYNTH);

		/*
		 * Bring the VF down.
		 */
		hn_xpnt_vf_saveifflags(sc);
		sc->hn_vf_ifp->if_flags &= ~IFF_UP;
		hn_xpnt_vf_iocsetflags(sc);
	}

	/* Suspend data transfers. */
	hn_suspend_data(sc);

	/* Clear OACTIVE bit. */
	atomic_clear_int(&ifp->if_drv_flags, IFF_DRV_OACTIVE);
	for (i = 0; i < sc->hn_tx_ring_inuse; ++i)
		sc->hn_tx_ring[i].hn_oactive = 0;

	/*
	 * If the non-transparent mode VF is active, make sure
	 * that the RX filter still allows packet reception.
	 */
	if (!detaching && (sc->hn_flags & HN_FLAG_RXVF))
		hn_rxfilter_config(sc);
}