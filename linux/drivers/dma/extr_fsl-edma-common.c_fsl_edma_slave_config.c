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
struct fsl_edma_chan {int /*<<< orphan*/  cfg; } ;
struct dma_slave_config {int dummy; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsl_edma_unprep_slave_dma (struct fsl_edma_chan*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dma_slave_config*,int) ; 
 struct fsl_edma_chan* to_fsl_edma_chan (struct dma_chan*) ; 

int fsl_edma_slave_config(struct dma_chan *chan,
				 struct dma_slave_config *cfg)
{
	struct fsl_edma_chan *fsl_chan = to_fsl_edma_chan(chan);

	memcpy(&fsl_chan->cfg, cfg, sizeof(*cfg));
	fsl_edma_unprep_slave_dma(fsl_chan);

	return 0;
}