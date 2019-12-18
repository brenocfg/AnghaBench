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
typedef  int u32 ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int /*<<< orphan*/  hrz_dev ;

/* Variables and functions */
 int DBG_BUS ; 
 int DBG_FLOW ; 
 int DBG_IRQ ; 
 int DBG_RX ; 
 int DBG_TX ; 
 int DBG_WARN ; 
 int INTERESTING_INTERRUPTS ; 
 int /*<<< orphan*/  INT_SOURCE_REG_OFF ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  PRINTD (int,char*,...) ; 
 int RX_BUS_MASTER_COMPLETE ; 
 int RX_DATA_AV ; 
 int TX_BUS_MASTER_COMPLETE ; 
 int rd_regl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_bus_master_complete_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx_data_av_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_bus_master_complete_handler (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t interrupt_handler(int irq, void *dev_id)
{
  hrz_dev *dev = dev_id;
  u32 int_source;
  unsigned int irq_ok;
  
  PRINTD (DBG_FLOW, "interrupt_handler: %p", dev_id);
  
  // definitely for us
  irq_ok = 0;
  while ((int_source = rd_regl (dev, INT_SOURCE_REG_OFF)
	  & INTERESTING_INTERRUPTS)) {
    // In the interests of fairness, the handlers below are
    // called in sequence and without immediate return to the head of
    // the while loop. This is only of issue for slow hosts (or when
    // debugging messages are on). Really slow hosts may find a fast
    // sender keeps them permanently in the IRQ handler. :(
    
    // (only an issue for slow hosts) RX completion goes before
    // rx_data_av as the former implies rx_busy and so the latter
    // would just abort. If it reschedules another transfer
    // (continuing the same frame) then it will not clear rx_busy.
    
    // (only an issue for slow hosts) TX completion goes before RX
    // data available as it is a much shorter routine - there is the
    // chance that any further transfers it schedules will be complete
    // by the time of the return to the head of the while loop
    
    if (int_source & RX_BUS_MASTER_COMPLETE) {
      ++irq_ok;
      PRINTD (DBG_IRQ|DBG_BUS|DBG_RX, "rx_bus_master_complete asserted");
      rx_bus_master_complete_handler (dev);
    }
    if (int_source & TX_BUS_MASTER_COMPLETE) {
      ++irq_ok;
      PRINTD (DBG_IRQ|DBG_BUS|DBG_TX, "tx_bus_master_complete asserted");
      tx_bus_master_complete_handler (dev);
    }
    if (int_source & RX_DATA_AV) {
      ++irq_ok;
      PRINTD (DBG_IRQ|DBG_RX, "rx_data_av asserted");
      rx_data_av_handler (dev);
    }
  }
  if (irq_ok) {
    PRINTD (DBG_IRQ, "work done: %u", irq_ok);
  } else {
    PRINTD (DBG_IRQ|DBG_WARN, "spurious interrupt source: %#x", int_source);
  }
  
  PRINTD (DBG_IRQ|DBG_FLOW, "interrupt_handler done: %p", dev_id);
  if (irq_ok)
	return IRQ_HANDLED;
  return IRQ_NONE;
}