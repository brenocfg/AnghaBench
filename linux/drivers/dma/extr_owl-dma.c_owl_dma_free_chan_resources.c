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
struct owl_dma_vchan {int /*<<< orphan*/  vc; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 struct owl_dma_vchan* to_owl_vchan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_free_chan_resources (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void owl_dma_free_chan_resources(struct dma_chan *chan)
{
	struct owl_dma_vchan *vchan = to_owl_vchan(chan);

	/* Ensure all queued descriptors are freed */
	vchan_free_chan_resources(&vchan->vc);
}