#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct TYPE_10__ {int /*<<< orphan*/  ifru_data; } ;
struct ifreq {int ifr_reqcap; TYPE_1__ ifr_ifru; int /*<<< orphan*/  ifr_mtu; } ;
struct ifnet {int if_flags; int if_drv_flags; int if_capenable; int if_hwassist; int if_capabilities; TYPE_2__* if_softc; } ;
struct ifi2creq {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  driver_mtx; int /*<<< orphan*/  dying; int /*<<< orphan*/  connector; int /*<<< orphan*/  media; } ;
typedef  TYPE_2__ mxge_softc_t ;
typedef  int /*<<< orphan*/  i2c ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int CSUM_TCP ; 
 int CSUM_TCP_IPV6 ; 
 int CSUM_TSO ; 
 int CSUM_UDP ; 
 int CSUM_UDP_IPV6 ; 
 int EINVAL ; 
 int ENXIO ; 
 int IFCAP_LRO ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_RXCSUM_IPV6 ; 
 int IFCAP_TSO4 ; 
 int IFCAP_TSO6 ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_TXCSUM_IPV6 ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int IFCAP_VLAN_HWTSO ; 
 int IFF_DRV_RUNNING ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
 int /*<<< orphan*/  MXGE_SFP ; 
 int /*<<< orphan*/  MXGE_XFP ; 
#define  SIOCADDMULTI 134 
#define  SIOCDELMULTI 133 
#define  SIOCGI2C 132 
#define  SIOCGIFMEDIA 131 
#define  SIOCSIFCAP 130 
#define  SIOCSIFFLAGS 129 
#define  SIOCSIFMTU 128 
 int /*<<< orphan*/  VLAN_CAPABILITIES (struct ifnet*) ; 
 int copyin (int /*<<< orphan*/ ,struct ifi2creq*,int) ; 
 int copyout (struct ifi2creq*,int /*<<< orphan*/ ,int) ; 
 int ether_ioctl (struct ifnet*,int,scalar_t__) ; 
 int ifmedia_ioctl (struct ifnet*,struct ifreq*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ifr_data_get_ptr (struct ifreq*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int mxge_change_mtu (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxge_change_promisc (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mxge_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int mxge_fetch_i2c (TYPE_2__*,struct ifi2creq*) ; 
 int /*<<< orphan*/  mxge_media_probe (TYPE_2__*) ; 
 int mxge_open (TYPE_2__*) ; 
 int /*<<< orphan*/  mxge_set_multicast_list (TYPE_2__*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
mxge_ioctl(struct ifnet *ifp, u_long command, caddr_t data)
{
	mxge_softc_t *sc = ifp->if_softc;
	struct ifreq *ifr = (struct ifreq *)data;
	struct ifi2creq i2c;
	int err, mask;

	err = 0;
	switch (command) {
	case SIOCSIFMTU:
		err = mxge_change_mtu(sc, ifr->ifr_mtu);
		break;

	case SIOCSIFFLAGS:
		mtx_lock(&sc->driver_mtx);
		if (sc->dying) {
			mtx_unlock(&sc->driver_mtx);
			return EINVAL;
		}
		if (ifp->if_flags & IFF_UP) {
			if (!(ifp->if_drv_flags & IFF_DRV_RUNNING)) {
				err = mxge_open(sc);
			} else {
				/* take care of promis can allmulti
				   flag chages */
				mxge_change_promisc(sc,
						    ifp->if_flags & IFF_PROMISC);
				mxge_set_multicast_list(sc);
			}
		} else {
			if (ifp->if_drv_flags & IFF_DRV_RUNNING) {
				mxge_close(sc, 0);
			}
		}
		mtx_unlock(&sc->driver_mtx);
		break;

	case SIOCADDMULTI:
	case SIOCDELMULTI:
		mtx_lock(&sc->driver_mtx);
		if (sc->dying) {
			mtx_unlock(&sc->driver_mtx);
			return (EINVAL);
		}
		mxge_set_multicast_list(sc);
		mtx_unlock(&sc->driver_mtx);
		break;

	case SIOCSIFCAP:
		mtx_lock(&sc->driver_mtx);
		mask = ifr->ifr_reqcap ^ ifp->if_capenable;
		if (mask & IFCAP_TXCSUM) {
			if (IFCAP_TXCSUM & ifp->if_capenable) {
				ifp->if_capenable &= ~(IFCAP_TXCSUM|IFCAP_TSO4);
				ifp->if_hwassist &= ~(CSUM_TCP | CSUM_UDP);
			} else {
				ifp->if_capenable |= IFCAP_TXCSUM;
				ifp->if_hwassist |= (CSUM_TCP | CSUM_UDP);
			}
		} else if (mask & IFCAP_RXCSUM) {
			if (IFCAP_RXCSUM & ifp->if_capenable) {
				ifp->if_capenable &= ~IFCAP_RXCSUM;
			} else {
				ifp->if_capenable |= IFCAP_RXCSUM;
			}
		}
		if (mask & IFCAP_TSO4) {
			if (IFCAP_TSO4 & ifp->if_capenable) {
				ifp->if_capenable &= ~IFCAP_TSO4;
			} else if (IFCAP_TXCSUM & ifp->if_capenable) {
				ifp->if_capenable |= IFCAP_TSO4;
				ifp->if_hwassist |= CSUM_TSO;
			} else {
				printf("mxge requires tx checksum offload"
				       " be enabled to use TSO\n");
				err = EINVAL;
			}
		}
#if IFCAP_TSO6
		if (mask & IFCAP_TXCSUM_IPV6) {
			if (IFCAP_TXCSUM_IPV6 & ifp->if_capenable) {
				ifp->if_capenable &= ~(IFCAP_TXCSUM_IPV6
						       | IFCAP_TSO6);
				ifp->if_hwassist &= ~(CSUM_TCP_IPV6
						      | CSUM_UDP);
			} else {
				ifp->if_capenable |= IFCAP_TXCSUM_IPV6;
				ifp->if_hwassist |= (CSUM_TCP_IPV6
						     | CSUM_UDP_IPV6);
			}
		} else if (mask & IFCAP_RXCSUM_IPV6) {
			if (IFCAP_RXCSUM_IPV6 & ifp->if_capenable) {
				ifp->if_capenable &= ~IFCAP_RXCSUM_IPV6;
			} else {
				ifp->if_capenable |= IFCAP_RXCSUM_IPV6;
			}
		}
		if (mask & IFCAP_TSO6) {
			if (IFCAP_TSO6 & ifp->if_capenable) {
				ifp->if_capenable &= ~IFCAP_TSO6;
			} else if (IFCAP_TXCSUM_IPV6 & ifp->if_capenable) {
				ifp->if_capenable |= IFCAP_TSO6;
				ifp->if_hwassist |= CSUM_TSO;
			} else {
				printf("mxge requires tx checksum offload"
				       " be enabled to use TSO\n");
				err = EINVAL;
			}
		}
#endif /*IFCAP_TSO6 */

		if (mask & IFCAP_LRO)
			ifp->if_capenable ^= IFCAP_LRO;
		if (mask & IFCAP_VLAN_HWTAGGING)
			ifp->if_capenable ^= IFCAP_VLAN_HWTAGGING;
		if (mask & IFCAP_VLAN_HWTSO)
			ifp->if_capenable ^= IFCAP_VLAN_HWTSO;

		if (!(ifp->if_capabilities & IFCAP_VLAN_HWTSO) ||
		    !(ifp->if_capenable & IFCAP_VLAN_HWTAGGING))
			ifp->if_capenable &= ~IFCAP_VLAN_HWTSO;

		mtx_unlock(&sc->driver_mtx);
		VLAN_CAPABILITIES(ifp);

		break;

	case SIOCGIFMEDIA:
		mtx_lock(&sc->driver_mtx);
		if (sc->dying) {
			mtx_unlock(&sc->driver_mtx);
			return (EINVAL);
		}
		mxge_media_probe(sc);
		mtx_unlock(&sc->driver_mtx);
		err = ifmedia_ioctl(ifp, (struct ifreq *)data,
				    &sc->media, command);
		break;

	case SIOCGI2C:
		if (sc->connector != MXGE_XFP &&
		    sc->connector != MXGE_SFP) {
			err = ENXIO;
			break;
		}
		err = copyin(ifr_data_get_ptr(ifr), &i2c, sizeof(i2c));
		if (err != 0)
			break;
		mtx_lock(&sc->driver_mtx);
		if (sc->dying) {
			mtx_unlock(&sc->driver_mtx);
			return (EINVAL);
		}
		err = mxge_fetch_i2c(sc, &i2c);
		mtx_unlock(&sc->driver_mtx);
		if (err == 0)
			err = copyout(&i2c, ifr->ifr_ifru.ifru_data,
			    sizeof(i2c));
		break;
	default:
		err = ether_ioctl(ifp, command, data);
		break;
	}
	return err;
}