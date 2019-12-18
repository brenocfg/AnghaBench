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
struct mii_data {int /*<<< orphan*/  mii_media; } ;
struct ifreq {int ifr_reqcap; } ;
struct cgem_softc {int if_old_flags; int /*<<< orphan*/  miibus; } ;
typedef  int /*<<< orphan*/  if_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CGEM_CKSUM_ASSIST ; 
 int /*<<< orphan*/  CGEM_DMA_CFG ; 
 int CGEM_DMA_CFG_CHKSUM_GEN_OFFLOAD_EN ; 
 int /*<<< orphan*/  CGEM_LOCK (struct cgem_softc*) ; 
 int /*<<< orphan*/  CGEM_NET_CFG ; 
 int CGEM_NET_CFG_RX_CHKSUM_OFFLD_EN ; 
 int /*<<< orphan*/  CGEM_UNLOCK (struct cgem_softc*) ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_RXCSUM_IPV6 ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_TXCSUM_IPV6 ; 
 int IFCAP_VLAN_HWCSUM ; 
 int IFF_ALLMULTI ; 
 int IFF_DRV_RUNNING ; 
 int IFF_PROMISC ; 
 int IFF_UP ; 
 int RD4 (struct cgem_softc*,int /*<<< orphan*/ ) ; 
#define  SIOCADDMULTI 133 
#define  SIOCDELMULTI 132 
#define  SIOCGIFMEDIA 131 
#define  SIOCSIFCAP 130 
#define  SIOCSIFFLAGS 129 
#define  SIOCSIFMEDIA 128 
 int /*<<< orphan*/  WR4 (struct cgem_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cgem_init_locked (struct cgem_softc*) ; 
 int /*<<< orphan*/  cgem_rx_filter (struct cgem_softc*) ; 
 int /*<<< orphan*/  cgem_stop (struct cgem_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int ether_ioctl (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 int if_getflags (int /*<<< orphan*/ ) ; 
 struct cgem_softc* if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setcapenablebit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_sethwassistbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ifmedia_ioctl (int /*<<< orphan*/ ,struct ifreq*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
cgem_ioctl(if_t ifp, u_long cmd, caddr_t data)
{
	struct cgem_softc *sc = if_getsoftc(ifp);
	struct ifreq *ifr = (struct ifreq *)data;
	struct mii_data *mii;
	int error = 0, mask;

	switch (cmd) {
	case SIOCSIFFLAGS:
		CGEM_LOCK(sc);
		if ((if_getflags(ifp) & IFF_UP) != 0) {
			if ((if_getdrvflags(ifp) & IFF_DRV_RUNNING) != 0) {
				if (((if_getflags(ifp) ^ sc->if_old_flags) &
				     (IFF_PROMISC | IFF_ALLMULTI)) != 0) {
					cgem_rx_filter(sc);
				}
			} else {
				cgem_init_locked(sc);
			}
		} else if ((if_getdrvflags(ifp) & IFF_DRV_RUNNING) != 0) {
			if_setdrvflagbits(ifp, 0, IFF_DRV_RUNNING);
			cgem_stop(sc);
		}
		sc->if_old_flags = if_getflags(ifp);
		CGEM_UNLOCK(sc);
		break;

	case SIOCADDMULTI:
	case SIOCDELMULTI:
		/* Set up multi-cast filters. */
		if ((if_getdrvflags(ifp) & IFF_DRV_RUNNING) != 0) {
			CGEM_LOCK(sc);
			cgem_rx_filter(sc);
			CGEM_UNLOCK(sc);
		}
		break;

	case SIOCSIFMEDIA:
	case SIOCGIFMEDIA:
		mii = device_get_softc(sc->miibus);
		error = ifmedia_ioctl(ifp, ifr, &mii->mii_media, cmd);
		break;

	case SIOCSIFCAP:
		CGEM_LOCK(sc);
		mask = if_getcapenable(ifp) ^ ifr->ifr_reqcap;

		if ((mask & IFCAP_TXCSUM) != 0) {
			if ((ifr->ifr_reqcap & IFCAP_TXCSUM) != 0) {
				/* Turn on TX checksumming. */
				if_setcapenablebit(ifp, IFCAP_TXCSUM |
						   IFCAP_TXCSUM_IPV6, 0);
				if_sethwassistbits(ifp, CGEM_CKSUM_ASSIST, 0);

				WR4(sc, CGEM_DMA_CFG,
				    RD4(sc, CGEM_DMA_CFG) |
				     CGEM_DMA_CFG_CHKSUM_GEN_OFFLOAD_EN);
			} else {
				/* Turn off TX checksumming. */
				if_setcapenablebit(ifp, 0, IFCAP_TXCSUM |
						   IFCAP_TXCSUM_IPV6);
				if_sethwassistbits(ifp, 0, CGEM_CKSUM_ASSIST);

				WR4(sc, CGEM_DMA_CFG,
				    RD4(sc, CGEM_DMA_CFG) &
				     ~CGEM_DMA_CFG_CHKSUM_GEN_OFFLOAD_EN);
			}
		}
		if ((mask & IFCAP_RXCSUM) != 0) {
			if ((ifr->ifr_reqcap & IFCAP_RXCSUM) != 0) {
				/* Turn on RX checksumming. */
				if_setcapenablebit(ifp, IFCAP_RXCSUM |
						   IFCAP_RXCSUM_IPV6, 0);
				WR4(sc, CGEM_NET_CFG,
				    RD4(sc, CGEM_NET_CFG) |
				     CGEM_NET_CFG_RX_CHKSUM_OFFLD_EN);
			} else {
				/* Turn off RX checksumming. */
				if_setcapenablebit(ifp, 0, IFCAP_RXCSUM |
						   IFCAP_RXCSUM_IPV6);
				WR4(sc, CGEM_NET_CFG,
				    RD4(sc, CGEM_NET_CFG) &
				     ~CGEM_NET_CFG_RX_CHKSUM_OFFLD_EN);
			}
		}
		if ((if_getcapenable(ifp) & (IFCAP_RXCSUM | IFCAP_TXCSUM)) == 
		    (IFCAP_RXCSUM | IFCAP_TXCSUM))
			if_setcapenablebit(ifp, IFCAP_VLAN_HWCSUM, 0);
		else
			if_setcapenablebit(ifp, 0, IFCAP_VLAN_HWCSUM);

		CGEM_UNLOCK(sc);
		break;
	default:
		error = ether_ioctl(ifp, cmd, data);
		break;
	}

	return (error);
}