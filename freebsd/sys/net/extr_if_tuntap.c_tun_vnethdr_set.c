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
struct tuntap_softc {int tun_vhdrlen; } ;
struct ifnet {int /*<<< orphan*/  if_capabilities; int /*<<< orphan*/  if_capenable; struct tuntap_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAP_VNET_HDR_CAPS ; 
 int /*<<< orphan*/  TUNDEBUG (struct ifnet*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TUN_LOCK_ASSERT (struct tuntap_softc*) ; 
 int /*<<< orphan*/  tun_caps_changed (struct ifnet*) ; 

__attribute__((used)) static void
tun_vnethdr_set(struct ifnet *ifp, int vhdrlen)
{
	struct tuntap_softc *tp = ifp->if_softc;

	TUN_LOCK_ASSERT(tp);

	if (tp->tun_vhdrlen == vhdrlen)
		return;

	/*
	 * Update if_capabilities to reflect the
	 * functionalities offered by the virtio-net
	 * header.
	 */
	if (vhdrlen != 0)
		ifp->if_capabilities |=
			TAP_VNET_HDR_CAPS;
	else
		ifp->if_capabilities &=
			~TAP_VNET_HDR_CAPS;
	/*
	 * Disable any capabilities that we don't
	 * support anymore.
	 */
	ifp->if_capenable &= ifp->if_capabilities;
	tun_caps_changed(ifp);
	tp->tun_vhdrlen = vhdrlen;

	TUNDEBUG(ifp, "vnet_hdr_len=%d, if_capabilities=%x\n",
	    vhdrlen, ifp->if_capabilities);
}