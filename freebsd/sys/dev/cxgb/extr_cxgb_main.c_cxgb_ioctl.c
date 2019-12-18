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
typedef  int uint32_t ;
struct port_info {int if_flags; int /*<<< orphan*/  media; struct adapter* adapter; } ;
struct ifreq {int ifr_mtu; int ifr_reqcap; } ;
struct ifnet {int if_mtu; int if_flags; int if_drv_flags; int if_capenable; int if_hwassist; struct port_info* if_softc; } ;
struct adapter {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADAPTER_LOCK (struct adapter*) ; 
 int /*<<< orphan*/  ADAPTER_LOCK_ASSERT_NOTOWNED (struct adapter*) ; 
 int /*<<< orphan*/  ADAPTER_UNLOCK (struct adapter*) ; 
 int CSUM_IP ; 
 int CSUM_TCP ; 
 int CSUM_TCP_IPV6 ; 
 int CSUM_UDP ; 
 int CSUM_UDP_IPV6 ; 
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENXIO ; 
 int ETHERMIN ; 
 int ETHERMTU_JUMBO ; 
 int IFCAP_LRO ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_RXCSUM_IPV6 ; 
 int IFCAP_TOE4 ; 
 int IFCAP_TSO4 ; 
 int IFCAP_TSO6 ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_TXCSUM_IPV6 ; 
 int IFCAP_VLAN_HWCSUM ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int IFCAP_VLAN_HWTSO ; 
 int IFCAP_VLAN_MTU ; 
 int IFF_ALLMULTI ; 
 int IFF_DRV_RUNNING ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
 int /*<<< orphan*/  IS_BUSY (struct adapter*) ; 
 int /*<<< orphan*/  IS_DOOMED (struct port_info*) ; 
 int /*<<< orphan*/  PORT_LOCK (struct port_info*) ; 
 int /*<<< orphan*/  PORT_UNLOCK (struct port_info*) ; 
#define  SIOCADDMULTI 134 
#define  SIOCDELMULTI 133 
#define  SIOCGIFMEDIA 132 
#define  SIOCSIFCAP 131 
#define  SIOCSIFFLAGS 130 
#define  SIOCSIFMEDIA 129 
#define  SIOCSIFMTU 128 
 int /*<<< orphan*/  VLAN_CAPABILITIES (struct ifnet*) ; 
 int cxgb_init_locked (struct port_info*) ; 
 int /*<<< orphan*/  cxgb_set_lro (struct port_info*,int) ; 
 int cxgb_uninit_locked (struct port_info*) ; 
 int /*<<< orphan*/  cxgb_update_mac_settings (struct port_info*) ; 
 int ether_ioctl (struct ifnet*,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,unsigned long) ; 
 int toe_capability (struct port_info*,int) ; 

__attribute__((used)) static int
cxgb_ioctl(struct ifnet *ifp, unsigned long command, caddr_t data)
{
	struct port_info *p = ifp->if_softc;
	struct adapter *sc = p->adapter;
	struct ifreq *ifr = (struct ifreq *)data;
	int flags, error = 0, mtu;
	uint32_t mask;

	switch (command) {
	case SIOCSIFMTU:
		ADAPTER_LOCK(sc);
		error = IS_DOOMED(p) ? ENXIO : (IS_BUSY(sc) ? EBUSY : 0);
		if (error) {
fail:
			ADAPTER_UNLOCK(sc);
			return (error);
		}

		mtu = ifr->ifr_mtu;
		if ((mtu < ETHERMIN) || (mtu > ETHERMTU_JUMBO)) {
			error = EINVAL;
		} else {
			ifp->if_mtu = mtu;
			PORT_LOCK(p);
			cxgb_update_mac_settings(p);
			PORT_UNLOCK(p);
		}
		ADAPTER_UNLOCK(sc);
		break;
	case SIOCSIFFLAGS:
		ADAPTER_LOCK(sc);
		if (IS_DOOMED(p)) {
			error = ENXIO;
			goto fail;
		}
		if (ifp->if_flags & IFF_UP) {
			if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
				flags = p->if_flags;
				if (((ifp->if_flags ^ flags) & IFF_PROMISC) ||
				    ((ifp->if_flags ^ flags) & IFF_ALLMULTI)) {
					if (IS_BUSY(sc)) {
						error = EBUSY;
						goto fail;
					}
					PORT_LOCK(p);
					cxgb_update_mac_settings(p);
					PORT_UNLOCK(p);
				}
				ADAPTER_UNLOCK(sc);
			} else
				error = cxgb_init_locked(p);
			p->if_flags = ifp->if_flags;
		} else if (ifp->if_drv_flags & IFF_DRV_RUNNING)
			error = cxgb_uninit_locked(p);
		else
			ADAPTER_UNLOCK(sc);

		ADAPTER_LOCK_ASSERT_NOTOWNED(sc);
		break;
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		ADAPTER_LOCK(sc);
		error = IS_DOOMED(p) ? ENXIO : (IS_BUSY(sc) ? EBUSY : 0);
		if (error)
			goto fail;

		if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
			PORT_LOCK(p);
			cxgb_update_mac_settings(p);
			PORT_UNLOCK(p);
		}
		ADAPTER_UNLOCK(sc);

		break;
	case SIOCSIFCAP:
		ADAPTER_LOCK(sc);
		error = IS_DOOMED(p) ? ENXIO : (IS_BUSY(sc) ? EBUSY : 0);
		if (error)
			goto fail;

		mask = ifr->ifr_reqcap ^ ifp->if_capenable;
		if (mask & IFCAP_TXCSUM) {
			ifp->if_capenable ^= IFCAP_TXCSUM;
			ifp->if_hwassist ^= (CSUM_TCP | CSUM_UDP | CSUM_IP);

			if (IFCAP_TSO4 & ifp->if_capenable &&
			    !(IFCAP_TXCSUM & ifp->if_capenable)) {
				ifp->if_capenable &= ~IFCAP_TSO4;
				if_printf(ifp,
				    "tso4 disabled due to -txcsum.\n");
			}
		}
		if (mask & IFCAP_TXCSUM_IPV6) {
			ifp->if_capenable ^= IFCAP_TXCSUM_IPV6;
			ifp->if_hwassist ^= (CSUM_UDP_IPV6 | CSUM_TCP_IPV6);

			if (IFCAP_TSO6 & ifp->if_capenable &&
			    !(IFCAP_TXCSUM_IPV6 & ifp->if_capenable)) {
				ifp->if_capenable &= ~IFCAP_TSO6;
				if_printf(ifp,
				    "tso6 disabled due to -txcsum6.\n");
			}
		}
		if (mask & IFCAP_RXCSUM)
			ifp->if_capenable ^= IFCAP_RXCSUM;
		if (mask & IFCAP_RXCSUM_IPV6)
			ifp->if_capenable ^= IFCAP_RXCSUM_IPV6;

		/*
		 * Note that we leave CSUM_TSO alone (it is always set).  The
		 * kernel takes both IFCAP_TSOx and CSUM_TSO into account before
		 * sending a TSO request our way, so it's sufficient to toggle
		 * IFCAP_TSOx only.
		 */
		if (mask & IFCAP_TSO4) {
			if (!(IFCAP_TSO4 & ifp->if_capenable) &&
			    !(IFCAP_TXCSUM & ifp->if_capenable)) {
				if_printf(ifp, "enable txcsum first.\n");
				error = EAGAIN;
				goto fail;
			}
			ifp->if_capenable ^= IFCAP_TSO4;
		}
		if (mask & IFCAP_TSO6) {
			if (!(IFCAP_TSO6 & ifp->if_capenable) &&
			    !(IFCAP_TXCSUM_IPV6 & ifp->if_capenable)) {
				if_printf(ifp, "enable txcsum6 first.\n");
				error = EAGAIN;
				goto fail;
			}
			ifp->if_capenable ^= IFCAP_TSO6;
		}
		if (mask & IFCAP_LRO) {
			ifp->if_capenable ^= IFCAP_LRO;

			/* Safe to do this even if cxgb_up not called yet */
			cxgb_set_lro(p, ifp->if_capenable & IFCAP_LRO);
		}
#ifdef TCP_OFFLOAD
		if (mask & IFCAP_TOE4) {
			int enable = (ifp->if_capenable ^ mask) & IFCAP_TOE4;

			error = toe_capability(p, enable);
			if (error == 0)
				ifp->if_capenable ^= mask;
		}
#endif
		if (mask & IFCAP_VLAN_HWTAGGING) {
			ifp->if_capenable ^= IFCAP_VLAN_HWTAGGING;
			if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
				PORT_LOCK(p);
				cxgb_update_mac_settings(p);
				PORT_UNLOCK(p);
			}
		}
		if (mask & IFCAP_VLAN_MTU) {
			ifp->if_capenable ^= IFCAP_VLAN_MTU;
			if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
				PORT_LOCK(p);
				cxgb_update_mac_settings(p);
				PORT_UNLOCK(p);
			}
		}
		if (mask & IFCAP_VLAN_HWTSO)
			ifp->if_capenable ^= IFCAP_VLAN_HWTSO;
		if (mask & IFCAP_VLAN_HWCSUM)
			ifp->if_capenable ^= IFCAP_VLAN_HWCSUM;

#ifdef VLAN_CAPABILITIES
		VLAN_CAPABILITIES(ifp);
#endif
		ADAPTER_UNLOCK(sc);
		break;
	case SIOCSIFMEDIA:
	case SIOCGIFMEDIA:
		error = ifmedia_ioctl(ifp, ifr, &p->media, command);
		break;
	default:
		error = ether_ioctl(ifp, command, data);
	}

	return (error);
}