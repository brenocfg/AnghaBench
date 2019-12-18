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
struct netif_driver {int netif_nifs; TYPE_1__* netif_ifs; } ;
struct TYPE_2__ {scalar_t__ dif_used; } ;

/* Variables and functions */
 scalar_t__ netif_debug ; 
 struct netif_driver** netif_drivers ; 
 int /*<<< orphan*/  printf (char*) ; 

void
netif_init(void)
{
	struct netif_driver *drv;
	int d, i;
    
#ifdef NETIF_DEBUG
	if (netif_debug)
		printf("netif_init: called\n");
#endif
	for (d = 0; netif_drivers[d]; d++) {
		drv = netif_drivers[d];
		for (i = 0; i < drv->netif_nifs; i++)
			drv->netif_ifs[i].dif_used = 0;
	}
}