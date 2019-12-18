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
typedef  scalar_t__ u8 ;
struct owl_dma_vchan {scalar_t__ drq; } ;
struct owl_dma {scalar_t__ nr_vchans; int /*<<< orphan*/  dma; } ;
struct of_phandle_args {scalar_t__* args; } ;
struct of_dma {struct owl_dma* of_dma_data; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 struct dma_chan* dma_get_any_slave_channel (int /*<<< orphan*/ *) ; 
 struct owl_dma_vchan* to_owl_vchan (struct dma_chan*) ; 

__attribute__((used)) static struct dma_chan *owl_dma_of_xlate(struct of_phandle_args *dma_spec,
					 struct of_dma *ofdma)
{
	struct owl_dma *od = ofdma->of_dma_data;
	struct owl_dma_vchan *vchan;
	struct dma_chan *chan;
	u8 drq = dma_spec->args[0];

	if (drq > od->nr_vchans)
		return NULL;

	chan = dma_get_any_slave_channel(&od->dma);
	if (!chan)
		return NULL;

	vchan = to_owl_vchan(chan);
	vchan->drq = drq;

	return chan;
}