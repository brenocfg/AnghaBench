#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dst_maxburst; int /*<<< orphan*/  src_maxburst; } ;
struct dw_dma_chan {TYPE_1__ dma_sconfig; } ;
struct dw_dma {int /*<<< orphan*/  (* encode_maxburst ) (struct dw_dma_chan*,int /*<<< orphan*/ *) ;} ;
struct dma_slave_config {int dummy; } ;
struct dma_chan {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct dma_slave_config*,int) ; 
 int /*<<< orphan*/  stub1 (struct dw_dma_chan*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct dw_dma_chan*,int /*<<< orphan*/ *) ; 
 struct dw_dma* to_dw_dma (int /*<<< orphan*/ ) ; 
 struct dw_dma_chan* to_dw_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static int dwc_config(struct dma_chan *chan, struct dma_slave_config *sconfig)
{
	struct dw_dma_chan *dwc = to_dw_dma_chan(chan);
	struct dw_dma *dw = to_dw_dma(chan->device);

	memcpy(&dwc->dma_sconfig, sconfig, sizeof(*sconfig));

	dw->encode_maxburst(dwc, &dwc->dma_sconfig.src_maxburst);
	dw->encode_maxburst(dwc, &dwc->dma_sconfig.dst_maxburst);

	return 0;
}