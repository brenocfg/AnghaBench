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
typedef  int u_long ;
struct lio {int if_flags; int /*<<< orphan*/  oct_dev; int /*<<< orphan*/  ifmedia; int /*<<< orphan*/  ifstate; } ;
struct ifreq {int ifr_reqcap; int /*<<< orphan*/  ifr_mtu; } ;
struct ifnet {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int CSUM_IP ; 
 int CSUM_TCP ; 
 int CSUM_TCP_IPV6 ; 
 int CSUM_UDP ; 
 int CSUM_UDP_IPV6 ; 
 int IFCAP_LRO ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_RXCSUM_IPV6 ; 
 int IFCAP_TSO4 ; 
 int IFCAP_TSO6 ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_TXCSUM_IPV6 ; 
 int IFCAP_VLAN_HWFILTER ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int IFCAP_VLAN_HWTSO ; 
 int IFF_ALLMULTI ; 
 int IFF_DRV_RUNNING ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
 int LIO_IFSTATE_DETACH ; 
#define  SIOCADDMULTI 136 
#define  SIOCDELMULTI 135 
#define  SIOCGIFMEDIA 134 
#define  SIOCGIFXMEDIA 133 
#define  SIOCSIFADDR 132 
#define  SIOCSIFCAP 131 
#define  SIOCSIFFLAGS 130 
#define  SIOCSIFMEDIA 129 
#define  SIOCSIFMTU 128 
 int /*<<< orphan*/  VLAN_CAPABILITIES (struct ifnet*) ; 
 int atomic_load_acq_int (int /*<<< orphan*/ *) ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int if_getcapenable (struct ifnet*) ; 
 int if_getdrvflags (struct ifnet*) ; 
 int if_getflags (struct ifnet*) ; 
 struct lio* if_getsoftc (struct ifnet*) ; 
 int /*<<< orphan*/  if_setflagbits (struct ifnet*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_sethwassistbits (struct ifnet*,int,int) ; 
 int /*<<< orphan*/  if_togglecapenable (struct ifnet*,int) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 
 int lio_change_dev_flags (struct ifnet*) ; 
 int lio_change_mtu (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  lio_open (struct lio*) ; 
 int lio_set_lro (struct ifnet*) ; 
 int lio_set_mcast_list (struct ifnet*) ; 
 int lio_set_rx_csum (struct ifnet*,int) ; 
 int lio_set_tso4 (struct ifnet*) ; 
 int lio_set_tso6 (struct ifnet*) ; 
 int /*<<< orphan*/  lio_stop (struct ifnet*) ; 

int
lio_ioctl(struct ifnet *ifp, u_long cmd, caddr_t data)
{
	struct lio	*lio = if_getsoftc(ifp);
	struct ifreq	*ifrequest = (struct ifreq *)data;
	int	error = 0;

	switch (cmd) {
	case SIOCSIFADDR:
		lio_dev_dbg(lio->oct_dev, "ioctl: SIOCSIFADDR\n");
		if_setflagbits(ifp, IFF_UP, 0);
		error = ether_ioctl(ifp, cmd, data);
		break;
	case SIOCSIFMTU:
		lio_dev_dbg(lio->oct_dev, "ioctl: SIOCSIFMTU\n");
		error = lio_change_mtu(ifp, ifrequest->ifr_mtu);
		break;
	case SIOCSIFFLAGS:
		lio_dev_dbg(lio->oct_dev, "ioctl: SIOCSIFFLAGS\n");
		if (if_getflags(ifp) & IFF_UP) {
			if (if_getdrvflags(ifp) & IFF_DRV_RUNNING) {
				if ((if_getflags(ifp) ^ lio->if_flags) &
				    (IFF_PROMISC | IFF_ALLMULTI))
					error = lio_change_dev_flags(ifp);
			} else {
				if (!(atomic_load_acq_int(&lio->ifstate) &
				      LIO_IFSTATE_DETACH))
					lio_open(lio);
			}
		} else {
			if (if_getdrvflags(ifp) & IFF_DRV_RUNNING)
				lio_stop(ifp);
		}
		lio->if_flags = if_getflags(ifp);
		break;
	case SIOCADDMULTI:
		lio_dev_dbg(lio->oct_dev, "ioctl: SIOCADDMULTI\n");
		if (if_getdrvflags(ifp) & IFF_DRV_RUNNING)
			error = lio_set_mcast_list(ifp);
		break;
	case SIOCDELMULTI:
		lio_dev_dbg(lio->oct_dev, "ioctl: SIOCSIFMULTI\n");
		break;
	case SIOCSIFMEDIA:
		lio_dev_dbg(lio->oct_dev, "ioctl: SIOCSIFMEDIA\n");
	case SIOCGIFMEDIA:
		lio_dev_dbg(lio->oct_dev, "ioctl: SIOCGIFMEDIA\n");
	case SIOCGIFXMEDIA:
		lio_dev_dbg(lio->oct_dev, "ioctl: SIOCGIFXMEDIA\n");
		error = ifmedia_ioctl(ifp, ifrequest, &lio->ifmedia, cmd);
		break;
	case SIOCSIFCAP:
		{
			int	features = ifrequest->ifr_reqcap ^
					if_getcapenable(ifp);

			lio_dev_dbg(lio->oct_dev, "ioctl: SIOCSIFCAP (Set Capabilities)\n");

			if (!features)
				break;

			if (features & IFCAP_TXCSUM) {
				if_togglecapenable(ifp, IFCAP_TXCSUM);
				if (if_getcapenable(ifp) & IFCAP_TXCSUM)
					if_sethwassistbits(ifp, (CSUM_TCP |
								 CSUM_UDP |
								 CSUM_IP), 0);
				else
					if_sethwassistbits(ifp, 0,
							(CSUM_TCP | CSUM_UDP |
							 CSUM_IP));
			}
			if (features & IFCAP_TXCSUM_IPV6) {
				if_togglecapenable(ifp, IFCAP_TXCSUM_IPV6);
				if (if_getcapenable(ifp) & IFCAP_TXCSUM_IPV6)
					if_sethwassistbits(ifp, (CSUM_UDP_IPV6 |
							   CSUM_TCP_IPV6), 0);
				else
					if_sethwassistbits(ifp, 0,
							   (CSUM_UDP_IPV6 |
							    CSUM_TCP_IPV6));
			}
			if (features & (IFCAP_RXCSUM | IFCAP_RXCSUM_IPV6))
				error |= lio_set_rx_csum(ifp, (features &
							       (IFCAP_RXCSUM |
							 IFCAP_RXCSUM_IPV6)));

			if (features & IFCAP_TSO4)
				error |= lio_set_tso4(ifp);

			if (features & IFCAP_TSO6)
				error |= lio_set_tso6(ifp);

			if (features & IFCAP_LRO)
				error |= lio_set_lro(ifp);

			if (features & IFCAP_VLAN_HWTAGGING)
				if_togglecapenable(ifp, IFCAP_VLAN_HWTAGGING);

			if (features & IFCAP_VLAN_HWFILTER)
				if_togglecapenable(ifp, IFCAP_VLAN_HWFILTER);

			if (features & IFCAP_VLAN_HWTSO)
				if_togglecapenable(ifp, IFCAP_VLAN_HWTSO);

			VLAN_CAPABILITIES(ifp);
			break;
		}
	default:
		lio_dev_dbg(lio->oct_dev, "ioctl: UNKNOWN (0x%X)\n", (int)cmd);
		error = ether_ioctl(ifp, cmd, data);
		break;
	}

	return (error);
}