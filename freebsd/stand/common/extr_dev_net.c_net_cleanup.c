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
struct TYPE_2__ {scalar_t__ s_addr; } ;

/* Variables and functions */
 scalar_t__ debug ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_name ; 
 int netdev_sock ; 
 int /*<<< orphan*/  netif_close (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_1__ rootip ; 

__attribute__((used)) static void
net_cleanup(void)
{

	if (netdev_sock >= 0) {
#ifdef	NETIF_DEBUG
		if (debug)
			printf("net_cleanup: calling netif_close()\n");
#endif
		rootip.s_addr = 0;
		free(netdev_name);
		netif_close(netdev_sock);
		netdev_sock = -1;
	}
}