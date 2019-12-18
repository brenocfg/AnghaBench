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
struct edma_chan {int /*<<< orphan*/  ch_num; struct edma_cc* ecc; } ;
struct edma_cc {int default_queue; int num_tc; } ;
typedef  enum dma_event_q { ____Placeholder_dma_event_q } dma_event_q ;

/* Variables and functions */
 int EDMA_CHAN_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDMA_DMAQNUM ; 
 int EVENTQ_DEFAULT ; 
 int /*<<< orphan*/  edma_modify_array (struct edma_cc*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void edma_assign_channel_eventq(struct edma_chan *echan,
				       enum dma_event_q eventq_no)
{
	struct edma_cc *ecc = echan->ecc;
	int channel = EDMA_CHAN_SLOT(echan->ch_num);
	int bit = (channel & 0x7) * 4;

	/* default to low priority queue */
	if (eventq_no == EVENTQ_DEFAULT)
		eventq_no = ecc->default_queue;
	if (eventq_no >= ecc->num_tc)
		return;

	eventq_no &= 7;
	edma_modify_array(ecc, EDMA_DMAQNUM, (channel >> 3), ~(0x7 << bit),
			  eventq_no << bit);
}