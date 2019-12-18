#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  size_t u16 ;
typedef  int /*<<< orphan*/  rx_q_entry ;
struct TYPE_12__ {int /*<<< orphan*/  rd_buf_type; int /*<<< orphan*/  wr_buf_type; } ;
typedef  TYPE_1__ rx_ch_desc ;
struct TYPE_13__ {size_t* spare_buffers; int /*<<< orphan*/  mem_lock; int /*<<< orphan*/ * rx_q_reset; int /*<<< orphan*/ * rx_q_wrap; int /*<<< orphan*/ * rx_q_entry; int /*<<< orphan*/  noof_spare_buffers; } ;
typedef  TYPE_2__ hrz_dev ;
struct TYPE_14__ {int /*<<< orphan*/ * rx_q_entries; TYPE_1__* rx_descs; } ;
typedef  int /*<<< orphan*/  HDW ;

/* Variables and functions */
 int BUFFER_PTR_MASK ; 
 int DBG_RX ; 
 int DBG_VCC ; 
 int DBG_WARN ; 
 int /*<<< orphan*/  FLUSH_RX_CHANNEL (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  PRINTD (int,char*,...) ; 
 int RX_CHANNEL_DISABLED ; 
 int RX_CHANNEL_IDLE ; 
 int RX_CHANS ; 
 int /*<<< orphan*/  RX_QUEUE_WR_PTR_OFF ; 
 int /*<<< orphan*/  SELECT_RX_CHANNEL (TYPE_2__*,size_t) ; 
 int SIMONS_DODGEY_MARKER ; 
 int /*<<< orphan*/  WAIT_FLUSH_RX_COMPLETE (TYPE_2__*) ; 
 int /*<<< orphan*/  WAIT_UPDATE_COMPLETE (TYPE_2__*) ; 
 TYPE_6__* memmap ; 
 int rd_mem (TYPE_2__*,int /*<<< orphan*/ *) ; 
 size_t rd_regw (TYPE_2__*,int /*<<< orphan*/ ) ; 
 size_t rx_q_entry_to_rx_channel (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wr_mem (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void hrz_close_rx (hrz_dev * dev, u16 vc) {
  unsigned long flags;
  
  u32 value;
  
  u32 r1, r2;
  
  rx_ch_desc * rx_desc = &memmap->rx_descs[vc];
  
  int was_idle = 0;
  
  spin_lock_irqsave (&dev->mem_lock, flags);
  value = rd_mem (dev, &rx_desc->wr_buf_type) & BUFFER_PTR_MASK;
  spin_unlock_irqrestore (&dev->mem_lock, flags);
  
  if (value == RX_CHANNEL_DISABLED) {
    // I suppose this could happen once we deal with _NONE traffic properly
    PRINTD (DBG_VCC, "closing VC: RX channel %u already disabled", vc);
    return;
  }
  if (value == RX_CHANNEL_IDLE)
    was_idle = 1;
  
  spin_lock_irqsave (&dev->mem_lock, flags);
  
  for (;;) {
    wr_mem (dev, &rx_desc->wr_buf_type, RX_CHANNEL_DISABLED);
    
    if ((rd_mem (dev, &rx_desc->wr_buf_type) & BUFFER_PTR_MASK) == RX_CHANNEL_DISABLED)
      break;
    
    was_idle = 0;
  }
  
  if (was_idle) {
    spin_unlock_irqrestore (&dev->mem_lock, flags);
    return;
  }
  
  WAIT_FLUSH_RX_COMPLETE(dev);
  
  // XXX Is this all really necessary? We can rely on the rx_data_av
  // handler to discard frames that remain queued for delivery. If the
  // worry is that immediately reopening the channel (perhaps by a
  // different process) may cause some data to be mis-delivered then
  // there may still be a simpler solution (such as busy-waiting on
  // rx_busy once the channel is disabled or before a new one is
  // opened - does this leave any holes?). Arguably setting up and
  // tearing down the TX and RX halves of each virtual circuit could
  // most safely be done within ?x_busy protected regions.
  
  // OK, current changes are that Simon's marker is disabled and we DO
  // look for NULL rxer elsewhere. The code here seems flush frames
  // and then remember the last dead cell belonging to the channel
  // just disabled - the cell gets relinked at the next vc_open.
  // However, when all VCs are closed or only a few opened there are a
  // handful of buffers that are unusable.
  
  // Does anyone feel like documenting spare_buffers properly?
  // Does anyone feel like fixing this in a nicer way?
  
  // Flush any data which is left in the channel
  for (;;) {
    // Change the rx channel port to something different to the RX
    // channel we are trying to close to force Horizon to flush the rx
    // channel read and write pointers.
    
    u16 other = vc^(RX_CHANS/2);
    
    SELECT_RX_CHANNEL (dev, other);
    WAIT_UPDATE_COMPLETE (dev);
    
    r1 = rd_mem (dev, &rx_desc->rd_buf_type);
    
    // Select this RX channel. Flush doesn't seem to work unless we
    // select an RX channel before hand
    
    SELECT_RX_CHANNEL (dev, vc);
    WAIT_UPDATE_COMPLETE (dev);
    
    // Attempt to flush a frame on this RX channel
    
    FLUSH_RX_CHANNEL (dev, vc);
    WAIT_FLUSH_RX_COMPLETE (dev);
    
    // Force Horizon to flush rx channel read and write pointers as before
    
    SELECT_RX_CHANNEL (dev, other);
    WAIT_UPDATE_COMPLETE (dev);
    
    r2 = rd_mem (dev, &rx_desc->rd_buf_type);
    
    PRINTD (DBG_VCC|DBG_RX, "r1 = %u, r2 = %u", r1, r2);
    
    if (r1 == r2) {
      dev->spare_buffers[dev->noof_spare_buffers++] = (u16)r1;
      break;
    }
  }
  
#if 0
  {
    rx_q_entry * wr_ptr = &memmap->rx_q_entries[rd_regw (dev, RX_QUEUE_WR_PTR_OFF)];
    rx_q_entry * rd_ptr = dev->rx_q_entry;
    
    PRINTD (DBG_VCC|DBG_RX, "rd_ptr = %u, wr_ptr = %u", rd_ptr, wr_ptr);
    
    while (rd_ptr != wr_ptr) {
      u32 x = rd_mem (dev, (HDW *) rd_ptr);
      
      if (vc == rx_q_entry_to_rx_channel (x)) {
	x |= SIMONS_DODGEY_MARKER;
	
	PRINTD (DBG_RX|DBG_VCC|DBG_WARN, "marking a frame as dodgey");
	
	wr_mem (dev, (HDW *) rd_ptr, x);
      }
      
      if (rd_ptr == dev->rx_q_wrap)
	rd_ptr = dev->rx_q_reset;
      else
	rd_ptr++;
    }
  }
#endif
  
  spin_unlock_irqrestore (&dev->mem_lock, flags);
  
  return;
}