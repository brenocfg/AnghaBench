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
struct TYPE_4__ {int /*<<< orphan*/  chan; } ;
struct tegra_adma_chan {unsigned int sreq_index; int sreq_reserved; int sreq_dir; TYPE_2__ vc; struct tegra_adma* tdma; } ;
struct tegra_adma {int /*<<< orphan*/  dev; int /*<<< orphan*/  rx_requests_reserved; int /*<<< orphan*/  tx_requests_reserved; TYPE_1__* cdata; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
struct TYPE_3__ {unsigned int ch_req_max; } ;

/* Variables and functions */
#define  DMA_DEV_TO_MEM 129 
#define  DMA_MEM_TO_DEV 128 
 int EINVAL ; 
 int /*<<< orphan*/  dev_WARN (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_chan_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tegra_adma_request_alloc(struct tegra_adma_chan *tdc,
				    enum dma_transfer_direction direction)
{
	struct tegra_adma *tdma = tdc->tdma;
	unsigned int sreq_index = tdc->sreq_index;

	if (tdc->sreq_reserved)
		return tdc->sreq_dir == direction ? 0 : -EINVAL;

	if (sreq_index > tdma->cdata->ch_req_max) {
		dev_err(tdma->dev, "invalid DMA request\n");
		return -EINVAL;
	}

	switch (direction) {
	case DMA_MEM_TO_DEV:
		if (test_and_set_bit(sreq_index, &tdma->tx_requests_reserved)) {
			dev_err(tdma->dev, "DMA request reserved\n");
			return -EINVAL;
		}
		break;

	case DMA_DEV_TO_MEM:
		if (test_and_set_bit(sreq_index, &tdma->rx_requests_reserved)) {
			dev_err(tdma->dev, "DMA request reserved\n");
			return -EINVAL;
		}
		break;

	default:
		dev_WARN(tdma->dev, "channel %s has invalid transfer type\n",
			 dma_chan_name(&tdc->vc.chan));
		return -EINVAL;
	}

	tdc->sreq_dir = direction;
	tdc->sreq_reserved = true;

	return 0;
}