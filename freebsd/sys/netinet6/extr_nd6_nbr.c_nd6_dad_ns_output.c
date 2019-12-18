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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  sin6_addr; } ;
struct in6_ifaddr {TYPE_2__ ia_addr; } ;
struct ifnet {int if_flags; int if_drv_flags; } ;
struct dadq {int /*<<< orphan*/ * dad_nonce; int /*<<< orphan*/  dad_ns_ocount; int /*<<< orphan*/  dad_ns_tcount; TYPE_1__* dad_ifa; } ;
struct TYPE_3__ {struct ifnet* ifa_ifp; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 int ND_OPT_NONCE_LEN32 ; 
 scalar_t__ V_dad_enhanced ; 
 int /*<<< orphan*/  arc4random () ; 
 int /*<<< orphan*/  nd6_ns_output (struct ifnet*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nd6_dad_ns_output(struct dadq *dp)
{
	struct in6_ifaddr *ia = (struct in6_ifaddr *)dp->dad_ifa;
	struct ifnet *ifp = dp->dad_ifa->ifa_ifp;
	int i;

	dp->dad_ns_tcount++;
	if ((ifp->if_flags & IFF_UP) == 0) {
		return;
	}
	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0) {
		return;
	}

	dp->dad_ns_ocount++;
	if (V_dad_enhanced != 0) {
		for (i = 0; i < ND_OPT_NONCE_LEN32; i++)
			dp->dad_nonce[i] = arc4random();
		/*
		 * XXXHRS: Note that in the case that
		 * DupAddrDetectTransmits > 1, multiple NS messages with
		 * different nonces can be looped back in an unexpected
		 * order.  The current implementation recognizes only
		 * the latest nonce on the sender side.  Practically it
		 * should work well in almost all cases.
		 */
	}
	nd6_ns_output(ifp, NULL, NULL, &ia->ia_addr.sin6_addr,
	    (uint8_t *)&dp->dad_nonce[0]);
}