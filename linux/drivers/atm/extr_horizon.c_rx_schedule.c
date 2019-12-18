#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct atm_vcc {int /*<<< orphan*/  (* push ) (struct atm_vcc*,struct sk_buff*) ;TYPE_2__* stats; } ;
struct TYPE_14__ {unsigned int rx_bytes; unsigned int rx_regions; unsigned int rx_addr; int /*<<< orphan*/  flags; int /*<<< orphan*/  rx_channel; struct sk_buff* rx_skb; TYPE_1__* rx_iovec; } ;
typedef  TYPE_3__ hrz_dev ;
struct TYPE_13__ {int /*<<< orphan*/  rx; } ;
struct TYPE_12__ {unsigned int iov_base; unsigned int iov_len; } ;
struct TYPE_11__ {struct atm_vcc* vcc; } ;

/* Variables and functions */
 TYPE_10__* ATM_SKB (struct sk_buff*) ; 
 int /*<<< orphan*/  DATA_PORT_OFF ; 
 int DBG_BUS ; 
 int DBG_ERR ; 
 int DBG_RX ; 
 int DBG_SKB ; 
 int DBG_WARN ; 
 int /*<<< orphan*/  FLUSH_RX_CHANNEL (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MASTER_RX_ADDR_REG_OFF ; 
 int /*<<< orphan*/  MASTER_RX_COUNT_REG_OFF ; 
 unsigned int MAX_PIO_COUNT ; 
 unsigned int MAX_TRANSFER_COUNT ; 
 int /*<<< orphan*/  PRINTD (int,char*,...) ; 
 int /*<<< orphan*/  YELLOW_LED_ON (TYPE_3__*) ; 
 int /*<<< orphan*/  __net_timestamp (struct sk_buff*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_skb (char*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  hrz_kfree_skb (struct sk_buff*) ; 
 scalar_t__ rd_regl (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rds_regb (TYPE_3__*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  rx_busy ; 
 int spin_count ; 
 int /*<<< orphan*/  stub1 (struct atm_vcc*,struct sk_buff*) ; 
 unsigned int virt_to_bus (unsigned int) ; 
 int /*<<< orphan*/  wr_regl (TYPE_3__*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void rx_schedule (hrz_dev * dev, int irq) {
  unsigned int rx_bytes;
  
  int pio_instead = 0;
#ifndef TAILRECURSIONWORKS
  pio_instead = 1;
  while (pio_instead) {
#endif
    // bytes waiting for RX transfer
    rx_bytes = dev->rx_bytes;
    
#if 0
    spin_count = 0;
    while (rd_regl (dev, MASTER_RX_COUNT_REG_OFF)) {
      PRINTD (DBG_RX|DBG_WARN, "RX error: other PCI Bus Master RX still in progress!");
      if (++spin_count > 10) {
	PRINTD (DBG_RX|DBG_ERR, "spun out waiting PCI Bus Master RX completion");
	wr_regl (dev, MASTER_RX_COUNT_REG_OFF, 0);
	clear_bit (rx_busy, &dev->flags);
	hrz_kfree_skb (dev->rx_skb);
	return;
      }
    }
#endif
    
    // this code follows the TX code but (at the moment) there is only
    // one region - the skb itself. I don't know if this will change,
    // but it doesn't hurt to have the code here, disabled.
    
    if (rx_bytes) {
      // start next transfer within same region
      if (rx_bytes <= MAX_PIO_COUNT) {
	PRINTD (DBG_RX|DBG_BUS, "(pio)");
	pio_instead = 1;
      }
      if (rx_bytes <= MAX_TRANSFER_COUNT) {
	PRINTD (DBG_RX|DBG_BUS, "(simple or last multi)");
	dev->rx_bytes = 0;
      } else {
	PRINTD (DBG_RX|DBG_BUS, "(continuing multi)");
	dev->rx_bytes = rx_bytes - MAX_TRANSFER_COUNT;
	rx_bytes = MAX_TRANSFER_COUNT;
      }
    } else {
      // rx_bytes == 0 -- we're between regions
      // regions remaining to transfer
#if 0
      unsigned int rx_regions = dev->rx_regions;
#else
      unsigned int rx_regions = 0;
#endif
      
      if (rx_regions) {
#if 0
	// start a new region
	dev->rx_addr = dev->rx_iovec->iov_base;
	rx_bytes = dev->rx_iovec->iov_len;
	++dev->rx_iovec;
	dev->rx_regions = rx_regions - 1;
	
	if (rx_bytes <= MAX_PIO_COUNT) {
	  PRINTD (DBG_RX|DBG_BUS, "(pio)");
	  pio_instead = 1;
	}
	if (rx_bytes <= MAX_TRANSFER_COUNT) {
	  PRINTD (DBG_RX|DBG_BUS, "(full region)");
	  dev->rx_bytes = 0;
	} else {
	  PRINTD (DBG_RX|DBG_BUS, "(start multi region)");
	  dev->rx_bytes = rx_bytes - MAX_TRANSFER_COUNT;
	  rx_bytes = MAX_TRANSFER_COUNT;
	}
#endif
      } else {
	// rx_regions == 0
	// that's all folks - end of frame
	struct sk_buff * skb = dev->rx_skb;
	// dev->rx_iovec = 0;
	
	FLUSH_RX_CHANNEL (dev, dev->rx_channel);
	
	dump_skb ("<<<", dev->rx_channel, skb);
	
	PRINTD (DBG_RX|DBG_SKB, "push %p %u", skb->data, skb->len);
	
	{
	  struct atm_vcc * vcc = ATM_SKB(skb)->vcc;
	  // VC layer stats
	  atomic_inc(&vcc->stats->rx);
	  __net_timestamp(skb);
	  // end of our responsibility
	  vcc->push (vcc, skb);
	}
      }
    }
    
    // note: writing RX_COUNT clears any interrupt condition
    if (rx_bytes) {
      if (pio_instead) {
	if (irq)
	  wr_regl (dev, MASTER_RX_COUNT_REG_OFF, 0);
	rds_regb (dev, DATA_PORT_OFF, dev->rx_addr, rx_bytes);
      } else {
	wr_regl (dev, MASTER_RX_ADDR_REG_OFF, virt_to_bus (dev->rx_addr));
	wr_regl (dev, MASTER_RX_COUNT_REG_OFF, rx_bytes);
      }
      dev->rx_addr += rx_bytes;
    } else {
      if (irq)
	wr_regl (dev, MASTER_RX_COUNT_REG_OFF, 0);
      // allow another RX thread to start
      YELLOW_LED_ON(dev);
      clear_bit (rx_busy, &dev->flags);
      PRINTD (DBG_RX, "cleared rx_busy for dev %p", dev);
    }
    
#ifdef TAILRECURSIONWORKS
    // and we all bless optimised tail calls
    if (pio_instead)
      return rx_schedule (dev, 0);
    return;
#else
    // grrrrrrr!
    irq = 0;
  }
  return;
#endif
}