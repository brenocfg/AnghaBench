#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tegra_dma_sg_req {unsigned int req_len; long words_xferred; int /*<<< orphan*/  node; } ;
struct tegra_dma_channel {TYPE_2__* tdma; int /*<<< orphan*/  pending_sg_req; } ;
struct TYPE_4__ {TYPE_1__* chip_data; } ;
struct TYPE_3__ {scalar_t__ support_separate_wcount_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEGRA_APBDMA_CHAN_STATUS ; 
 int /*<<< orphan*/  TEGRA_APBDMA_CHAN_WORD_TRANSFER ; 
 unsigned long TEGRA_APBDMA_STATUS_ISE_EOC ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 unsigned long get_current_xferred_count (struct tegra_dma_channel*,struct tegra_dma_sg_req*,unsigned long) ; 
 int /*<<< orphan*/  list_is_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned long tdc_read (struct tegra_dma_channel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int tegra_dma_sg_bytes_xferred(struct tegra_dma_channel *tdc,
					       struct tegra_dma_sg_req *sg_req)
{
	unsigned long status, wcount = 0;

	if (!list_is_first(&sg_req->node, &tdc->pending_sg_req))
		return 0;

	if (tdc->tdma->chip_data->support_separate_wcount_reg)
		wcount = tdc_read(tdc, TEGRA_APBDMA_CHAN_WORD_TRANSFER);

	status = tdc_read(tdc, TEGRA_APBDMA_CHAN_STATUS);

	if (!tdc->tdma->chip_data->support_separate_wcount_reg)
		wcount = status;

	if (status & TEGRA_APBDMA_STATUS_ISE_EOC)
		return sg_req->req_len;

	wcount = get_current_xferred_count(tdc, sg_req, wcount);

	if (!wcount) {
		/*
		 * If wcount wasn't ever polled for this SG before, then
		 * simply assume that transfer hasn't started yet.
		 *
		 * Otherwise it's the end of the transfer.
		 *
		 * The alternative would be to poll the status register
		 * until EOC bit is set or wcount goes UP. That's so
		 * because EOC bit is getting set only after the last
		 * burst's completion and counter is less than the actual
		 * transfer size by 4 bytes. The counter value wraps around
		 * in a cyclic mode before EOC is set(!), so we can't easily
		 * distinguish start of transfer from its end.
		 */
		if (sg_req->words_xferred)
			wcount = sg_req->req_len - 4;

	} else if (wcount < sg_req->words_xferred) {
		/*
		 * This case will never happen for a non-cyclic transfer.
		 *
		 * For a cyclic transfer, although it is possible for the
		 * next transfer to have already started (resetting the word
		 * count), this case should still not happen because we should
		 * have detected that the EOC bit is set and hence the transfer
		 * was completed.
		 */
		WARN_ON_ONCE(1);

		wcount = sg_req->req_len - 4;
	} else {
		sg_req->words_xferred = wcount;
	}

	return wcount;
}