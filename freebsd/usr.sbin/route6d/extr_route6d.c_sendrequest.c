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
struct netinfo6 {int /*<<< orphan*/  rip6_metric; } ;
struct TYPE_3__ {int /*<<< orphan*/  sin6_addr; } ;
struct ifc {int ifc_flags; TYPE_1__ ifc_ripsin; int /*<<< orphan*/  ifc_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  rip6_cmd; struct netinfo6* rip6_nets; } ;

/* Variables and functions */
 int EAFNOSUPPORT ; 
 int /*<<< orphan*/  HOPCNT_INFINITY6 ; 
 int IFF_LOOPBACK ; 
 int IFF_UP ; 
 int /*<<< orphan*/  RIP6_REQUEST ; 
 int /*<<< orphan*/  RIP6_RESPONSE ; 
 int /*<<< orphan*/  RIPSIZE (int) ; 
 int /*<<< orphan*/  inet6_n2p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct netinfo6*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* ripbuf ; 
 int sendpacket (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracet (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sendrequest(struct ifc *ifcp)
{
	struct netinfo6 *np;
	int error;

	if (ifcp->ifc_flags & IFF_LOOPBACK)
		return;
	ripbuf->rip6_cmd = RIP6_REQUEST;
	np = ripbuf->rip6_nets;
	memset(np, 0, sizeof(struct netinfo6));
	np->rip6_metric = HOPCNT_INFINITY6;
	tracet(1, "Send rtdump Request to %s (%s)\n",
		ifcp->ifc_name, inet6_n2p(&ifcp->ifc_ripsin.sin6_addr));
	error = sendpacket(&ifcp->ifc_ripsin, RIPSIZE(1));
	if (error == EAFNOSUPPORT) {
		/* Protocol not supported */
		tracet(1, "Could not send rtdump Request to %s (%s): "
			"set IFF_UP to 0\n",
			ifcp->ifc_name, inet6_n2p(&ifcp->ifc_ripsin.sin6_addr));
		ifcp->ifc_flags &= ~IFF_UP;	/* As if down for AF_INET6 */
	}
	ripbuf->rip6_cmd = RIP6_RESPONSE;
}