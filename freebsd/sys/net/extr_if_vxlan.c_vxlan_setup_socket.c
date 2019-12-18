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
typedef  union vxlan_sockaddr {int dummy; } vxlan_sockaddr ;
struct vxlan_softc {int vxl_vso_mc_index; int vxl_vni; struct vxlan_socket* vxl_sock; int /*<<< orphan*/  vxl_mc_ifindex; union vxlan_sockaddr vxl_dst_addr; union vxlan_sockaddr vxl_src_addr; struct ifnet* vxl_ifp; } ;
struct vxlan_socket {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*,int) ; 
 int /*<<< orphan*/  vxlan_free_multicast (struct vxlan_softc*) ; 
 int vxlan_setup_multicast (struct vxlan_softc*) ; 
 int vxlan_sockaddr_in_multicast (union vxlan_sockaddr*) ; 
 int vxlan_socket_create (struct ifnet*,int,union vxlan_sockaddr*,struct vxlan_socket**) ; 
 int vxlan_socket_insert_softc (struct vxlan_socket*,struct vxlan_softc*) ; 
 struct vxlan_socket* vxlan_socket_lookup (union vxlan_sockaddr*) ; 
 int vxlan_socket_mc_add_group (struct vxlan_socket*,union vxlan_sockaddr*,union vxlan_sockaddr*,int /*<<< orphan*/ ,int*) ; 
 struct vxlan_socket* vxlan_socket_mc_lookup (union vxlan_sockaddr*) ; 
 int /*<<< orphan*/  vxlan_socket_mc_release_group_by_idx (struct vxlan_socket*,int) ; 
 int /*<<< orphan*/  vxlan_socket_release (struct vxlan_socket*) ; 

__attribute__((used)) static int
vxlan_setup_socket(struct vxlan_softc *sc)
{
	struct vxlan_socket *vso;
	struct ifnet *ifp;
	union vxlan_sockaddr *saddr, *daddr;
	int multicast, error;

	vso = NULL;
	ifp = sc->vxl_ifp;
	saddr = &sc->vxl_src_addr;
	daddr = &sc->vxl_dst_addr;

	multicast = vxlan_sockaddr_in_multicast(daddr);
	MPASS(multicast != -1);
	sc->vxl_vso_mc_index = -1;

	/*
	 * Try to create the socket. If that fails, attempt to use an
	 * existing socket.
	 */
	error = vxlan_socket_create(ifp, multicast, saddr, &vso);
	if (error) {
		if (multicast != 0)
			vso = vxlan_socket_mc_lookup(saddr);
		else
			vso = vxlan_socket_lookup(saddr);

		if (vso == NULL) {
			if_printf(ifp, "cannot create socket (error: %d), "
			    "and no existing socket found\n", error);
			goto out;
		}
	}

	if (multicast != 0) {
		error = vxlan_setup_multicast(sc);
		if (error)
			goto out;

		error = vxlan_socket_mc_add_group(vso, daddr, saddr,
		    sc->vxl_mc_ifindex, &sc->vxl_vso_mc_index);
		if (error)
			goto out;
	}

	sc->vxl_sock = vso;
	error = vxlan_socket_insert_softc(vso, sc);
	if (error) {
		sc->vxl_sock = NULL;
		if_printf(ifp, "network identifier %d already exists in "
		    "this socket\n", sc->vxl_vni);
		goto out;
	}

	return (0);

out:
	if (vso != NULL) {
		if (sc->vxl_vso_mc_index != -1) {
			vxlan_socket_mc_release_group_by_idx(vso,
			    sc->vxl_vso_mc_index);
			sc->vxl_vso_mc_index = -1;
		}
		if (multicast != 0)
			vxlan_free_multicast(sc);
		vxlan_socket_release(vso);
	}

	return (error);
}