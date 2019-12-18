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
struct edma_regs {int /*<<< orphan*/  cr; TYPE_1__* tcd; } ;
struct fsl_edma_engine {int n_chans; struct fsl_edma_chan* chans; struct edma_regs regs; } ;
struct fsl_edma_chan {scalar_t__ slave_id; int /*<<< orphan*/  pm_state; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  csr; } ;

/* Variables and functions */
 int EDMA_CR_ERCA ; 
 int EDMA_CR_ERGA ; 
 int /*<<< orphan*/  RUNNING ; 
 struct fsl_edma_engine* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  edma_writel (struct fsl_edma_engine*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edma_writew (struct fsl_edma_engine*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_edma_chan_mux (struct fsl_edma_chan*,scalar_t__,int) ; 

__attribute__((used)) static int fsl_edma_resume_early(struct device *dev)
{
	struct fsl_edma_engine *fsl_edma = dev_get_drvdata(dev);
	struct fsl_edma_chan *fsl_chan;
	struct edma_regs *regs = &fsl_edma->regs;
	int i;

	for (i = 0; i < fsl_edma->n_chans; i++) {
		fsl_chan = &fsl_edma->chans[i];
		fsl_chan->pm_state = RUNNING;
		edma_writew(fsl_edma, 0x0, &regs->tcd[i].csr);
		if (fsl_chan->slave_id != 0)
			fsl_edma_chan_mux(fsl_chan, fsl_chan->slave_id, true);
	}

	edma_writel(fsl_edma, EDMA_CR_ERGA | EDMA_CR_ERCA, regs->cr);

	return 0;
}