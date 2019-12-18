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
typedef  int u32 ;
struct device {int dummy; } ;
struct caam_drv_private_jr {int /*<<< orphan*/  irqtask; TYPE_1__* rregs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  jrintstatus; int /*<<< orphan*/  rconfig_lo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  JRCFG_IMSK ; 
 int JRINT_JR_ERROR ; 
 int /*<<< orphan*/  clrsetbits_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct caam_drv_private_jr* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int rd_reg32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr_reg32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static irqreturn_t caam_jr_interrupt(int irq, void *st_dev)
{
	struct device *dev = st_dev;
	struct caam_drv_private_jr *jrp = dev_get_drvdata(dev);
	u32 irqstate;

	/*
	 * Check the output ring for ready responses, kick
	 * tasklet if jobs done.
	 */
	irqstate = rd_reg32(&jrp->rregs->jrintstatus);
	if (!irqstate)
		return IRQ_NONE;

	/*
	 * If JobR error, we got more development work to do
	 * Flag a bug now, but we really need to shut down and
	 * restart the queue (and fix code).
	 */
	if (irqstate & JRINT_JR_ERROR) {
		dev_err(dev, "job ring error: irqstate: %08x\n", irqstate);
		BUG();
	}

	/* mask valid interrupts */
	clrsetbits_32(&jrp->rregs->rconfig_lo, 0, JRCFG_IMSK);

	/* Have valid interrupt at this point, just ACK and trigger */
	wr_reg32(&jrp->rregs->jrintstatus, irqstate);

	preempt_disable();
	tasklet_schedule(&jrp->irqtask);
	preempt_enable();

	return IRQ_HANDLED;
}