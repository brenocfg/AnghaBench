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
struct netif_driver {char* netif_bname; int (* netif_match ) (struct netif*,void*) ;} ;
struct netif {int nif_unit; int /*<<< orphan*/  nif_sel; struct netif_driver* nif_driver; } ;

/* Variables and functions */
 scalar_t__ netif_debug ; 
 int /*<<< orphan*/  printf (char*,char*,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct netif*,void*) ; 

int
netif_match(struct netif *nif, void *machdep_hint)
{
	struct netif_driver *drv = nif->nif_driver;

#if NETIF_DEBUG
	if (netif_debug)
		printf("%s%d: netif_match (%d)\n", drv->netif_bname,
		    nif->nif_unit, nif->nif_sel);
#endif
	return drv->netif_match(nif, machdep_hint);
}