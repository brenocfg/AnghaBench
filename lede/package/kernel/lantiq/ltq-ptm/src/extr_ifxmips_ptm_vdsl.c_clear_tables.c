#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  dataptr; } ;
struct TYPE_9__ {int /*<<< orphan*/  dataptr; } ;
struct TYPE_8__ {int /*<<< orphan*/  dataptr; } ;
struct TYPE_7__ {int /*<<< orphan*/  dataptr; } ;
struct TYPE_6__ {int /*<<< orphan*/  dataptr; } ;

/* Variables and functions */
 TYPE_5__* CPU_TO_WAN_TX_DESC_BASE ; 
 int CPU_TO_WAN_TX_DESC_NUM ; 
 TYPE_4__* FASTPATH_TO_WAN_TX_DESC_BASE ; 
 int FASTPATH_TO_WAN_TX_DESC_NUM ; 
 TYPE_3__* WAN_RX_DESC_BASE ; 
 int WAN_RX_DESC_NUM ; 
 TYPE_2__* WAN_SWAP_DESC_BASE ; 
 int WAN_SWAP_DESC_NUM ; 
 TYPE_1__* WAN_TX_DESC_BASE (int) ; 
 int WAN_TX_DESC_NUM ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct sk_buff* get_skb_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void clear_tables(void)
{
    struct sk_buff *skb;
    int i, j;

    for ( i = 0; i < WAN_RX_DESC_NUM; i++ ) {
        skb = get_skb_pointer(WAN_RX_DESC_BASE[i].dataptr);
        if ( skb != NULL )
            dev_kfree_skb_any(skb);
    }

    for ( i = 0; i < CPU_TO_WAN_TX_DESC_NUM; i++ ) {
        skb = get_skb_pointer(CPU_TO_WAN_TX_DESC_BASE[i].dataptr);
        if ( skb != NULL )
            dev_kfree_skb_any(skb);
    }

    for ( j = 0; j < 8; j++ )
        for ( i = 0; i < WAN_TX_DESC_NUM; i++ ) {
            skb = get_skb_pointer(WAN_TX_DESC_BASE(j)[i].dataptr);
            if ( skb != NULL )
                dev_kfree_skb_any(skb);
        }

    for ( i = 0; i < WAN_SWAP_DESC_NUM; i++ ) {
        skb = get_skb_pointer(WAN_SWAP_DESC_BASE[i].dataptr);
        if ( skb != NULL )
            dev_kfree_skb_any(skb);
    }

    for ( i = 0; i < FASTPATH_TO_WAN_TX_DESC_NUM; i++ ) {
        skb = get_skb_pointer(FASTPATH_TO_WAN_TX_DESC_BASE[i].dataptr);
        if ( skb != NULL )
            dev_kfree_skb_any(skb);
    }
}