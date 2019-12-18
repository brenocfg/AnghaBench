#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lsi_mac; } ;
struct lacp_port {TYPE_1__ lp_systemid; struct ifnet* lp_ifp; } ;
struct lacp_markerinfo {int /*<<< orphan*/  mi_rq_xid; int /*<<< orphan*/  mi_rq_system; int /*<<< orphan*/  mi_rq_port; } ;
struct ifnet {int /*<<< orphan*/  if_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lacp_fill_markerinfo(struct lacp_port *lp, struct lacp_markerinfo *info)
{
	struct ifnet *ifp = lp->lp_ifp;

	/* Fill in the port index and system id (encoded as the MAC) */
	info->mi_rq_port = htons(ifp->if_index);
	memcpy(&info->mi_rq_system, lp->lp_systemid.lsi_mac, ETHER_ADDR_LEN);
	info->mi_rq_xid = htonl(0);
}