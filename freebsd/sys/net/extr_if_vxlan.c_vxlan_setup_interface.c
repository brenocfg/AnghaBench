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
struct vxlanudphdr {int dummy; } ;
struct vxlan_softc {int /*<<< orphan*/  vxl_dst_addr; struct ifnet* vxl_ifp; } ;
struct ip6_hdr {int dummy; } ;
struct ip {int dummy; } ;
struct ifnet {scalar_t__ if_hdrlen; } ;

/* Variables and functions */
 scalar_t__ ETHER_HDR_LEN ; 
 scalar_t__ VXLAN_SOCKADDR_IS_IPV4 (int /*<<< orphan*/ *) ; 
 scalar_t__ VXLAN_SOCKADDR_IS_IPV6 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vxlan_setup_interface(struct vxlan_softc *sc)
{
	struct ifnet *ifp;

	ifp = sc->vxl_ifp;
	ifp->if_hdrlen = ETHER_HDR_LEN + sizeof(struct vxlanudphdr);

	if (VXLAN_SOCKADDR_IS_IPV4(&sc->vxl_dst_addr) != 0)
		ifp->if_hdrlen += sizeof(struct ip);
	else if (VXLAN_SOCKADDR_IS_IPV6(&sc->vxl_dst_addr) != 0)
		ifp->if_hdrlen += sizeof(struct ip6_hdr);
}