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
struct nuport_mac_priv {scalar_t__* rx_skb; } ;

/* Variables and functions */
 unsigned int RX_RING_SIZE ; 

__attribute__((used)) static unsigned int nuport_mac_has_work(struct nuport_mac_priv *priv)
{
	unsigned int i;

	for (i = 0; i < RX_RING_SIZE; i++)
		if (priv->rx_skb[i])
			return 1;

	return 0;
}