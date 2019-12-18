#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int data_width; int /*<<< orphan*/  psize; } ;
struct TYPE_5__ {int data_width; int /*<<< orphan*/  psize; } ;
struct stedma40_chan_cfg {scalar_t__ mode; scalar_t__ dir; scalar_t__ dev_type; TYPE_3__ dst_info; TYPE_2__ src_info; } ;
struct d40_chan {TYPE_1__* base; } ;
struct TYPE_4__ {scalar_t__ num_log_chans; scalar_t__ num_phy_chans; } ;

/* Variables and functions */
 scalar_t__ DMA_DEV_TO_DEV ; 
 int EINVAL ; 
 scalar_t__ STEDMA40_MODE_LOGICAL ; 
 int /*<<< orphan*/  chan_err (struct d40_chan*,char*,...) ; 
 int d40_psize_2_burst_size (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int d40_validate_conf(struct d40_chan *d40c,
			     struct stedma40_chan_cfg *conf)
{
	int res = 0;
	bool is_log = conf->mode == STEDMA40_MODE_LOGICAL;

	if (!conf->dir) {
		chan_err(d40c, "Invalid direction.\n");
		res = -EINVAL;
	}

	if ((is_log && conf->dev_type > d40c->base->num_log_chans)  ||
	    (!is_log && conf->dev_type > d40c->base->num_phy_chans) ||
	    (conf->dev_type < 0)) {
		chan_err(d40c, "Invalid device type (%d)\n", conf->dev_type);
		res = -EINVAL;
	}

	if (conf->dir == DMA_DEV_TO_DEV) {
		/*
		 * DMAC HW supports it. Will be added to this driver,
		 * in case any dma client requires it.
		 */
		chan_err(d40c, "periph to periph not supported\n");
		res = -EINVAL;
	}

	if (d40_psize_2_burst_size(is_log, conf->src_info.psize) *
	    conf->src_info.data_width !=
	    d40_psize_2_burst_size(is_log, conf->dst_info.psize) *
	    conf->dst_info.data_width) {
		/*
		 * The DMAC hardware only supports
		 * src (burst x width) == dst (burst x width)
		 */

		chan_err(d40c, "src (burst x width) != dst (burst x width)\n");
		res = -EINVAL;
	}

	return res;
}