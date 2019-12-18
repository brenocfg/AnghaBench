#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ sin_port; } ;
struct TYPE_7__ {TYPE_1__ in4; } ;
struct vxlan_softc {char* vxl_mc_ifname; int /*<<< orphan*/  vxl_ifp; TYPE_2__ vxl_dst_addr; TYPE_2__ vxl_src_addr; int /*<<< orphan*/  vxl_vni; } ;

/* Variables and functions */
 int EINVAL ; 
 int VXLAN_SOCKADDR_IS_IPV4 (TYPE_2__*) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ vxlan_check_vni (int /*<<< orphan*/ ) ; 
 scalar_t__ vxlan_sockaddr_in_any (TYPE_2__*) ; 
 scalar_t__ vxlan_sockaddr_in_multicast (TYPE_2__*) ; 
 scalar_t__ vxlan_sockaddr_supported (TYPE_2__*,int) ; 

__attribute__((used)) static int
vxlan_valid_init_config(struct vxlan_softc *sc)
{
	const char *reason;

	if (vxlan_check_vni(sc->vxl_vni) != 0) {
		reason = "invalid virtual network identifier specified";
		goto fail;
	}

	if (vxlan_sockaddr_supported(&sc->vxl_src_addr, 1) == 0) {
		reason = "source address type is not supported";
		goto fail;
	}

	if (vxlan_sockaddr_supported(&sc->vxl_dst_addr, 0) == 0) {
		reason = "destination address type is not supported";
		goto fail;
	}

	if (vxlan_sockaddr_in_any(&sc->vxl_dst_addr) != 0) {
		reason = "no valid destination address specified";
		goto fail;
	}

	if (vxlan_sockaddr_in_multicast(&sc->vxl_dst_addr) == 0 &&
	    sc->vxl_mc_ifname[0] != '\0') {
		reason = "can only specify interface with a group address";
		goto fail;
	}

	if (vxlan_sockaddr_in_any(&sc->vxl_src_addr) == 0) {
		if (VXLAN_SOCKADDR_IS_IPV4(&sc->vxl_src_addr) ^
		    VXLAN_SOCKADDR_IS_IPV4(&sc->vxl_dst_addr)) {
			reason = "source and destination address must both "
			    "be either IPv4 or IPv6";
			goto fail;
		}
	}

	if (sc->vxl_src_addr.in4.sin_port == 0) {
		reason = "local port not specified";
		goto fail;
	}

	if (sc->vxl_dst_addr.in4.sin_port == 0) {
		reason = "remote port not specified";
		goto fail;
	}

	return (0);

fail:
	if_printf(sc->vxl_ifp, "cannot initialize interface: %s\n", reason);
	return (EINVAL);
}