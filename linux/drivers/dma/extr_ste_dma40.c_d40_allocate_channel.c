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
struct d40_phy_res {size_t num; } ;
struct TYPE_3__ {int dev_type; scalar_t__ mode; scalar_t__ dir; int phy_channel; scalar_t__ use_fixed_channel; } ;
struct d40_chan {int log_num; struct d40_phy_res* phy_chan; TYPE_2__* base; TYPE_1__ dma_cfg; } ;
struct TYPE_4__ {int num_phy_chans; struct d40_chan** lookup_phy_chans; struct d40_chan** lookup_log_chans; struct d40_phy_res* phy_res; } ;

/* Variables and functions */
 int D40_PHY_CHAN ; 
 int D40_TYPE_TO_EVENT (int) ; 
 int D40_TYPE_TO_GROUP (int) ; 
 scalar_t__ DMA_DEV_TO_MEM ; 
 scalar_t__ DMA_MEM_TO_DEV ; 
 scalar_t__ DMA_MEM_TO_MEM ; 
 int EINVAL ; 
 scalar_t__ STEDMA40_MODE_LOGICAL ; 
 int /*<<< orphan*/  chan2dev (struct d40_chan*) ; 
 scalar_t__ d40_alloc_mask_set (struct d40_phy_res*,int,int,int,int*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int d40_allocate_channel(struct d40_chan *d40c, bool *first_phy_user)
{
	int dev_type = d40c->dma_cfg.dev_type;
	int event_group;
	int event_line;
	struct d40_phy_res *phys;
	int i;
	int j;
	int log_num;
	int num_phy_chans;
	bool is_src;
	bool is_log = d40c->dma_cfg.mode == STEDMA40_MODE_LOGICAL;

	phys = d40c->base->phy_res;
	num_phy_chans = d40c->base->num_phy_chans;

	if (d40c->dma_cfg.dir == DMA_DEV_TO_MEM) {
		log_num = 2 * dev_type;
		is_src = true;
	} else if (d40c->dma_cfg.dir == DMA_MEM_TO_DEV ||
		   d40c->dma_cfg.dir == DMA_MEM_TO_MEM) {
		/* dst event lines are used for logical memcpy */
		log_num = 2 * dev_type + 1;
		is_src = false;
	} else
		return -EINVAL;

	event_group = D40_TYPE_TO_GROUP(dev_type);
	event_line = D40_TYPE_TO_EVENT(dev_type);

	if (!is_log) {
		if (d40c->dma_cfg.dir == DMA_MEM_TO_MEM) {
			/* Find physical half channel */
			if (d40c->dma_cfg.use_fixed_channel) {
				i = d40c->dma_cfg.phy_channel;
				if (d40_alloc_mask_set(&phys[i], is_src,
						       0, is_log,
						       first_phy_user))
					goto found_phy;
			} else {
				for (i = 0; i < num_phy_chans; i++) {
					if (d40_alloc_mask_set(&phys[i], is_src,
						       0, is_log,
						       first_phy_user))
						goto found_phy;
				}
			}
		} else
			for (j = 0; j < d40c->base->num_phy_chans; j += 8) {
				int phy_num = j  + event_group * 2;
				for (i = phy_num; i < phy_num + 2; i++) {
					if (d40_alloc_mask_set(&phys[i],
							       is_src,
							       0,
							       is_log,
							       first_phy_user))
						goto found_phy;
				}
			}
		return -EINVAL;
found_phy:
		d40c->phy_chan = &phys[i];
		d40c->log_num = D40_PHY_CHAN;
		goto out;
	}
	if (dev_type == -1)
		return -EINVAL;

	/* Find logical channel */
	for (j = 0; j < d40c->base->num_phy_chans; j += 8) {
		int phy_num = j + event_group * 2;

		if (d40c->dma_cfg.use_fixed_channel) {
			i = d40c->dma_cfg.phy_channel;

			if ((i != phy_num) && (i != phy_num + 1)) {
				dev_err(chan2dev(d40c),
					"invalid fixed phy channel %d\n", i);
				return -EINVAL;
			}

			if (d40_alloc_mask_set(&phys[i], is_src, event_line,
					       is_log, first_phy_user))
				goto found_log;

			dev_err(chan2dev(d40c),
				"could not allocate fixed phy channel %d\n", i);
			return -EINVAL;
		}

		/*
		 * Spread logical channels across all available physical rather
		 * than pack every logical channel at the first available phy
		 * channels.
		 */
		if (is_src) {
			for (i = phy_num; i < phy_num + 2; i++) {
				if (d40_alloc_mask_set(&phys[i], is_src,
						       event_line, is_log,
						       first_phy_user))
					goto found_log;
			}
		} else {
			for (i = phy_num + 1; i >= phy_num; i--) {
				if (d40_alloc_mask_set(&phys[i], is_src,
						       event_line, is_log,
						       first_phy_user))
					goto found_log;
			}
		}
	}
	return -EINVAL;

found_log:
	d40c->phy_chan = &phys[i];
	d40c->log_num = log_num;
out:

	if (is_log)
		d40c->base->lookup_log_chans[d40c->log_num] = d40c;
	else
		d40c->base->lookup_phy_chans[d40c->phy_chan->num] = d40c;

	return 0;

}