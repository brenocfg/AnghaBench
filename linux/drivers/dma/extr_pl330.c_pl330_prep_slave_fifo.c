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
struct TYPE_4__ {TYPE_1__* device; } ;
struct dma_pl330_chan {int dir; int burst_sz; int /*<<< orphan*/  fifo_dma; int /*<<< orphan*/  fifo_addr; TYPE_2__ chan; } ;
struct device {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_map_resource (struct device*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int pl330_dma_slave_map_dir (int) ; 
 int /*<<< orphan*/  pl330_unprep_slave_fifo (struct dma_pl330_chan*) ; 

__attribute__((used)) static bool pl330_prep_slave_fifo(struct dma_pl330_chan *pch,
				  enum dma_transfer_direction dir)
{
	struct device *dev = pch->chan.device->dev;
	enum dma_data_direction dma_dir = pl330_dma_slave_map_dir(dir);

	/* Already mapped for this config? */
	if (pch->dir == dma_dir)
		return true;

	pl330_unprep_slave_fifo(pch);
	pch->fifo_dma = dma_map_resource(dev, pch->fifo_addr,
					 1 << pch->burst_sz, dma_dir, 0);
	if (dma_mapping_error(dev, pch->fifo_dma))
		return false;

	pch->dir = dma_dir;
	return true;
}