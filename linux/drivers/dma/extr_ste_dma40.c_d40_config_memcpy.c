#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  dev_type; } ;
struct TYPE_9__ {int /*<<< orphan*/  lcsp3; int /*<<< orphan*/  lcsp1; } ;
struct TYPE_8__ {size_t chan_id; TYPE_1__* device; } ;
struct d40_chan {int /*<<< orphan*/  dst_def_cfg; int /*<<< orphan*/  src_def_cfg; TYPE_4__ dma_cfg; TYPE_3__ log_def; TYPE_2__ chan; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;
struct TYPE_7__ {int /*<<< orphan*/  cap_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D40_SREG_CFG_EIM_POS ; 
 int /*<<< orphan*/  D40_SREG_CFG_TIM_POS ; 
 int /*<<< orphan*/  DMA_MEMCPY ; 
 int /*<<< orphan*/  DMA_SLAVE ; 
 int EINVAL ; 
 int /*<<< orphan*/  chan_err (struct d40_chan*,char*) ; 
 int /*<<< orphan*/  d40_log_cfg (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dma40_memcpy_channels ; 
 TYPE_4__ dma40_memcpy_conf_log ; 
 TYPE_4__ dma40_memcpy_conf_phy ; 
 scalar_t__ dma_has_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int d40_config_memcpy(struct d40_chan *d40c)
{
	dma_cap_mask_t cap = d40c->chan.device->cap_mask;

	if (dma_has_cap(DMA_MEMCPY, cap) && !dma_has_cap(DMA_SLAVE, cap)) {
		d40c->dma_cfg = dma40_memcpy_conf_log;
		d40c->dma_cfg.dev_type = dma40_memcpy_channels[d40c->chan.chan_id];

		d40_log_cfg(&d40c->dma_cfg,
			    &d40c->log_def.lcsp1, &d40c->log_def.lcsp3);

	} else if (dma_has_cap(DMA_MEMCPY, cap) &&
		   dma_has_cap(DMA_SLAVE, cap)) {
		d40c->dma_cfg = dma40_memcpy_conf_phy;

		/* Generate interrrupt at end of transfer or relink. */
		d40c->dst_def_cfg |= BIT(D40_SREG_CFG_TIM_POS);

		/* Generate interrupt on error. */
		d40c->src_def_cfg |= BIT(D40_SREG_CFG_EIM_POS);
		d40c->dst_def_cfg |= BIT(D40_SREG_CFG_EIM_POS);

	} else {
		chan_err(d40c, "No memcpy\n");
		return -EINVAL;
	}

	return 0;
}