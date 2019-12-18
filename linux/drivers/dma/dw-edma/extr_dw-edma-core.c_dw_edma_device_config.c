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
struct dw_edma_chan {int configured; int /*<<< orphan*/  config; } ;
struct dma_slave_config {int dummy; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 struct dw_edma_chan* dchan2dw_edma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dma_slave_config*,int) ; 

__attribute__((used)) static int dw_edma_device_config(struct dma_chan *dchan,
				 struct dma_slave_config *config)
{
	struct dw_edma_chan *chan = dchan2dw_edma_chan(dchan);

	memcpy(&chan->config, config, sizeof(*config));
	chan->configured = true;

	return 0;
}