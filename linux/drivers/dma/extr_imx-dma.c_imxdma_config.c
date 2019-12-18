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
struct imxdma_channel {int /*<<< orphan*/  config; } ;
struct dma_slave_config {int dummy; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dma_slave_config*,int) ; 
 struct imxdma_channel* to_imxdma_chan (struct dma_chan*) ; 

__attribute__((used)) static int imxdma_config(struct dma_chan *chan,
			 struct dma_slave_config *dmaengine_cfg)
{
	struct imxdma_channel *imxdmac = to_imxdma_chan(chan);

	memcpy(&imxdmac->config, dmaengine_cfg, sizeof(*dmaengine_cfg));

	return 0;
}