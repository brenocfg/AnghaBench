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
struct uml_net_private {int dummy; } ;
struct sk_buff {TYPE_1__* dev; } ;
struct TYPE_2__ {scalar_t__ mtu; } ;

/* Variables and functions */
 scalar_t__ ETH_HEADER_ETHERTAP ; 
 int net_recvfrom (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  skb_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int etap_read(int fd, struct sk_buff *skb, struct uml_net_private *lp)
{
	int len;

	len = net_recvfrom(fd, skb_mac_header(skb),
			   skb->dev->mtu + 2 + ETH_HEADER_ETHERTAP);
	if (len <= 0)
		return(len);

	skb_pull(skb, 2);
	len -= 2;
	return len;
}