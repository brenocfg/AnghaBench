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
struct ifnet {scalar_t__ if_init; struct ieee80211vap* if_softc; } ;
struct ieee80211vap {scalar_t__ iv_opmode; TYPE_1__* iv_ic; int /*<<< orphan*/  iv_rawbpf; } ;
struct TYPE_2__ {int /*<<< orphan*/  ic_montaps; } ;

/* Variables and functions */
 int DLT_IEEE802_11_RADIO ; 
 int /*<<< orphan*/  IEEE80211_FEXT_BPF ; 
 scalar_t__ IEEE80211_M_MONITOR ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bpf_peers_present (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_init ; 
 int /*<<< orphan*/  ieee80211_syncflag_ext (struct ieee80211vap*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bpf_track(void *arg, struct ifnet *ifp, int dlt, int attach)
{
	/* NB: identify vap's by if_init */
	if (dlt == DLT_IEEE802_11_RADIO &&
	    ifp->if_init == ieee80211_init) {
		struct ieee80211vap *vap = ifp->if_softc;
		/*
		 * Track bpf radiotap listener state.  We mark the vap
		 * to indicate if any listener is present and the com
		 * to indicate if any listener exists on any associated
		 * vap.  This flag is used by drivers to prepare radiotap
		 * state only when needed.
		 */
		if (attach) {
			ieee80211_syncflag_ext(vap, IEEE80211_FEXT_BPF);
			if (vap->iv_opmode == IEEE80211_M_MONITOR)
				atomic_add_int(&vap->iv_ic->ic_montaps, 1);
		} else if (!bpf_peers_present(vap->iv_rawbpf)) {
			ieee80211_syncflag_ext(vap, -IEEE80211_FEXT_BPF);
			if (vap->iv_opmode == IEEE80211_M_MONITOR)
				atomic_subtract_int(&vap->iv_ic->ic_montaps, 1);
		}
	}
}