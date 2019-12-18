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
struct psp_device {int sev_int_rcvd; TYPE_1__* vdata; scalar_t__ io_regs; int /*<<< orphan*/  sev_int_queue; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ intsts_reg; scalar_t__ cmdresp_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int PSP_CMDRESP_RESP ; 
 unsigned int PSP_CMD_COMPLETE ; 
 void* ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t psp_irq_handler(int irq, void *data)
{
	struct psp_device *psp = data;
	unsigned int status;
	int reg;

	/* Read the interrupt status: */
	status = ioread32(psp->io_regs + psp->vdata->intsts_reg);

	/* Check if it is command completion: */
	if (!(status & PSP_CMD_COMPLETE))
		goto done;

	/* Check if it is SEV command completion: */
	reg = ioread32(psp->io_regs + psp->vdata->cmdresp_reg);
	if (reg & PSP_CMDRESP_RESP) {
		psp->sev_int_rcvd = 1;
		wake_up(&psp->sev_int_queue);
	}

done:
	/* Clear the interrupt status by writing the same value we read. */
	iowrite32(status, psp->io_regs + psp->vdata->intsts_reg);

	return IRQ_HANDLED;
}