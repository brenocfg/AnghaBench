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
typedef  int /*<<< orphan*/  u32 ;
struct d40_phy_res {scalar_t__ allocated_src; scalar_t__ allocated_dst; size_t num; } ;
struct TYPE_3__ {scalar_t__ dir; int /*<<< orphan*/  dev_type; } ;
struct d40_chan {size_t log_num; int busy; int configured; TYPE_2__* base; struct d40_phy_res* phy_chan; TYPE_1__ dma_cfg; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/ ** lookup_phy_chans; int /*<<< orphan*/ ** lookup_log_chans; } ;

/* Variables and functions */
 scalar_t__ D40_ALLOC_FREE ; 
 int /*<<< orphan*/  D40_DMA_STOP ; 
 int /*<<< orphan*/  D40_TYPE_TO_EVENT (int /*<<< orphan*/ ) ; 
 scalar_t__ DMA_DEV_TO_MEM ; 
 scalar_t__ DMA_MEM_TO_DEV ; 
 scalar_t__ DMA_MEM_TO_MEM ; 
 int EINVAL ; 
 int /*<<< orphan*/  chan_err (struct d40_chan*,char*) ; 
 scalar_t__ chan_is_logical (struct d40_chan*) ; 
 int /*<<< orphan*/  d40_alloc_mask_free (struct d40_phy_res*,int,int /*<<< orphan*/ ) ; 
 int d40_channel_execute_command (struct d40_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d40_term_all (struct d40_chan*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int d40_free_dma(struct d40_chan *d40c)
{

	int res = 0;
	u32 event = D40_TYPE_TO_EVENT(d40c->dma_cfg.dev_type);
	struct d40_phy_res *phy = d40c->phy_chan;
	bool is_src;

	/* Terminate all queued and active transfers */
	d40_term_all(d40c);

	if (phy == NULL) {
		chan_err(d40c, "phy == null\n");
		return -EINVAL;
	}

	if (phy->allocated_src == D40_ALLOC_FREE &&
	    phy->allocated_dst == D40_ALLOC_FREE) {
		chan_err(d40c, "channel already free\n");
		return -EINVAL;
	}

	if (d40c->dma_cfg.dir == DMA_MEM_TO_DEV ||
	    d40c->dma_cfg.dir == DMA_MEM_TO_MEM)
		is_src = false;
	else if (d40c->dma_cfg.dir == DMA_DEV_TO_MEM)
		is_src = true;
	else {
		chan_err(d40c, "Unknown direction\n");
		return -EINVAL;
	}

	pm_runtime_get_sync(d40c->base->dev);
	res = d40_channel_execute_command(d40c, D40_DMA_STOP);
	if (res) {
		chan_err(d40c, "stop failed\n");
		goto mark_last_busy;
	}

	d40_alloc_mask_free(phy, is_src, chan_is_logical(d40c) ? event : 0);

	if (chan_is_logical(d40c))
		d40c->base->lookup_log_chans[d40c->log_num] = NULL;
	else
		d40c->base->lookup_phy_chans[phy->num] = NULL;

	if (d40c->busy) {
		pm_runtime_mark_last_busy(d40c->base->dev);
		pm_runtime_put_autosuspend(d40c->base->dev);
	}

	d40c->busy = false;
	d40c->phy_chan = NULL;
	d40c->configured = false;
 mark_last_busy:
	pm_runtime_mark_last_busy(d40c->base->dev);
	pm_runtime_put_autosuspend(d40c->base->dev);
	return res;
}