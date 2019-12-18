#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  chan_id; } ;
struct TYPE_6__ {TYPE_1__ chan; } ;
struct fsl_edma_chan {TYPE_4__* edma; TYPE_2__ vchan; } ;
struct edma_regs {int /*<<< orphan*/  ceei; int /*<<< orphan*/  cerq; } ;
struct TYPE_8__ {TYPE_3__* drvdata; struct edma_regs regs; } ;
struct TYPE_7__ {scalar_t__ version; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDMA_CEEI_CEEI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edma_writeb (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ v1 ; 

void fsl_edma_disable_request(struct fsl_edma_chan *fsl_chan)
{
	struct edma_regs *regs = &fsl_chan->edma->regs;
	u32 ch = fsl_chan->vchan.chan.chan_id;

	if (fsl_chan->edma->drvdata->version == v1) {
		edma_writeb(fsl_chan->edma, ch, regs->cerq);
		edma_writeb(fsl_chan->edma, EDMA_CEEI_CEEI(ch), regs->ceei);
	} else {
		/* ColdFire is big endian, and accesses natively
		 * big endian I/O peripherals
		 */
		iowrite8(ch, regs->cerq);
		iowrite8(EDMA_CEEI_CEEI(ch), regs->ceei);
	}
}