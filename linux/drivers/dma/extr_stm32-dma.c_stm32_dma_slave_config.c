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
struct stm32_dma_chan {int config_init; int /*<<< orphan*/  dma_sconfig; } ;
struct dma_slave_config {int dummy; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dma_slave_config*,int) ; 
 struct stm32_dma_chan* to_stm32_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static int stm32_dma_slave_config(struct dma_chan *c,
				  struct dma_slave_config *config)
{
	struct stm32_dma_chan *chan = to_stm32_dma_chan(c);

	memcpy(&chan->dma_sconfig, config, sizeof(*config));

	chan->config_init = true;

	return 0;
}