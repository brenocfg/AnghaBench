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
struct sk_buff {size_t len; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  __skb_trim (struct sk_buff*,size_t) ; 
 struct sk_buff* alloc_skb (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  skb_cloned (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_get (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_nonlinear (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *get_cpl_skb(struct sk_buff *skb,
				   size_t len, gfp_t gfp)
{
	if (likely(!skb_is_nonlinear(skb) && !skb_cloned(skb))) {
		WARN_ONCE(skb->len < len, "skb alloc error");
		__skb_trim(skb, len);
		skb_get(skb);
	} else {
		skb = alloc_skb(len, gfp);
		if (skb)
			__skb_put(skb, len);
	}
	return skb;
}