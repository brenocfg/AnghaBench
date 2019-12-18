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
typedef  int uint64_t ;
struct ifreq {int ifr_reqcap; } ;
struct ifnet {int if_capabilities; int (* if_ioctl ) (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int if_capenable; int if_hwassist; } ;
struct hn_softc {struct ifnet* hn_vf_ifp; struct ifnet* hn_ifp; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int CSUM_IP6_TSO ; 
 int CSUM_IP_TSO ; 
 int HN_CSUM_IP6_HWASSIST (struct hn_softc*) ; 
 int HN_CSUM_IP_HWASSIST (struct hn_softc*) ; 
 int /*<<< orphan*/  HN_LOCK_ASSERT (struct hn_softc*) ; 
 int IFCAP_TSO4 ; 
 int IFCAP_TSO6 ; 
 int IFCAP_TXCSUM ; 
 int IFCAP_TXCSUM_IPV6 ; 
 int /*<<< orphan*/  SIOCSIFCAP ; 
 int stub1 (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hn_xpnt_vf_iocsetcaps(struct hn_softc *sc, struct ifreq *ifr)
{
	struct ifnet *ifp, *vf_ifp;
	uint64_t tmp;
	int error;

	HN_LOCK_ASSERT(sc);
	ifp = sc->hn_ifp;
	vf_ifp = sc->hn_vf_ifp;

	/*
	 * Fix up requested capabilities w/ supported capabilities,
	 * since the supported capabilities could have been changed.
	 */
	ifr->ifr_reqcap &= ifp->if_capabilities;
	/* Pass SIOCSIFCAP to VF. */
	error = vf_ifp->if_ioctl(vf_ifp, SIOCSIFCAP, (caddr_t)ifr);

	/*
	 * NOTE:
	 * The error will be propagated to the callers, however, it
	 * is _not_ useful here.
	 */

	/*
	 * Merge VF's enabled capabilities.
	 */
	ifp->if_capenable = vf_ifp->if_capenable & ifp->if_capabilities;

	tmp = vf_ifp->if_hwassist & HN_CSUM_IP_HWASSIST(sc);
	if (ifp->if_capenable & IFCAP_TXCSUM)
		ifp->if_hwassist |= tmp;
	else
		ifp->if_hwassist &= ~tmp;

	tmp = vf_ifp->if_hwassist & HN_CSUM_IP6_HWASSIST(sc);
	if (ifp->if_capenable & IFCAP_TXCSUM_IPV6)
		ifp->if_hwassist |= tmp;
	else
		ifp->if_hwassist &= ~tmp;

	tmp = vf_ifp->if_hwassist & CSUM_IP_TSO;
	if (ifp->if_capenable & IFCAP_TSO4)
		ifp->if_hwassist |= tmp;
	else
		ifp->if_hwassist &= ~tmp;

	tmp = vf_ifp->if_hwassist & CSUM_IP6_TSO;
	if (ifp->if_capenable & IFCAP_TSO6)
		ifp->if_hwassist |= tmp;
	else
		ifp->if_hwassist &= ~tmp;

	return (error);
}