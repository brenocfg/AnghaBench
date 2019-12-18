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
struct eni_dev {int /*<<< orphan*/  tx_wait; int /*<<< orphan*/  lock; int /*<<< orphan*/  events; } ;
struct atm_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,struct atm_dev*) ; 
 struct eni_dev* ENI_DEV (struct atm_dev*) ; 
 int /*<<< orphan*/  EVENT (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MID_DMA_ERR_ACK ; 
 int MID_RX_DMA_COMPLETE ; 
 int MID_SERVICE ; 
 int MID_TX_COMPLETE ; 
 int MID_TX_DMA_COMPLETE ; 
 int MID_TX_DMA_OVFL ; 
 int MID_TX_IDENT_MISM ; 
 int /*<<< orphan*/  bug_int (struct atm_dev*,int) ; 
 int /*<<< orphan*/  dequeue_rx (struct atm_dev*) ; 
 int /*<<< orphan*/  dequeue_tx (struct atm_dev*) ; 
 int /*<<< orphan*/  get_service (struct atm_dev*) ; 
 int /*<<< orphan*/  poll_rx (struct atm_dev*) ; 
 int /*<<< orphan*/  poll_tx (struct atm_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_complete ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eni_tasklet(unsigned long data)
{
	struct atm_dev *dev = (struct atm_dev *) data;
	struct eni_dev *eni_dev = ENI_DEV(dev);
	unsigned long flags;
	u32 events;

	DPRINTK("eni_tasklet (dev %p)\n",dev);
	spin_lock_irqsave(&eni_dev->lock,flags);
	events = xchg(&eni_dev->events,0);
	spin_unlock_irqrestore(&eni_dev->lock,flags);
	if (events & MID_RX_DMA_COMPLETE) {
		EVENT("INT: RX DMA complete, starting dequeue_rx\n",0,0);
		dequeue_rx(dev);
		EVENT("dequeue_rx done, starting poll_rx\n",0,0);
		poll_rx(dev);
		EVENT("poll_rx done\n",0,0);
		/* poll_tx ? */
	}
	if (events & MID_SERVICE) {
		EVENT("INT: service, starting get_service\n",0,0);
		get_service(dev);
		EVENT("get_service done, starting poll_rx\n",0,0);
		poll_rx(dev);
		EVENT("poll_rx done\n",0,0);
	}
 	if (events & MID_TX_DMA_COMPLETE) {
		EVENT("INT: TX DMA COMPLETE\n",0,0);
		dequeue_tx(dev);
	}
	if (events & MID_TX_COMPLETE) {
		EVENT("INT: TX COMPLETE\n",0,0);
		tx_complete++;
		wake_up(&eni_dev->tx_wait);
		/* poll_rx ? */
	}
	if (events & (MID_DMA_ERR_ACK | MID_TX_IDENT_MISM | MID_TX_DMA_OVFL)) {
		EVENT("bug interrupt\n",0,0);
		bug_int(dev,events);
	}
	poll_tx(dev);
}