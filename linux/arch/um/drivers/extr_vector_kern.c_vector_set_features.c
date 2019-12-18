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
struct vector_private {int req_size; int max_packet; int headroom; } ;
struct net_device {int dummy; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_GRO ; 
 int SAFETY_MARGIN ; 
 struct vector_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int vector_set_features(struct net_device *dev,
	netdev_features_t features)
{
	struct vector_private *vp = netdev_priv(dev);
	/* Adjust buffer sizes for GSO/GRO. Unfortunately, there is
	 * no way to negotiate it on raw sockets, so we can change
	 * only our side.
	 */
	if (features & NETIF_F_GRO)
		/* All new frame buffers will be GRO-sized */
		vp->req_size = 65536;
	else
		/* All new frame buffers will be normal sized */
		vp->req_size = vp->max_packet + vp->headroom + SAFETY_MARGIN;
	return 0;
}