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
 int /*<<< orphan*/  netfront_carrier_on (struct netfront_info*) ; 
 int /*<<< orphan*/  netif_disconnect_backend (struct netfront_info*) ; 
 scalar_t__ xen_suspend_cancelled ; 

__attribute__((used)) static int
netfront_resume(device_t dev)
{
	struct netfront_info *info = device_get_softc(dev);
	u_int i;

	if (xen_suspend_cancelled) {
		for (i = 0; i < info->num_queues; i++) {
			XN_RX_LOCK(&info->rxq[i]);
			XN_TX_LOCK(&info->txq[i]);
		}
		netfront_carrier_on(info);
		for (i = 0; i < info->num_queues; i++) {
			XN_RX_UNLOCK(&info->rxq[i]);
			XN_TX_UNLOCK(&info->txq[i]);
		}
		return (0);
	}

	netif_disconnect_backend(info);
	return (0);
}