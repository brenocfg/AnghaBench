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
struct dma_chan {int dummy; } ;
struct bcm2835_chan {struct dma_slave_config cfg; } ;

/* Variables and functions */
 struct bcm2835_chan* to_bcm2835_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static int bcm2835_dma_slave_config(struct dma_chan *chan,
				    struct dma_slave_config *cfg)
{
	struct bcm2835_chan *c = to_bcm2835_dma_chan(chan);

	c->cfg = *cfg;

	return 0;
}