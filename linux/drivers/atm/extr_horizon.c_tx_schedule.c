#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  len; } ;
struct TYPE_16__ {unsigned int tx_bytes; unsigned int tx_regions; unsigned int tx_addr; struct sk_buff* tx_skb; TYPE_1__* tx_iovec; int /*<<< orphan*/  flags; } ;
typedef  TYPE_4__ hrz_dev ;
struct TYPE_15__ {TYPE_2__* stats; } ;
struct TYPE_14__ {int /*<<< orphan*/  tx; } ;
struct TYPE_13__ {unsigned int iov_base; unsigned int iov_len; } ;
struct TYPE_12__ {TYPE_3__* vcc; } ;

/* Variables and functions */
 TYPE_11__* ATM_SKB (struct sk_buff*) ; 
 int /*<<< orphan*/  DATA_PORT_OFF ; 
 int DBG_BUS ; 
 int DBG_ERR ; 
 int DBG_TX ; 
 int DBG_WARN ; 
 int /*<<< orphan*/  MASTER_TX_ADDR_REG_OFF ; 
 unsigned int MASTER_TX_AUTO_APPEND_DESC ; 
 int /*<<< orphan*/  MASTER_TX_COUNT_REG_OFF ; 
 unsigned int MAX_PIO_COUNT ; 
 unsigned int MAX_TRANSFER_COUNT ; 
 int /*<<< orphan*/  PRINTD (int,char*) ; 
 int /*<<< orphan*/  TX_DESCRIPTOR_PORT_OFF ; 
 int /*<<< orphan*/  TX_DESCRIPTOR_REG_OFF ; 
 int /*<<< orphan*/  YELLOW_LED_ON (TYPE_4__* const) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 unsigned int cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrz_kfree_skb (struct sk_buff*) ; 
 scalar_t__ rd_regl (TYPE_4__* const,int /*<<< orphan*/ ) ; 
 int spin_count ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_release (TYPE_4__* const) ; 
 int /*<<< orphan*/  ultra ; 
 unsigned int virt_to_bus (unsigned int) ; 
 int /*<<< orphan*/  wr_regl (TYPE_4__* const,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  wrs_regb (TYPE_4__* const,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void tx_schedule (hrz_dev * const dev, int irq) {
  unsigned int tx_bytes;
  
  int append_desc = 0;
  
  int pio_instead = 0;
#ifndef TAILRECURSIONWORKS
  pio_instead = 1;
  while (pio_instead) {
#endif
    // bytes in current region waiting for TX transfer
    tx_bytes = dev->tx_bytes;
    
#if 0
    spin_count = 0;
    while (rd_regl (dev, MASTER_TX_COUNT_REG_OFF)) {
      PRINTD (DBG_TX|DBG_WARN, "TX error: other PCI Bus Master TX still in progress!");
      if (++spin_count > 10) {
	PRINTD (DBG_TX|DBG_ERR, "spun out waiting PCI Bus Master TX completion");
	wr_regl (dev, MASTER_TX_COUNT_REG_OFF, 0);
	tx_release (dev);
	hrz_kfree_skb (dev->tx_skb);
	return;
      }
    }
#endif
    
    if (tx_bytes) {
      // start next transfer within same region
      if (!test_bit (ultra, &dev->flags) || tx_bytes <= MAX_PIO_COUNT) {
	PRINTD (DBG_TX|DBG_BUS, "(pio)");
	pio_instead = 1;
      }
      if (tx_bytes <= MAX_TRANSFER_COUNT) {
	PRINTD (DBG_TX|DBG_BUS, "(simple or last multi)");
	if (!dev->tx_iovec) {
	  // end of last region
	  append_desc = 1;
	}
	dev->tx_bytes = 0;
      } else {
	PRINTD (DBG_TX|DBG_BUS, "(continuing multi)");
	dev->tx_bytes = tx_bytes - MAX_TRANSFER_COUNT;
	tx_bytes = MAX_TRANSFER_COUNT;
      }
    } else {
      // tx_bytes == 0 -- we're between regions
      // regions remaining to transfer
      unsigned int tx_regions = dev->tx_regions;
      
      if (tx_regions) {
	// start a new region
	dev->tx_addr = dev->tx_iovec->iov_base;
	tx_bytes = dev->tx_iovec->iov_len;
	++dev->tx_iovec;
	dev->tx_regions = tx_regions - 1;
	
	if (!test_bit (ultra, &dev->flags) || tx_bytes <= MAX_PIO_COUNT) {
	  PRINTD (DBG_TX|DBG_BUS, "(pio)");
	  pio_instead = 1;
	}
	if (tx_bytes <= MAX_TRANSFER_COUNT) {
	  PRINTD (DBG_TX|DBG_BUS, "(full region)");
	  dev->tx_bytes = 0;
	} else {
	  PRINTD (DBG_TX|DBG_BUS, "(start multi region)");
	  dev->tx_bytes = tx_bytes - MAX_TRANSFER_COUNT;
	  tx_bytes = MAX_TRANSFER_COUNT;
	}
      } else {
	// tx_regions == 0
	// that's all folks - end of frame
	struct sk_buff * skb = dev->tx_skb;
	dev->tx_iovec = NULL;
	
	// VC layer stats
	atomic_inc(&ATM_SKB(skb)->vcc->stats->tx);
	
	// free the skb
	hrz_kfree_skb (skb);
      }
    }
    
    // note: writing TX_COUNT clears any interrupt condition
    if (tx_bytes) {
      if (pio_instead) {
	if (irq)
	  wr_regl (dev, MASTER_TX_COUNT_REG_OFF, 0);
	wrs_regb (dev, DATA_PORT_OFF, dev->tx_addr, tx_bytes);
	if (append_desc)
	  wr_regl (dev, TX_DESCRIPTOR_PORT_OFF, cpu_to_be32 (dev->tx_skb->len));
      } else {
	wr_regl (dev, MASTER_TX_ADDR_REG_OFF, virt_to_bus (dev->tx_addr));
	if (append_desc)
	  wr_regl (dev, TX_DESCRIPTOR_REG_OFF, cpu_to_be32 (dev->tx_skb->len));
	wr_regl (dev, MASTER_TX_COUNT_REG_OFF,
		 append_desc
		 ? tx_bytes | MASTER_TX_AUTO_APPEND_DESC
		 : tx_bytes);
      }
      dev->tx_addr += tx_bytes;
    } else {
      if (irq)
	wr_regl (dev, MASTER_TX_COUNT_REG_OFF, 0);
      YELLOW_LED_ON(dev);
      tx_release (dev);
    }
    
#ifdef TAILRECURSIONWORKS
    // and we all bless optimised tail calls
    if (pio_instead)
      return tx_schedule (dev, 0);
    return;
#else
    // grrrrrrr!
    irq = 0;
  }
  return;
#endif
}