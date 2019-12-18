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
typedef  int /*<<< orphan*/  uint64_t ;
struct ifnet {struct ieee80211vap* if_softc; } ;
struct ieee80211vap {struct ieee80211com* iv_ic; } ;
struct ieee80211com {int /*<<< orphan*/  ic_ierrors; int /*<<< orphan*/  ic_oerrors; } ;
typedef  int ift_counter ;

/* Variables and functions */
#define  IFCOUNTER_IERRORS 129 
#define  IFCOUNTER_OERRORS 128 
 int /*<<< orphan*/  counter_u64_fetch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_get_counter_default (struct ifnet*,int) ; 

__attribute__((used)) static uint64_t
ieee80211_get_counter(struct ifnet *ifp, ift_counter cnt)
{
	struct ieee80211vap *vap = ifp->if_softc;
	struct ieee80211com *ic = vap->iv_ic;
	uint64_t rv;

	rv = if_get_counter_default(ifp, cnt);
	switch (cnt) {
	case IFCOUNTER_OERRORS:
		rv += counter_u64_fetch(ic->ic_oerrors);
		break;
	case IFCOUNTER_IERRORS:
		rv += counter_u64_fetch(ic->ic_ierrors);
		break;
	default:
		break;
	}

	return (rv);
}