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
struct device {int dummy; } ;
struct caam_drv_private_jr {TYPE_1__* rregs; int /*<<< orphan*/  ridx; } ;
struct TYPE_2__ {int /*<<< orphan*/  rconfig_lo; int /*<<< orphan*/  jrcommand; int /*<<< orphan*/  jrintstatus; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  JRCFG_IMSK ; 
 int JRCR_RESET ; 
 int JRINT_ERR_HALT_COMPLETE ; 
 int JRINT_ERR_HALT_INPROGRESS ; 
 int JRINT_ERR_HALT_MASK ; 
 int /*<<< orphan*/  clrsetbits_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct caam_drv_private_jr* dev_get_drvdata (struct device*) ; 
 int rd_reg32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr_reg32 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int caam_reset_hw_jr(struct device *dev)
{
	struct caam_drv_private_jr *jrp = dev_get_drvdata(dev);
	unsigned int timeout = 100000;

	/*
	 * mask interrupts since we are going to poll
	 * for reset completion status
	 */
	clrsetbits_32(&jrp->rregs->rconfig_lo, 0, JRCFG_IMSK);

	/* initiate flush (required prior to reset) */
	wr_reg32(&jrp->rregs->jrcommand, JRCR_RESET);
	while (((rd_reg32(&jrp->rregs->jrintstatus) & JRINT_ERR_HALT_MASK) ==
		JRINT_ERR_HALT_INPROGRESS) && --timeout)
		cpu_relax();

	if ((rd_reg32(&jrp->rregs->jrintstatus) & JRINT_ERR_HALT_MASK) !=
	    JRINT_ERR_HALT_COMPLETE || timeout == 0) {
		dev_err(dev, "failed to flush job ring %d\n", jrp->ridx);
		return -EIO;
	}

	/* initiate reset */
	timeout = 100000;
	wr_reg32(&jrp->rregs->jrcommand, JRCR_RESET);
	while ((rd_reg32(&jrp->rregs->jrcommand) & JRCR_RESET) && --timeout)
		cpu_relax();

	if (timeout == 0) {
		dev_err(dev, "failed to reset job ring %d\n", jrp->ridx);
		return -EIO;
	}

	/* unmask interrupts */
	clrsetbits_32(&jrp->rregs->rconfig_lo, JRCFG_IMSK, 0);

	return 0;
}