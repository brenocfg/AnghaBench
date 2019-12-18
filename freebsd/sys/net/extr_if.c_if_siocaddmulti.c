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
struct ifnet {int /*<<< orphan*/  (* if_ioctl ) (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  if_vnet; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIOCADDMULTI ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*,int) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
if_siocaddmulti(void *arg, int pending)
{
	struct ifnet *ifp;

	ifp = arg;
#ifdef DIAGNOSTIC
	if (pending > 1)
		if_printf(ifp, "%d SIOCADDMULTI coalesced\n", pending);
#endif
	CURVNET_SET(ifp->if_vnet);
	(void )(*ifp->if_ioctl)(ifp, SIOCADDMULTI, 0);
	CURVNET_RESTORE();
}