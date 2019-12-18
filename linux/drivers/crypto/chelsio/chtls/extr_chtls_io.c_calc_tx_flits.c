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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {unsigned int nr_frags; } ;

/* Variables and functions */
 unsigned int sgl_len (unsigned int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff const*) ; 
 scalar_t__ skb_tail_pointer (struct sk_buff const*) ; 
 scalar_t__ skb_transport_header (struct sk_buff const*) ; 

__attribute__((used)) static unsigned int calc_tx_flits(const struct sk_buff *skb,
				  unsigned int immdlen)
{
	unsigned int flits, cnt;

	flits = immdlen / 8;   /* headers */
	cnt = skb_shinfo(skb)->nr_frags;
	if (skb_tail_pointer(skb) != skb_transport_header(skb))
		cnt++;
	return flits + sgl_len(cnt);
}