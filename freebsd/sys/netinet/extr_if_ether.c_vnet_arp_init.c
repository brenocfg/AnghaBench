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

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_DEFAULT_VNET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arp_iflladdr ; 
 int /*<<< orphan*/  arp_nh ; 
 int /*<<< orphan*/  curvnet ; 
 int /*<<< orphan*/  iflladdr_event ; 
 int /*<<< orphan*/  iflladdr_tag ; 
 int /*<<< orphan*/  netisr_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netisr_register_vnet (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vnet_arp_init(void)
{

	if (IS_DEFAULT_VNET(curvnet)) {
		netisr_register(&arp_nh);
		iflladdr_tag = EVENTHANDLER_REGISTER(iflladdr_event,
		    arp_iflladdr, NULL, EVENTHANDLER_PRI_ANY);
	}
#ifdef VIMAGE
	else
		netisr_register_vnet(&arp_nh);
#endif
}