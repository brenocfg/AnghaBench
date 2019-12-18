#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
struct TYPE_18__ {struct sk_buff* skb; } ;
typedef  TYPE_4__ tx_simple ;
struct TYPE_19__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_5__ tx_out ;
struct sk_buff {int dummy; } ;
struct TYPE_17__ {int /*<<< orphan*/  tx_ok; } ;
struct TYPE_20__ {TYPE_3__ stats; } ;
typedef  TYPE_6__ amb_dev ;
struct TYPE_16__ {TYPE_1__* stats; } ;
struct TYPE_15__ {int /*<<< orphan*/  tx; } ;
struct TYPE_14__ {TYPE_2__* vcc; } ;

/* Variables and functions */
 TYPE_13__* ATM_SKB (struct sk_buff*) ; 
 int DBG_FLOW ; 
 int DBG_TX ; 
 int /*<<< orphan*/  PRINTD (int,char*,TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  amb_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_4__* bus_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_4__*) ; 

__attribute__((used)) static void tx_complete (amb_dev * dev, tx_out * tx) {
  tx_simple * tx_descr = bus_to_virt (tx->handle);
  struct sk_buff * skb = tx_descr->skb;
  
  PRINTD (DBG_FLOW|DBG_TX, "tx_complete %p %p", dev, tx);
  
  // VC layer stats
  atomic_inc(&ATM_SKB(skb)->vcc->stats->tx);
  
  // free the descriptor
  kfree (tx_descr);
  
  // free the skb
  amb_kfree_skb (skb);
  
  dev->stats.tx_ok++;
  return;
}