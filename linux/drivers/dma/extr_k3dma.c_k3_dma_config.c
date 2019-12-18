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
struct k3_dma_chan {int /*<<< orphan*/  slave_config; } ;
struct dma_slave_config {int dummy; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dma_slave_config*,int) ; 
 struct k3_dma_chan* to_k3_chan (struct dma_chan*) ; 

__attribute__((used)) static int k3_dma_config(struct dma_chan *chan,
			 struct dma_slave_config *cfg)
{
	struct k3_dma_chan *c = to_k3_chan(chan);

	memcpy(&c->slave_config, cfg, sizeof(*cfg));

	return 0;
}