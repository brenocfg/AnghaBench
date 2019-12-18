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
struct of_phandle_args {int /*<<< orphan*/ * args; } ;
struct of_dma {struct moxart_dmadev* of_dma_data; } ;
struct moxart_dmadev {int /*<<< orphan*/  dma_slave; } ;
struct moxart_chan {int /*<<< orphan*/  line_reqno; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 struct dma_chan* dma_get_any_slave_channel (int /*<<< orphan*/ *) ; 
 struct moxart_chan* to_moxart_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static struct dma_chan *moxart_of_xlate(struct of_phandle_args *dma_spec,
					struct of_dma *ofdma)
{
	struct moxart_dmadev *mdc = ofdma->of_dma_data;
	struct dma_chan *chan;
	struct moxart_chan *ch;

	chan = dma_get_any_slave_channel(&mdc->dma_slave);
	if (!chan)
		return NULL;

	ch = to_moxart_dma_chan(chan);
	ch->line_reqno = dma_spec->args[0];

	return chan;
}