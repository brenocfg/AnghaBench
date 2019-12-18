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
struct scatterlist {int dummy; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;

/* Variables and functions */
 struct dma_async_tx_descriptor* d40_prep_sg (struct dma_chan*,struct scatterlist*,struct scatterlist*,unsigned int,int,unsigned long) ; 
 int /*<<< orphan*/  is_slave_direction (int) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *
d40_prep_slave_sg(struct dma_chan *chan, struct scatterlist *sgl,
		  unsigned int sg_len, enum dma_transfer_direction direction,
		  unsigned long dma_flags, void *context)
{
	if (!is_slave_direction(direction))
		return NULL;

	return d40_prep_sg(chan, sgl, sgl, sg_len, direction, dma_flags);
}