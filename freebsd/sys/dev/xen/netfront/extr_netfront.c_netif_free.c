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
struct netfront_info {int /*<<< orphan*/  sc_media; int /*<<< orphan*/ * xn_ifp; int /*<<< orphan*/  txq; int /*<<< orphan*/  rxq; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  XN_LOCK (struct netfront_info*) ; 
 int /*<<< orphan*/  XN_UNLOCK (struct netfront_info*) ; 
 int /*<<< orphan*/  ether_ifdetach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_disconnect_backend (struct netfront_info*) ; 
 int /*<<< orphan*/  xn_stop (struct netfront_info*) ; 

__attribute__((used)) static void
netif_free(struct netfront_info *np)
{

	XN_LOCK(np);
	xn_stop(np);
	XN_UNLOCK(np);
	netif_disconnect_backend(np);
	ether_ifdetach(np->xn_ifp);
	free(np->rxq, M_DEVBUF);
	free(np->txq, M_DEVBUF);
	if_free(np->xn_ifp);
	np->xn_ifp = NULL;
	ifmedia_removeall(&np->sc_media);
}