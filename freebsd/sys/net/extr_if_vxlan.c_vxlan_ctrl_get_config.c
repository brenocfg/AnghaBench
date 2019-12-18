#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union vxlan_sockaddr {int dummy; } vxlan_sockaddr ;
struct vxlan_softc {int vxl_flags; int /*<<< orphan*/  vxl_ttl; int /*<<< orphan*/  vxl_max_port; int /*<<< orphan*/  vxl_min_port; int /*<<< orphan*/  vxl_ftable_timeout; int /*<<< orphan*/  vxl_ftable_max; int /*<<< orphan*/  vxl_ftable_cnt; int /*<<< orphan*/  vxl_mc_ifindex; int /*<<< orphan*/  vxl_dst_addr; int /*<<< orphan*/  vxl_src_addr; int /*<<< orphan*/  vxl_vni; } ;
struct rm_priotracker {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  in6; } ;
struct ifvxlancfg {int vxlc_learn; TYPE_1__ vxlc_remote_sa; TYPE_1__ vxlc_local_sa; int /*<<< orphan*/  vxlc_ttl; int /*<<< orphan*/  vxlc_port_max; int /*<<< orphan*/  vxlc_port_min; int /*<<< orphan*/  vxlc_ftable_timeout; int /*<<< orphan*/  vxlc_ftable_max; int /*<<< orphan*/  vxlc_ftable_cnt; int /*<<< orphan*/  vxlc_mc_ifindex; int /*<<< orphan*/  vxlc_vni; } ;

/* Variables and functions */
 int VXLAN_FLAG_LEARN ; 
 int /*<<< orphan*/  VXLAN_RLOCK (struct vxlan_softc*,struct rm_priotracker*) ; 
 int /*<<< orphan*/  VXLAN_RUNLOCK (struct vxlan_softc*,struct rm_priotracker*) ; 
 scalar_t__ VXLAN_SOCKADDR_IS_IPV6 (TYPE_1__*) ; 
 int /*<<< orphan*/  bzero (struct ifvxlancfg*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sa6_recoverscope (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vxlan_ctrl_get_config(struct vxlan_softc *sc, void *arg)
{
	struct rm_priotracker tracker;
	struct ifvxlancfg *cfg;

	cfg = arg;
	bzero(cfg, sizeof(*cfg));

	VXLAN_RLOCK(sc, &tracker);
	cfg->vxlc_vni = sc->vxl_vni;
	memcpy(&cfg->vxlc_local_sa, &sc->vxl_src_addr,
	    sizeof(union vxlan_sockaddr));
	memcpy(&cfg->vxlc_remote_sa, &sc->vxl_dst_addr,
	    sizeof(union vxlan_sockaddr));
	cfg->vxlc_mc_ifindex = sc->vxl_mc_ifindex;
	cfg->vxlc_ftable_cnt = sc->vxl_ftable_cnt;
	cfg->vxlc_ftable_max = sc->vxl_ftable_max;
	cfg->vxlc_ftable_timeout = sc->vxl_ftable_timeout;
	cfg->vxlc_port_min = sc->vxl_min_port;
	cfg->vxlc_port_max = sc->vxl_max_port;
	cfg->vxlc_learn = (sc->vxl_flags & VXLAN_FLAG_LEARN) != 0;
	cfg->vxlc_ttl = sc->vxl_ttl;
	VXLAN_RUNLOCK(sc, &tracker);

#ifdef INET6
	if (VXLAN_SOCKADDR_IS_IPV6(&cfg->vxlc_local_sa))
		sa6_recoverscope(&cfg->vxlc_local_sa.in6);
	if (VXLAN_SOCKADDR_IS_IPV6(&cfg->vxlc_remote_sa))
		sa6_recoverscope(&cfg->vxlc_remote_sa.in6);
#endif

	return (0);
}