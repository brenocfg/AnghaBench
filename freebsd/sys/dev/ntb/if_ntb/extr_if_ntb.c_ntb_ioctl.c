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
struct ntb_net_ctx {int /*<<< orphan*/  media; scalar_t__ mtu; } ;
struct ifreq {int ifr_reqcap; scalar_t__ ifr_mtu; } ;
typedef  int /*<<< orphan*/  if_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ETHER_HDR_LEN ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_RXCSUM_IPV6 ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_TXCSUM_IPV6 ; 
 int /*<<< orphan*/  NTB_CSUM_FEATURES ; 
 int /*<<< orphan*/  NTB_CSUM_FEATURES6 ; 
#define  SIOCADDMULTI 134 
#define  SIOCDELMULTI 133 
#define  SIOCGIFMEDIA 132 
#define  SIOCSIFCAP 131 
#define  SIOCSIFFLAGS 130 
#define  SIOCSIFMEDIA 129 
#define  SIOCSIFMTU 128 
 int ether_ioctl (int /*<<< orphan*/ ,int,scalar_t__) ; 
 struct ntb_net_ctx* if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setcapenablebit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  if_sethwassistbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setmtu (int /*<<< orphan*/ ,scalar_t__) ; 
 int ifmedia_ioctl (int /*<<< orphan*/ ,struct ifreq*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ntb_ioctl(if_t ifp, u_long command, caddr_t data)
{
	struct ntb_net_ctx *sc = if_getsoftc(ifp);
	struct ifreq *ifr = (struct ifreq *)data;
	int error = 0;

	switch (command) {
	case SIOCSIFFLAGS:
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		break;

	case SIOCSIFMTU:
	    {
		if (ifr->ifr_mtu > sc->mtu - ETHER_HDR_LEN) {
			error = EINVAL;
			break;
		}

		if_setmtu(ifp, ifr->ifr_mtu);
		break;
	    }

	case SIOCSIFMEDIA:
	case SIOCGIFMEDIA:
		error = ifmedia_ioctl(ifp, ifr, &sc->media, command);
		break;

	case SIOCSIFCAP:
		if (ifr->ifr_reqcap & IFCAP_RXCSUM)
			if_setcapenablebit(ifp, IFCAP_RXCSUM, 0);
		else
			if_setcapenablebit(ifp, 0, IFCAP_RXCSUM);
		if (ifr->ifr_reqcap & IFCAP_TXCSUM) {
			if_setcapenablebit(ifp, IFCAP_TXCSUM, 0);
			if_sethwassistbits(ifp, NTB_CSUM_FEATURES, 0);
		} else {
			if_setcapenablebit(ifp, 0, IFCAP_TXCSUM);
			if_sethwassistbits(ifp, 0, NTB_CSUM_FEATURES);
		}
		if (ifr->ifr_reqcap & IFCAP_RXCSUM_IPV6)
			if_setcapenablebit(ifp, IFCAP_RXCSUM_IPV6, 0);
		else
			if_setcapenablebit(ifp, 0, IFCAP_RXCSUM_IPV6);
		if (ifr->ifr_reqcap & IFCAP_TXCSUM_IPV6) {
			if_setcapenablebit(ifp, IFCAP_TXCSUM_IPV6, 0);
			if_sethwassistbits(ifp, NTB_CSUM_FEATURES6, 0);
		} else {
			if_setcapenablebit(ifp, 0, IFCAP_TXCSUM_IPV6);
			if_sethwassistbits(ifp, 0, NTB_CSUM_FEATURES6);
		}
		break;

	default:
		error = ether_ioctl(ifp, command, data);
		break;
	}

	return (error);
}