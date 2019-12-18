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
struct ulp_skb_cb {int flags; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int ULPCB_FLAG_NEED_HDR ; 
 int ULPCB_FLAG_NO_APPEND ; 
 int ULPCB_FLAG_NO_HDR ; 
 struct ulp_skb_cb* ULP_SKB_CB (struct sk_buff*) ; 

__attribute__((used)) static void tx_skb_finalize(struct sk_buff *skb)
{
	struct ulp_skb_cb *cb = ULP_SKB_CB(skb);

	if (!(cb->flags & ULPCB_FLAG_NO_HDR))
		cb->flags = ULPCB_FLAG_NEED_HDR;
	cb->flags |= ULPCB_FLAG_NO_APPEND;
}