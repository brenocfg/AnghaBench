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
struct ifnet {TYPE_1__* if_debugnet_methods; } ;
struct debugnet_pcb {struct ifnet* dp_ifp; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dn_poll ) (struct ifnet*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ifnet*,int) ; 

void
debugnet_network_poll(struct debugnet_pcb *pcb)
{
	struct ifnet *ifp;

	ifp = pcb->dp_ifp;
	ifp->if_debugnet_methods->dn_poll(ifp, 1000);
}