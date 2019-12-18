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
typedef  int u8 ;
struct sk_buff {int* data; } ;
struct ag71xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR8216_HEADER_LEN ; 
 int AR8216_PACKET_TYPE_MASK ; 
#define  AR8216_PACKET_TYPE_NORMAL 128 
 int EINVAL ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 

int ag71xx_remove_ar8216_header(struct ag71xx *ag, struct sk_buff *skb,
				int pktlen)
{
	u8 type;

	type = skb->data[1] & AR8216_PACKET_TYPE_MASK;
	switch (type) {
	case AR8216_PACKET_TYPE_NORMAL:
		break;

	default:
		return -EINVAL;
	}

	skb_pull(skb, AR8216_HEADER_LEN);
	return 0;
}