#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct netfront_info {int num_queues; TYPE_1__* rxq; int /*<<< orphan*/  xbdev; struct ifnet* xn_ifp; } ;
struct ifnet {int if_capenable; int if_capabilities; int if_hwassist; } ;
struct TYPE_5__ {struct ifnet* ifp; } ;
struct TYPE_4__ {TYPE_2__ lro; } ;

/* Variables and functions */
 int CSUM_TSO ; 
 int IFCAP_LRO ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_TSO4 ; 
 int IFCAP_TXCSUM ; 
 int XN_CSUM_FEATURES ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tcp_lro_free (TYPE_2__*) ; 
 int tcp_lro_init (TYPE_2__*) ; 
 scalar_t__ xn_enable_lro ; 

__attribute__((used)) static int
xn_configure_features(struct netfront_info *np)
{
	int err, cap_enabled;
#if (defined(INET) || defined(INET6))
	int i;
#endif
	struct ifnet *ifp;

	ifp = np->xn_ifp;
	err = 0;

	if ((ifp->if_capenable & ifp->if_capabilities) == ifp->if_capenable) {
		/* Current options are available, no need to do anything. */
		return (0);
	}

	/* Try to preserve as many options as possible. */
	cap_enabled = ifp->if_capenable;
	ifp->if_capenable = ifp->if_hwassist = 0;

#if (defined(INET) || defined(INET6))
	if ((cap_enabled & IFCAP_LRO) != 0)
		for (i = 0; i < np->num_queues; i++)
			tcp_lro_free(&np->rxq[i].lro);
	if (xn_enable_lro &&
	    (ifp->if_capabilities & cap_enabled & IFCAP_LRO) != 0) {
	    	ifp->if_capenable |= IFCAP_LRO;
		for (i = 0; i < np->num_queues; i++) {
			err = tcp_lro_init(&np->rxq[i].lro);
			if (err != 0) {
				device_printf(np->xbdev,
				    "LRO initialization failed\n");
				ifp->if_capenable &= ~IFCAP_LRO;
				break;
			}
			np->rxq[i].lro.ifp = ifp;
		}
	}
	if ((ifp->if_capabilities & cap_enabled & IFCAP_TSO4) != 0) {
		ifp->if_capenable |= IFCAP_TSO4;
		ifp->if_hwassist |= CSUM_TSO;
	}
#endif
	if ((ifp->if_capabilities & cap_enabled & IFCAP_TXCSUM) != 0) {
		ifp->if_capenable |= IFCAP_TXCSUM;
		ifp->if_hwassist |= XN_CSUM_FEATURES;
	}
	if ((ifp->if_capabilities & cap_enabled & IFCAP_RXCSUM) != 0)
		ifp->if_capenable |= IFCAP_RXCSUM;

	return (err);
}