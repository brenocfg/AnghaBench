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
struct dma_slave_config {int dummy; } ;
struct dma_pl330_chan {int /*<<< orphan*/  slave_config; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dma_slave_config*,int) ; 
 struct dma_pl330_chan* to_pchan (struct dma_chan*) ; 

__attribute__((used)) static int pl330_config(struct dma_chan *chan,
			struct dma_slave_config *slave_config)
{
	struct dma_pl330_chan *pch = to_pchan(chan);

	memcpy(&pch->slave_config, slave_config, sizeof(*slave_config));

	return 0;
}