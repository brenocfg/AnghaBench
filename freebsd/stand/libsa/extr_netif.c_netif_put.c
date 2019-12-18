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
struct netif_driver {char* netif_bname; scalar_t__ (* netif_put ) (struct iodesc*,void*,size_t) ;} ;
struct netif {int nif_unit; struct netif_driver* nif_driver; } ;
struct iodesc {struct netif* io_netif; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ netif_debug ; 
 int /*<<< orphan*/  panic (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*,int,...) ; 
 scalar_t__ stub1 (struct iodesc*,void*,size_t) ; 

ssize_t
netif_put(struct iodesc *desc, void *pkt, size_t len)
{
#ifdef NETIF_DEBUG
	struct netif *nif = desc->io_netif;
#endif
	struct netif_driver *drv = desc->io_netif->nif_driver;
	ssize_t rv;

#ifdef NETIF_DEBUG
	if (netif_debug)
		printf("%s%d: netif_put\n", drv->netif_bname, nif->nif_unit);
#endif
#ifdef PARANOID
	if (drv->netif_put == NULL)
		panic("%s%d: no netif_put support", drv->netif_bname,
		    nif->nif_unit);
#endif
	rv = drv->netif_put(desc, pkt, len);
#ifdef NETIF_DEBUG
	if (netif_debug)
		printf("%s%d: netif_put returning %d\n", drv->netif_bname,
		    nif->nif_unit, (int)rv);
#endif
	return (rv);
}