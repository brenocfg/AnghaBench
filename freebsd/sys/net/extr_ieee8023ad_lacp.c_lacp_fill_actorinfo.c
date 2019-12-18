#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lagg_softc {int /*<<< orphan*/  sc_ifp; } ;
struct lagg_port {struct lagg_softc* lp_softc; } ;
struct lacp_port {int /*<<< orphan*/  lp_state; TYPE_2__* lp_ifp; struct lagg_port* lp_lagg; } ;
struct TYPE_4__ {void* lpi_portno; void* lpi_prio; } ;
struct TYPE_6__ {int /*<<< orphan*/  lsi_mac; void* lsi_prio; } ;
struct lacp_peerinfo {int /*<<< orphan*/  lip_state; TYPE_1__ lip_portid; TYPE_3__ lip_systemid; } ;
struct TYPE_5__ {int /*<<< orphan*/  if_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  IF_LLADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LACP_PORT_PRIO ; 
 int /*<<< orphan*/  LACP_SYSTEM_PRIO ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lacp_fill_actorinfo(struct lacp_port *lp, struct lacp_peerinfo *info)
{
	struct lagg_port *lgp = lp->lp_lagg;
	struct lagg_softc *sc = lgp->lp_softc;

	info->lip_systemid.lsi_prio = htons(LACP_SYSTEM_PRIO);
	memcpy(&info->lip_systemid.lsi_mac,
	    IF_LLADDR(sc->sc_ifp), ETHER_ADDR_LEN);
	info->lip_portid.lpi_prio = htons(LACP_PORT_PRIO);
	info->lip_portid.lpi_portno = htons(lp->lp_ifp->if_index);
	info->lip_state = lp->lp_state;
}