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
struct zynqmp_dma_chan {int /*<<< orphan*/  dst_burst_len; int /*<<< orphan*/  src_burst_len; } ;
struct dma_slave_config {int /*<<< orphan*/  dst_maxburst; int /*<<< orphan*/  src_maxburst; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 struct zynqmp_dma_chan* to_chan (struct dma_chan*) ; 

__attribute__((used)) static int zynqmp_dma_device_config(struct dma_chan *dchan,
				    struct dma_slave_config *config)
{
	struct zynqmp_dma_chan *chan = to_chan(dchan);

	chan->src_burst_len = config->src_maxburst;
	chan->dst_burst_len = config->dst_maxburst;

	return 0;
}