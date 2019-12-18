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
struct netif_driver {char* netif_bname; int /*<<< orphan*/  (* netif_end ) (struct netif*) ;} ;
struct netif {int /*<<< orphan*/  nif_unit; struct netif_driver* nif_driver; } ;

/* Variables and functions */
 scalar_t__ netif_debug ; 
 int /*<<< orphan*/  panic (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct netif*) ; 

void
netif_detach(struct netif *nif)
{
	struct netif_driver *drv = nif->nif_driver;

#ifdef NETIF_DEBUG
	if (netif_debug)
		printf("%s%d: netif_detach\n", drv->netif_bname, nif->nif_unit);
#endif
#ifdef PARANOID
	if (drv->netif_end == NULL)
		panic("%s%d: no netif_end support", drv->netif_bname,
		    nif->nif_unit);
#endif
	drv->netif_end(nif);
}