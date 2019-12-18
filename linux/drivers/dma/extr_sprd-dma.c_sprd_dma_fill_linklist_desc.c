#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sprd_dma_chn_hw {int dummy; } ;
struct TYPE_2__ {scalar_t__ virt_addr; } ;
struct sprd_dma_chn {TYPE_1__ linklist; } ;
struct dma_slave_config {int dummy; } ;
struct dma_chan {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int sprd_dma_fill_desc (struct dma_chan*,struct sprd_dma_chn_hw*,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned long,struct dma_slave_config*) ; 
 struct sprd_dma_chn* to_sprd_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static int sprd_dma_fill_linklist_desc(struct dma_chan *chan,
				       unsigned int sglen, int sg_index,
				       dma_addr_t src, dma_addr_t dst, u32 len,
				       enum dma_transfer_direction dir,
				       unsigned long flags,
				       struct dma_slave_config *slave_cfg)
{
	struct sprd_dma_chn *schan = to_sprd_dma_chan(chan);
	struct sprd_dma_chn_hw *hw;

	if (!schan->linklist.virt_addr)
		return -EINVAL;

	hw = (struct sprd_dma_chn_hw *)(schan->linklist.virt_addr +
					sg_index * sizeof(*hw));

	return sprd_dma_fill_desc(chan, hw, sglen, sg_index, src, dst, len,
				  dir, flags, slave_cfg);
}