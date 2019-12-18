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
struct muge_softc {int sc_rfe_ctl; int /*<<< orphan*/  sc_ue; } ;
struct ifnet {int if_capabilities; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ETH_RFE_CTL ; 
 int ETH_RFE_CTL_ICMP_COE_ ; 
 int ETH_RFE_CTL_IGMP_COE_ ; 
 int ETH_RFE_CTL_IP_COE_ ; 
 int ETH_RFE_CTL_TCPUDP_COE_ ; 
 int ETH_RFE_CTL_VLAN_FILTER_ ; 
 int IFCAP_RXCSUM ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MUGE_LOCK_ASSERT (struct muge_softc*,int /*<<< orphan*/ ) ; 
 int lan78xx_write_reg (struct muge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  muge_warn_printf (struct muge_softc*,char*,int) ; 
 struct ifnet* uether_getifp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int muge_sethwcsum(struct muge_softc *sc)
{
	struct ifnet *ifp = uether_getifp(&sc->sc_ue);
	int err;

	if (!ifp)
		return (-EIO);

	MUGE_LOCK_ASSERT(sc, MA_OWNED);

	if (ifp->if_capabilities & IFCAP_RXCSUM) {
		sc->sc_rfe_ctl |= ETH_RFE_CTL_IGMP_COE_ | ETH_RFE_CTL_ICMP_COE_;
		sc->sc_rfe_ctl |= ETH_RFE_CTL_TCPUDP_COE_ | ETH_RFE_CTL_IP_COE_;
	} else {
		sc->sc_rfe_ctl &=
		    ~(ETH_RFE_CTL_IGMP_COE_ | ETH_RFE_CTL_ICMP_COE_);
		sc->sc_rfe_ctl &=
		     ~(ETH_RFE_CTL_TCPUDP_COE_ | ETH_RFE_CTL_IP_COE_);
	}

	sc->sc_rfe_ctl &= ~ETH_RFE_CTL_VLAN_FILTER_;

	err = lan78xx_write_reg(sc, ETH_RFE_CTL, sc->sc_rfe_ctl);

	if (err != 0) {
		muge_warn_printf(sc, "failed to write ETH_RFE_CTL (err=%d)\n",
		    err);
		return (err);
	}

	return (0);
}