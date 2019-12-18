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
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_xname; } ;
struct hn_softc {int hn_flags; int hn_link_flags; struct ifnet* hn_ifp; } ;

/* Variables and functions */
 int HN_FLAG_RXVF ; 
 int HN_FLAG_SYNTH_ATTACHED ; 
 int HN_LINK_FLAG_LINKUP ; 
 int HN_LINK_FLAG_NETCHG ; 
 int /*<<< orphan*/  HN_LOCK (struct hn_softc*) ; 
 int /*<<< orphan*/  HN_NVS_DATAPATH_SYNTH ; 
 int /*<<< orphan*/  HN_NVS_DATAPATH_VF ; 
 int /*<<< orphan*/  HN_UNLOCK (struct hn_softc*) ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  NDIS_PACKET_TYPE_NONE ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  devctl_notify (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hn_ismyvf (struct hn_softc*,struct ifnet*) ; 
 int /*<<< orphan*/  hn_nvs_set_datapath (struct hn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hn_resume_mgmt (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_rxfilter_config (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_rxvf_set (struct hn_softc*,struct ifnet*) ; 
 int /*<<< orphan*/  hn_set_rxfilter (struct hn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hn_suspend_mgmt (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_vf_rss_fixup (struct hn_softc*,int) ; 
 int /*<<< orphan*/  hn_vf_rss_restore (struct hn_softc*) ; 
 int /*<<< orphan*/  if_link_state_change (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hn_rxvf_change(struct hn_softc *sc, struct ifnet *ifp, bool rxvf)
{
	struct ifnet *hn_ifp;

	HN_LOCK(sc);

	if (!(sc->hn_flags & HN_FLAG_SYNTH_ATTACHED))
		goto out;

	if (!hn_ismyvf(sc, ifp))
		goto out;
	hn_ifp = sc->hn_ifp;

	if (rxvf) {
		if (sc->hn_flags & HN_FLAG_RXVF)
			goto out;

		sc->hn_flags |= HN_FLAG_RXVF;
		hn_rxfilter_config(sc);
	} else {
		if (!(sc->hn_flags & HN_FLAG_RXVF))
			goto out;

		sc->hn_flags &= ~HN_FLAG_RXVF;
		if (hn_ifp->if_drv_flags & IFF_DRV_RUNNING)
			hn_rxfilter_config(sc);
		else
			hn_set_rxfilter(sc, NDIS_PACKET_TYPE_NONE);
	}

	hn_nvs_set_datapath(sc,
	    rxvf ? HN_NVS_DATAPATH_VF : HN_NVS_DATAPATH_SYNTH);

	hn_rxvf_set(sc, rxvf ? ifp : NULL);

	if (rxvf) {
		hn_vf_rss_fixup(sc, true);
		hn_suspend_mgmt(sc);
		sc->hn_link_flags &=
		    ~(HN_LINK_FLAG_LINKUP | HN_LINK_FLAG_NETCHG);
		if_link_state_change(hn_ifp, LINK_STATE_DOWN);
	} else {
		hn_vf_rss_restore(sc);
		hn_resume_mgmt(sc);
	}

	devctl_notify("HYPERV_NIC_VF", hn_ifp->if_xname,
	    rxvf ? "VF_UP" : "VF_DOWN", NULL);

	if (bootverbose) {
		if_printf(hn_ifp, "datapath is switched %s %s\n",
		    rxvf ? "to" : "from", ifp->if_xname);
	}
out:
	HN_UNLOCK(sc);
}