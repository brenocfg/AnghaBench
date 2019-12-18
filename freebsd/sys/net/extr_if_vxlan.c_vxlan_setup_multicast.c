#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union vxlan_sockaddr {int dummy; } vxlan_sockaddr ;
struct vxlan_softc {char* vxl_mc_ifname; int /*<<< orphan*/  vxl_ttl; TYPE_2__* vxl_im6o; int /*<<< orphan*/  vxl_mc_ifp; TYPE_1__* vxl_im4o; union vxlan_sockaddr vxl_dst_addr; } ;
struct ip_moptions {int dummy; } ;
struct ip6_moptions {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  im6o_multicast_hlim; int /*<<< orphan*/  im6o_multicast_ifp; } ;
struct TYPE_3__ {int imo_multicast_vif; int /*<<< orphan*/  imo_multicast_ttl; int /*<<< orphan*/  imo_multicast_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_VXLAN ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ VXLAN_SOCKADDR_IS_IPV4 (union vxlan_sockaddr const*) ; 
 scalar_t__ VXLAN_SOCKADDR_IS_IPV6 (union vxlan_sockaddr const*) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int vxlan_setup_multicast_interface (struct vxlan_softc*) ; 

__attribute__((used)) static int
vxlan_setup_multicast(struct vxlan_softc *sc)
{
	const union vxlan_sockaddr *group;
	int error;

	group = &sc->vxl_dst_addr;
	error = 0;

	if (sc->vxl_mc_ifname[0] != '\0') {
		error = vxlan_setup_multicast_interface(sc);
		if (error)
			return (error);
	}

	/*
	 * Initialize an multicast options structure that is sufficiently
	 * populated for use in the respective IP output routine. This
	 * structure is typically stored in the socket, but our sockets
	 * may be shared among multiple interfaces.
	 */
	if (VXLAN_SOCKADDR_IS_IPV4(group)) {
		sc->vxl_im4o = malloc(sizeof(struct ip_moptions), M_VXLAN,
		    M_ZERO | M_WAITOK);
		sc->vxl_im4o->imo_multicast_ifp = sc->vxl_mc_ifp;
		sc->vxl_im4o->imo_multicast_ttl = sc->vxl_ttl;
		sc->vxl_im4o->imo_multicast_vif = -1;
	} else if (VXLAN_SOCKADDR_IS_IPV6(group)) {
		sc->vxl_im6o = malloc(sizeof(struct ip6_moptions), M_VXLAN,
		    M_ZERO | M_WAITOK);
		sc->vxl_im6o->im6o_multicast_ifp = sc->vxl_mc_ifp;
		sc->vxl_im6o->im6o_multicast_hlim = sc->vxl_ttl;
	}

	return (error);
}