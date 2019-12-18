#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int sin_len; void* sin_port; int /*<<< orphan*/  sin_addr; void* sin_family; } ;
struct TYPE_12__ {int sin6_len; int /*<<< orphan*/  sin6_addr; void* sin6_family; } ;
struct TYPE_17__ {TYPE_7__ in4; TYPE_3__ in6; } ;
struct TYPE_14__ {int sin_len; void* sin_port; int /*<<< orphan*/  sin_addr; void* sin_family; } ;
struct TYPE_10__ {int sin6_len; int /*<<< orphan*/  sin6_addr; void* sin6_family; } ;
struct TYPE_15__ {TYPE_5__ in4; TYPE_1__ in6; } ;
struct vxlan_softc {scalar_t__ vxl_min_port; scalar_t__ vxl_max_port; int /*<<< orphan*/  vxl_flags; int /*<<< orphan*/  vxl_ttl; int /*<<< orphan*/  vxl_ftable_max; int /*<<< orphan*/  vxl_ftable_timeout; int /*<<< orphan*/  vxl_mc_ifname; TYPE_8__ vxl_dst_addr; TYPE_6__ vxl_src_addr; int /*<<< orphan*/  vxl_vni; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_11__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_18__ {TYPE_4__ in6; TYPE_2__ in4; } ;
struct ifvxlanparam {int vxlp_with; scalar_t__ vxlp_min_port; scalar_t__ vxlp_max_port; scalar_t__ vxlp_learn; int /*<<< orphan*/  vxlp_ttl; int /*<<< orphan*/  vxlp_ftable_max; int /*<<< orphan*/  vxlp_ftable_timeout; int /*<<< orphan*/  vxlp_mc_ifname; int /*<<< orphan*/  vxlp_remote_port; int /*<<< orphan*/  vxlp_local_port; TYPE_9__ vxlp_remote_sa; TYPE_9__ vxlp_local_sa; int /*<<< orphan*/  vxlp_vni; } ;

/* Variables and functions */
 void* AF_INET ; 
 void* AF_INET6 ; 
 int EAFNOSUPPORT ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  VXLAN_FLAG_LEARN ; 
 int VXLAN_PARAM_WITH_FTABLE_MAX ; 
 int VXLAN_PARAM_WITH_FTABLE_TIMEOUT ; 
 int VXLAN_PARAM_WITH_LEARN ; 
 int VXLAN_PARAM_WITH_LOCAL_ADDR4 ; 
 int VXLAN_PARAM_WITH_LOCAL_ADDR6 ; 
 int VXLAN_PARAM_WITH_LOCAL_PORT ; 
 int VXLAN_PARAM_WITH_MULTICAST_IF ; 
 int VXLAN_PARAM_WITH_PORT_RANGE ; 
 int VXLAN_PARAM_WITH_REMOTE_ADDR4 ; 
 int VXLAN_PARAM_WITH_REMOTE_ADDR6 ; 
 int VXLAN_PARAM_WITH_REMOTE_PORT ; 
 int VXLAN_PARAM_WITH_TTL ; 
 int VXLAN_PARAM_WITH_VNI ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vxlan_check_ftable_max (int /*<<< orphan*/ ) ; 
 scalar_t__ vxlan_check_ftable_timeout (int /*<<< orphan*/ ) ; 
 scalar_t__ vxlan_check_ttl (int /*<<< orphan*/ ) ; 
 scalar_t__ vxlan_check_vni (int /*<<< orphan*/ ) ; 
 int vxlan_sockaddr_in6_embedscope (TYPE_9__*) ; 

__attribute__((used)) static int
vxlan_set_user_config(struct vxlan_softc *sc, struct ifvxlanparam *vxlp)
{

#ifndef INET
	if (vxlp->vxlp_with & (VXLAN_PARAM_WITH_LOCAL_ADDR4 |
	    VXLAN_PARAM_WITH_REMOTE_ADDR4))
		return (EAFNOSUPPORT);
#endif

#ifndef INET6
	if (vxlp->vxlp_with & (VXLAN_PARAM_WITH_LOCAL_ADDR6 |
	    VXLAN_PARAM_WITH_REMOTE_ADDR6))
		return (EAFNOSUPPORT);
#else
	if (vxlp->vxlp_with & VXLAN_PARAM_WITH_LOCAL_ADDR6) {
		int error = vxlan_sockaddr_in6_embedscope(&vxlp->vxlp_local_sa);
		if (error)
			return (error);
	}
	if (vxlp->vxlp_with & VXLAN_PARAM_WITH_REMOTE_ADDR6) {
		int error = vxlan_sockaddr_in6_embedscope(
		   &vxlp->vxlp_remote_sa);
		if (error)
			return (error);
	}
#endif

	if (vxlp->vxlp_with & VXLAN_PARAM_WITH_VNI) {
		if (vxlan_check_vni(vxlp->vxlp_vni) == 0)
			sc->vxl_vni = vxlp->vxlp_vni;
	}

	if (vxlp->vxlp_with & VXLAN_PARAM_WITH_LOCAL_ADDR4) {
		sc->vxl_src_addr.in4.sin_len = sizeof(struct sockaddr_in);
		sc->vxl_src_addr.in4.sin_family = AF_INET;
		sc->vxl_src_addr.in4.sin_addr =
		    vxlp->vxlp_local_sa.in4.sin_addr;
	} else if (vxlp->vxlp_with & VXLAN_PARAM_WITH_LOCAL_ADDR6) {
		sc->vxl_src_addr.in6.sin6_len = sizeof(struct sockaddr_in6);
		sc->vxl_src_addr.in6.sin6_family = AF_INET6;
		sc->vxl_src_addr.in6.sin6_addr =
		    vxlp->vxlp_local_sa.in6.sin6_addr;
	}

	if (vxlp->vxlp_with & VXLAN_PARAM_WITH_REMOTE_ADDR4) {
		sc->vxl_dst_addr.in4.sin_len = sizeof(struct sockaddr_in);
		sc->vxl_dst_addr.in4.sin_family = AF_INET;
		sc->vxl_dst_addr.in4.sin_addr =
		    vxlp->vxlp_remote_sa.in4.sin_addr;
	} else if (vxlp->vxlp_with & VXLAN_PARAM_WITH_REMOTE_ADDR6) {
		sc->vxl_dst_addr.in6.sin6_len = sizeof(struct sockaddr_in6);
		sc->vxl_dst_addr.in6.sin6_family = AF_INET6;
		sc->vxl_dst_addr.in6.sin6_addr =
		    vxlp->vxlp_remote_sa.in6.sin6_addr;
	}

	if (vxlp->vxlp_with & VXLAN_PARAM_WITH_LOCAL_PORT)
		sc->vxl_src_addr.in4.sin_port = htons(vxlp->vxlp_local_port);
	if (vxlp->vxlp_with & VXLAN_PARAM_WITH_REMOTE_PORT)
		sc->vxl_dst_addr.in4.sin_port = htons(vxlp->vxlp_remote_port);

	if (vxlp->vxlp_with & VXLAN_PARAM_WITH_PORT_RANGE) {
		if (vxlp->vxlp_min_port <= vxlp->vxlp_max_port) {
			sc->vxl_min_port = vxlp->vxlp_min_port;
			sc->vxl_max_port = vxlp->vxlp_max_port;
		}
	}

	if (vxlp->vxlp_with & VXLAN_PARAM_WITH_MULTICAST_IF)
		strlcpy(sc->vxl_mc_ifname, vxlp->vxlp_mc_ifname, IFNAMSIZ);

	if (vxlp->vxlp_with & VXLAN_PARAM_WITH_FTABLE_TIMEOUT) {
		if (vxlan_check_ftable_timeout(vxlp->vxlp_ftable_timeout) == 0)
			sc->vxl_ftable_timeout = vxlp->vxlp_ftable_timeout;
	}

	if (vxlp->vxlp_with & VXLAN_PARAM_WITH_FTABLE_MAX) {
		if (vxlan_check_ftable_max(vxlp->vxlp_ftable_max) == 0)
			sc->vxl_ftable_max = vxlp->vxlp_ftable_max;
	}

	if (vxlp->vxlp_with & VXLAN_PARAM_WITH_TTL) {
		if (vxlan_check_ttl(vxlp->vxlp_ttl) == 0)
			sc->vxl_ttl = vxlp->vxlp_ttl;
	}

	if (vxlp->vxlp_with & VXLAN_PARAM_WITH_LEARN) {
		if (vxlp->vxlp_learn == 0)
			sc->vxl_flags &= ~VXLAN_FLAG_LEARN;
	}

	return (0);
}