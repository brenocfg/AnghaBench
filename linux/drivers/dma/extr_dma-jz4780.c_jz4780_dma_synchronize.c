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
struct jz4780_dma_dev {int dummy; } ;
struct jz4780_dma_chan {int /*<<< orphan*/  id; int /*<<< orphan*/  vchan; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jz4780_dma_chan_disable (struct jz4780_dma_dev*,int /*<<< orphan*/ ) ; 
 struct jz4780_dma_dev* jz4780_dma_chan_parent (struct jz4780_dma_chan*) ; 
 struct jz4780_dma_chan* to_jz4780_dma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_synchronize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void jz4780_dma_synchronize(struct dma_chan *chan)
{
	struct jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);
	struct jz4780_dma_dev *jzdma = jz4780_dma_chan_parent(jzchan);

	vchan_synchronize(&jzchan->vchan);
	jz4780_dma_chan_disable(jzdma, jzchan->id);
}