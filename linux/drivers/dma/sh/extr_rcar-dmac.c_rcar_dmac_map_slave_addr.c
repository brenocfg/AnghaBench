#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ slave_addr; size_t xfer_size; } ;
struct rcar_dmac_chan_map {int dir; TYPE_4__ slave; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {scalar_t__ slave_addr; size_t xfer_size; } ;
struct TYPE_5__ {scalar_t__ slave_addr; size_t xfer_size; } ;
struct rcar_dmac_chan {int /*<<< orphan*/  index; TYPE_2__ dst; TYPE_1__ src; struct rcar_dmac_chan_map map; } ;
struct dma_chan {TYPE_3__* device; } ;
typedef  scalar_t__ phys_addr_t ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DMA_DEV_TO_MEM ; 
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 int EIO ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,scalar_t__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,scalar_t__*) ; 
 int /*<<< orphan*/  dma_map_resource (int /*<<< orphan*/ ,scalar_t__,size_t,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ ) ; 
 struct rcar_dmac_chan* to_rcar_dmac_chan (struct dma_chan*) ; 

__attribute__((used)) static int rcar_dmac_map_slave_addr(struct dma_chan *chan,
				    enum dma_transfer_direction dir)
{
	struct rcar_dmac_chan *rchan = to_rcar_dmac_chan(chan);
	struct rcar_dmac_chan_map *map = &rchan->map;
	phys_addr_t dev_addr;
	size_t dev_size;
	enum dma_data_direction dev_dir;

	if (dir == DMA_DEV_TO_MEM) {
		dev_addr = rchan->src.slave_addr;
		dev_size = rchan->src.xfer_size;
		dev_dir = DMA_TO_DEVICE;
	} else {
		dev_addr = rchan->dst.slave_addr;
		dev_size = rchan->dst.xfer_size;
		dev_dir = DMA_FROM_DEVICE;
	}

	/* Reuse current map if possible. */
	if (dev_addr == map->slave.slave_addr &&
	    dev_size == map->slave.xfer_size &&
	    dev_dir == map->dir)
		return 0;

	/* Remove old mapping if present. */
	if (map->slave.xfer_size)
		dma_unmap_resource(chan->device->dev, map->addr,
				   map->slave.xfer_size, map->dir, 0);
	map->slave.xfer_size = 0;

	/* Create new slave address map. */
	map->addr = dma_map_resource(chan->device->dev, dev_addr, dev_size,
				     dev_dir, 0);

	if (dma_mapping_error(chan->device->dev, map->addr)) {
		dev_err(chan->device->dev,
			"chan%u: failed to map %zx@%pap", rchan->index,
			dev_size, &dev_addr);
		return -EIO;
	}

	dev_dbg(chan->device->dev, "chan%u: map %zx@%pap to %pad dir: %s\n",
		rchan->index, dev_size, &dev_addr, &map->addr,
		dev_dir == DMA_TO_DEVICE ? "DMA_TO_DEVICE" : "DMA_FROM_DEVICE");

	map->slave.slave_addr = dev_addr;
	map->slave.xfer_size = dev_size;
	map->dir = dev_dir;

	return 0;
}