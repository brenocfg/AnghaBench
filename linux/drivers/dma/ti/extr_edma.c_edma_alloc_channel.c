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
struct edma_cc {int dummy; } ;
typedef  enum dma_event_q { ____Placeholder_dma_event_q } dma_event_q ;

/* Variables and functions */
 int /*<<< orphan*/  EDMA_CHANNEL_BIT (int) ; 
 int EDMA_CHAN_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDMA_DRAE ; 
 int /*<<< orphan*/  EDMA_REG_ARRAY_INDEX (int) ; 
 int /*<<< orphan*/  edma_assign_channel_eventq (struct edma_chan*,int) ; 
 int /*<<< orphan*/  edma_or_array2 (struct edma_cc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edma_setup_interrupt (struct edma_chan*,int) ; 
 int /*<<< orphan*/  edma_stop (struct edma_chan*) ; 

__attribute__((used)) static int edma_alloc_channel(struct edma_chan *echan,
			      enum dma_event_q eventq_no)
{
	struct edma_cc *ecc = echan->ecc;
	int channel = EDMA_CHAN_SLOT(echan->ch_num);

	/* ensure access through shadow region 0 */
	edma_or_array2(ecc, EDMA_DRAE, 0, EDMA_REG_ARRAY_INDEX(channel),
		       EDMA_CHANNEL_BIT(channel));

	/* ensure no events are pending */
	edma_stop(echan);

	edma_setup_interrupt(echan, true);

	edma_assign_channel_eventq(echan, eventq_no);

	return 0;
}