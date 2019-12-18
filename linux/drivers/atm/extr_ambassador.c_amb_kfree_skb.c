#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_4__ {TYPE_1__* vcc; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* pop ) (TYPE_1__*,struct sk_buff*) ;} ;

/* Variables and functions */
 TYPE_2__* ATM_SKB (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,struct sk_buff*) ; 

__attribute__((used)) static void amb_kfree_skb (struct sk_buff * skb) {
  if (ATM_SKB(skb)->vcc->pop) {
    ATM_SKB(skb)->vcc->pop (ATM_SKB(skb)->vcc, skb);
  } else {
    dev_kfree_skb_any (skb);
  }
}