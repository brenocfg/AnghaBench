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
typedef  int /*<<< orphan*/  uint8_t ;
struct mwl_softc {int /*<<< orphan*/  sc_mh; int /*<<< orphan*/  sc_ec; } ;
struct ether_multistep {int dummy; } ;
struct ether_multi {int /*<<< orphan*/  enm_addrlo; int /*<<< orphan*/  enm_addrhi; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_FIRST_MULTI (struct ether_multistep,int /*<<< orphan*/ *,struct ether_multi*) ; 
 int /*<<< orphan*/  ETHER_NEXT_MULTI (struct ether_multistep,struct ether_multi*) ; 
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_ADDR_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IEEE80211_ADDR_LEN ; 
 int /*<<< orphan*/  IFF_ALLMULTI ; 
 int MWL_HAL_MCAST_MAX ; 
 TYPE_1__* ifp ; 
 int /*<<< orphan*/  mwl_hal_setmcast (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mwl_setmcastfilter(struct mwl_softc *sc)
{
#if 0
	struct ether_multi *enm;
	struct ether_multistep estep;
	uint8_t macs[IEEE80211_ADDR_LEN*MWL_HAL_MCAST_MAX];/* XXX stack use */
	uint8_t *mp;
	int nmc;

	mp = macs;
	nmc = 0;
	ETHER_FIRST_MULTI(estep, &sc->sc_ec, enm);
	while (enm != NULL) {
		/* XXX Punt on ranges. */
		if (nmc == MWL_HAL_MCAST_MAX ||
		    !IEEE80211_ADDR_EQ(enm->enm_addrlo, enm->enm_addrhi)) {
			ifp->if_flags |= IFF_ALLMULTI;
			return;
		}
		IEEE80211_ADDR_COPY(mp, enm->enm_addrlo);
		mp += IEEE80211_ADDR_LEN, nmc++;
		ETHER_NEXT_MULTI(estep, enm);
	}
	ifp->if_flags &= ~IFF_ALLMULTI;
	mwl_hal_setmcast(sc->sc_mh, nmc, macs);
#endif
}