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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_12__ {int /*<<< orphan*/  cell_header; int /*<<< orphan*/  wr_buf_type; int /*<<< orphan*/  rd_buf_type; int /*<<< orphan*/  partial_crc; } ;
typedef  TYPE_1__ tx_ch_desc ;
struct TYPE_13__ {int channel; scalar_t__ tx_xbr_bits; scalar_t__ tx_pcr_bits; scalar_t__ tx_scr_bits; scalar_t__ tx_bucket_bits; int aal; } ;
typedef  TYPE_2__ hrz_vcc ;
struct TYPE_14__ {int tx_idle; int* tx_channel_record; int /*<<< orphan*/  mem_lock; } ;
typedef  TYPE_3__ hrz_dev ;
struct TYPE_11__ {TYPE_1__* tx_descs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUCKET_CAPACITY_ACCESS ; 
 int /*<<< orphan*/  BUCKET_FULLNESS_ACCESS ; 
 int BUFFER_PTR_MASK ; 
 int CHANNEL_TYPE_AAL3_4 ; 
 int CHANNEL_TYPE_AAL5 ; 
 int CHANNEL_TYPE_RAW_CELLS ; 
 int DBG_ERR ; 
 int DBG_FLOW ; 
 int DBG_QOS ; 
 int DBG_TX ; 
 int DBG_WARN ; 
 short EBUSY ; 
 unsigned short IDLE_CHANNELS_MASK ; 
 int INITIAL_CRC ; 
 int /*<<< orphan*/  PCR_TIMER_ACCESS ; 
 int /*<<< orphan*/  PRINTD (int,char*,...) ; 
 int /*<<< orphan*/  RATE_TYPE_ACCESS ; 
 int /*<<< orphan*/  SCR_TIMER_ACCESS ; 
 int TX_CHANS ; 
 int /*<<< orphan*/  TX_STATUS_OFF ; 
 scalar_t__ VBR_RATE_TYPE ; 
#define  aal0 130 
#define  aal34 129 
#define  aal5 128 
 TYPE_10__* memmap ; 
 int rd_mem (TYPE_3__*,int /*<<< orphan*/ *) ; 
 unsigned short rd_regw (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  update_tx_channel_config (TYPE_3__*,short,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wr_mem (TYPE_3__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static short setup_idle_tx_channel (hrz_dev * dev, hrz_vcc * vcc) {
  unsigned short idle_channels;
  short tx_channel = -1;
  unsigned int spin_count;
  PRINTD (DBG_FLOW|DBG_TX, "setup_idle_tx_channel %p", dev);
  
  // better would be to fail immediately, the caller can then decide whether
  // to wait or drop (depending on whether this is UBR etc.)
  spin_count = 0;
  while (!(idle_channels = rd_regw (dev, TX_STATUS_OFF) & IDLE_CHANNELS_MASK)) {
    PRINTD (DBG_TX|DBG_WARN, "waiting for idle TX channel");
    // delay a bit here
    if (++spin_count > 100) {
      PRINTD (DBG_TX|DBG_ERR, "spun out waiting for idle TX channel");
      return -EBUSY;
    }
  }
  
  // got an idle channel
  {
    // tx_idle ensures we look for idle channels in RR order
    int chan = dev->tx_idle;
    
    int keep_going = 1;
    while (keep_going) {
      if (idle_channels & (1<<chan)) {
	tx_channel = chan;
	keep_going = 0;
      }
      ++chan;
      if (chan == TX_CHANS)
	chan = 0;
    }
    
    dev->tx_idle = chan;
  }
  
  // set up the channel we found
  {
    // Initialise the cell header in the transmit channel descriptor
    // a.k.a. prepare the channel and remember that we have done so.
    
    tx_ch_desc * tx_desc = &memmap->tx_descs[tx_channel];
    u32 rd_ptr;
    u32 wr_ptr;
    u16 channel = vcc->channel;
    
    unsigned long flags;
    spin_lock_irqsave (&dev->mem_lock, flags);
    
    // Update the transmit channel record.
    dev->tx_channel_record[tx_channel] = channel;
    
    // xBR channel
    update_tx_channel_config (dev, tx_channel, RATE_TYPE_ACCESS,
			      vcc->tx_xbr_bits);
    
    // Update the PCR counter preload value etc.
    update_tx_channel_config (dev, tx_channel, PCR_TIMER_ACCESS,
			      vcc->tx_pcr_bits);

#if 0
    if (vcc->tx_xbr_bits == VBR_RATE_TYPE) {
      // SCR timer
      update_tx_channel_config (dev, tx_channel, SCR_TIMER_ACCESS,
				vcc->tx_scr_bits);
      
      // Bucket size...
      update_tx_channel_config (dev, tx_channel, BUCKET_CAPACITY_ACCESS,
				vcc->tx_bucket_bits);
      
      // ... and fullness
      update_tx_channel_config (dev, tx_channel, BUCKET_FULLNESS_ACCESS,
				vcc->tx_bucket_bits);
    }
#endif

    // Initialise the read and write buffer pointers
    rd_ptr = rd_mem (dev, &tx_desc->rd_buf_type) & BUFFER_PTR_MASK;
    wr_ptr = rd_mem (dev, &tx_desc->wr_buf_type) & BUFFER_PTR_MASK;
    
    // idle TX channels should have identical pointers
    if (rd_ptr != wr_ptr) {
      PRINTD (DBG_TX|DBG_ERR, "TX buffer pointers are broken!");
      // spin_unlock... return -E...
      // I wonder if gcc would get rid of one of the pointer aliases
    }
    PRINTD (DBG_TX, "TX buffer pointers are: rd %x, wr %x.",
	    rd_ptr, wr_ptr);
    
    switch (vcc->aal) {
      case aal0:
	PRINTD (DBG_QOS|DBG_TX, "tx_channel: aal0");
	rd_ptr |= CHANNEL_TYPE_RAW_CELLS;
	wr_ptr |= CHANNEL_TYPE_RAW_CELLS;
	break;
      case aal34:
	PRINTD (DBG_QOS|DBG_TX, "tx_channel: aal34");
	rd_ptr |= CHANNEL_TYPE_AAL3_4;
	wr_ptr |= CHANNEL_TYPE_AAL3_4;
	break;
      case aal5:
	rd_ptr |= CHANNEL_TYPE_AAL5;
	wr_ptr |= CHANNEL_TYPE_AAL5;
	// Initialise the CRC
	wr_mem (dev, &tx_desc->partial_crc, INITIAL_CRC);
	break;
    }
    
    wr_mem (dev, &tx_desc->rd_buf_type, rd_ptr);
    wr_mem (dev, &tx_desc->wr_buf_type, wr_ptr);
    
    // Write the Cell Header
    // Payload Type, CLP and GFC would go here if non-zero
    wr_mem (dev, &tx_desc->cell_header, channel);
    
    spin_unlock_irqrestore (&dev->mem_lock, flags);
  }
  
  return tx_channel;
}