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
struct netfront_info {int maxfrags; TYPE_1__* xn_ifp; int /*<<< orphan*/  xbdev; } ;
struct TYPE_2__ {int if_capabilities; } ;

/* Variables and functions */
 int IFCAP_HWCSUM ; 
 int IFCAP_LRO ; 
 int IFCAP_TSO4 ; 
 int MAX_TX_REQ_FRAGS ; 
 int /*<<< orphan*/  XST_NIL ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  xenbus_get_otherend_path (int /*<<< orphan*/ ) ; 
 scalar_t__ xs_scanf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,int*) ; 

__attribute__((used)) static void
xn_query_features(struct netfront_info *np)
{
	int val;

	device_printf(np->xbdev, "backend features:");

	if (xs_scanf(XST_NIL, xenbus_get_otherend_path(np->xbdev),
		"feature-sg", NULL, "%d", &val) != 0)
		val = 0;

	np->maxfrags = 1;
	if (val) {
		np->maxfrags = MAX_TX_REQ_FRAGS;
		printf(" feature-sg");
	}

	if (xs_scanf(XST_NIL, xenbus_get_otherend_path(np->xbdev),
		"feature-gso-tcpv4", NULL, "%d", &val) != 0)
		val = 0;

	np->xn_ifp->if_capabilities &= ~(IFCAP_TSO4|IFCAP_LRO);
	if (val) {
		np->xn_ifp->if_capabilities |= IFCAP_TSO4|IFCAP_LRO;
		printf(" feature-gso-tcp4");
	}

	/*
	 * HW CSUM offload is assumed to be available unless
	 * feature-no-csum-offload is set in xenstore.
	 */
	if (xs_scanf(XST_NIL, xenbus_get_otherend_path(np->xbdev),
		"feature-no-csum-offload", NULL, "%d", &val) != 0)
		val = 0;

	np->xn_ifp->if_capabilities |= IFCAP_HWCSUM;
	if (val) {
		np->xn_ifp->if_capabilities &= ~(IFCAP_HWCSUM);
		printf(" feature-no-csum-offload");
	}

	printf("\n");
}