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
typedef  size_t u_int ;
struct netfront_info {size_t num_queues; int /*<<< orphan*/ * txq; int /*<<< orphan*/ * rxq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  XN_RX_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XN_RX_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XN_TX_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XN_TX_UNLOCK (int /*<<< orphan*/ *) ; 
 struct netfront_info* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netfront_carrier_off (struct netfront_info*) ; 

__attribute__((used)) static int
netfront_suspend(device_t dev)
{
	struct netfront_info *np = device_get_softc(dev);
	u_int i;

	for (i = 0; i < np->num_queues; i++) {
		XN_RX_LOCK(&np->rxq[i]);
		XN_TX_LOCK(&np->txq[i]);
	}
	netfront_carrier_off(np);
	for (i = 0; i < np->num_queues; i++) {
		XN_RX_UNLOCK(&np->rxq[i]);
		XN_TX_UNLOCK(&np->txq[i]);
	}
	return (0);
}